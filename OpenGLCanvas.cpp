#include "OpenGLCanvas.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <QColor>
#include <QMouseEvent>
#include <QSize>
#include <QDebug>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;




OpenGLCanvas::OpenGLCanvas(QWidget* pQW_Parent)
   : QGLWidget(pQW_Parent), _pucBuffer(NULL)
{
    cube = 1;
    width = 512;
    height = 512;
    do_neighbors = 2;
    tX = 0;
    tY = 0;
    tZ = 0;
    ttX = 0;
    ttY = 0;
    ttZ = 0;
    just_up = 0;
    tW = 0;
    ttW = 0;
    winRadius = 500;
    transfac = .003;
    rad = 1.2;
    sumx = 0;
    sumy = 0;
    sumz = 0.;
    large = 1000000.;
    iterations = 0;
    delay = 4000;
    use_checkImage = 0;
    single_slice = 0;
    fileIsRead = 0;

    settings = 2;
    sliceNum = 60;
    sliceTrans = 0.1f;
    blending = true;

    sliceZ = 0;
    modelTexture = new GLubyte[Nz*Ny*Nx];
    gradientTexture = new GLubyte[4*256];

    shader = 0;

}

OpenGLCanvas::~OpenGLCanvas()
{
   delete[] _pucBuffer;
}

QSize OpenGLCanvas::minimumSizeHint() const
{
   return QSize(100, 100);
}


void OpenGLCanvas::refreshDraw()
{
    reloadShaders();
    paintGL();
    update();
}

void OpenGLCanvas::updateTexture(color* map)
{
    for (int i = 0; i < 256; i++)
    {
        gradientTexture[4*i] = (GLubyte) (map[i].red * 255);
        gradientTexture[4*i+1] = (GLubyte) (map[i].green * 255);
        gradientTexture[4*i+2] = (GLubyte) (map[i].blue * 255);
        gradientTexture[4*i+3] = (GLubyte) (map[i].alpha * 255);

    }

    makeCurrent();
    glBindTexture(GL_TEXTURE_1D, texName[1]);
   // glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, gradientTexture);

    reloadShaders();
    //paintGL();
    update();

}

void OpenGLCanvas::initializeGL()
{
    makeCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glTranslatef(0., 0., -4.);

    gluPerspective(40., width/height, 0.1, 60.);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);



}

void OpenGLCanvas::resizeGL(int iWidth, int iHeight)
{
    width = iWidth;
    height = iHeight;
    if (width > height)
       winRadius = (double)width*.5;
    else
       winRadius = (double)height*.5;

    makeCurrent();
    glViewport(0, 0, (GLsizei) iWidth, (GLsizei) iHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) iWidth/(GLfloat) iHeight, 0.1, 60.0);
    glTranslatef(0., 0., -4.);
    paintGL();

   emit SizeChanged(QSize(iWidth, iHeight));
}

void OpenGLCanvas::paintGL()
{
       int j;
       int sliceDir = 0;
       float correction;

       float tempo[3];
       ticks4 = clock();
       tt = (double)(ticks4 - ticks3)/(double)CLOCKS_PER_SEC;
       if(tt > .05) isSpinning = 0;
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       j = iterations - delay;

       if(isSpinning) {
          glMatrixMode(GL_MODELVIEW);
          doRotation(dX, dY);
          }

       makeCurrent();

       const double clip_plane1[4] = {0.0,1,0.0, 0.5};
       glClipPlane(GL_CLIP_PLANE0, clip_plane1);
       glEnable(GL_CLIP_PLANE0);
       const double clip_plane2[4] = {0.0,-1,0.0, 0.5};
       glClipPlane(GL_CLIP_PLANE1, clip_plane2);
       glEnable(GL_CLIP_PLANE1);

       const double clip_plane3[4] = {1,0.0,0.0, 0.5};
       glClipPlane(GL_CLIP_PLANE2, clip_plane3);
       glEnable(GL_CLIP_PLANE2);

       const double clip_plane4[4] = {-1,0.0,0.0, 0.5};
       glClipPlane(GL_CLIP_PLANE3, clip_plane4);
       glEnable(GL_CLIP_PLANE3);

       const double clip_plane5[4] = {0.0,0.0,1, 0.5};
       glClipPlane(GL_CLIP_PLANE4, clip_plane5);
       glEnable(GL_CLIP_PLANE4);

       const double clip_plane6[4] = {0.0,0.0,-1, 0.5};
       glClipPlane(GL_CLIP_PLANE5, clip_plane6);
       glEnable(GL_CLIP_PLANE5);

       drawBox();

       float mat[16];
       glMatrixMode(GL_MODELVIEW);
       glGetFloatv(GL_MODELVIEW_MATRIX, mat);

       if (fabs(mat[2]) > fabs(mat[6]) && fabs(mat[2]) > fabs(mat[10]))
            sliceDir = 2;
       else if(fabs(mat[6]) > fabs(mat[2]) && fabs(mat[6]) > fabs(mat[10]))
            sliceDir = 1;
       else
            sliceDir = 0;

       glColor4f(1.0, 1.0, 1.0, 1.0);


       if (fileIsRead)
       {
           makeCurrent();
           glUseProgram(program);
          glBegin(GL_QUADS);
            if (settings == 0)
            {
            //Draw single, slideable slice.
            if (sliceDir == 0)
            {
              glTexCoord3f(sliceZ+0.5f, 0.0, 1.0); glVertex3f(-0.5, -0.5, sliceZ);
              glTexCoord3f(sliceZ+0.5f, 0.0, 0.0); glVertex3f(-0.5, 0.5, sliceZ);
              glTexCoord3f(sliceZ+0.5f, 1.0, 0.0); glVertex3f(0.5, 0.5, sliceZ);
              glTexCoord3f(sliceZ+0.5f, 1.0, 1.0); glVertex3f(0.5, -0.5, sliceZ);

            }
            else if (sliceDir == 1)
            {
              glTexCoord3f(0.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, -0.5);
              glTexCoord3f(1.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, 0.5);
              glTexCoord3f(1.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, 0.5);
              glTexCoord3f(0.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, -0.5);
            }
            else
            {
              glTexCoord3f(0.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, -0.5);
              glTexCoord3f(1.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, 0.5);
              glTexCoord3f(1.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, 0.5);
              glTexCoord3f(0.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, -0.5);
            }
            }
            else if (settings == 1)
            {
            //Draw slices in the proper direction.
            if (sliceDir == 0)
            {
                if (mat[10] > 0)
                {
                    for (sliceZ = -0.5f; sliceZ <= 0.5f; sliceZ += 1.0f / (float)sliceNum)
                    {
                    float view[3] = {0.0f, 0.0f,-1.0f};
                    correction = findCorrection(mat, view);
                    //cout << correction << endl;
                    glColor4f(1.0, 1.0, 1.0, correction);
                    glTexCoord3f(sliceZ+0.5f, 0.0, 1.0); glVertex3f(-0.5, -0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 0.0, 0.0); glVertex3f(-0.5, 0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 1.0, 0.0); glVertex3f(0.5, 0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 1.0, 1.0); glVertex3f(0.5, -0.5, sliceZ);
                    }
                }
                else
                {
                    for (sliceZ = 0.5f; sliceZ >= -0.5f; sliceZ -= 1.0f / (float)sliceNum)
                    {
                    float view[3] = {0.0f, 0.0f,-1.0f};
                    correction = findCorrection(mat, view);
                    //cout << correction << endl;
                    glColor4f(1.0, 1.0, 1.0, correction);
                    glTexCoord3f(sliceZ+0.5f, 0.0, 1.0); glVertex3f(-0.5, -0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 0.0, 0.0); glVertex3f(-0.5, 0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 1.0, 0.0); glVertex3f(0.5, 0.5, sliceZ);
                    glTexCoord3f(sliceZ+0.5f, 1.0, 1.0); glVertex3f(0.5, -0.5, sliceZ);
                    }
                }
            }
            else if (sliceDir == 1)
            {
                if (mat[6] > 0)
                {
                    for (sliceZ = 0.5f; sliceZ >= -0.5f; sliceZ -= 1.0f / (float)sliceNum)
                    {
                    float view[3] = {0.0f, -1.0f, 0.0f};
                    correction = findCorrection(mat, view);
                    //cout << correction << endl;
                    glColor4f(1.0, 1.0, 1.0, correction);
                    glTexCoord3f(0.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, -0.5);
                    glTexCoord3f(1.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, 0.5);
                    glTexCoord3f(1.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, 0.5);
                    glTexCoord3f(0.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, -0.5);
                    }
                }
                else
                {
                    for (sliceZ = -0.5f; sliceZ <= 0.5f; sliceZ += 1.0f / (float)sliceNum)
                    {
                    float view[3] = {0.0f, -1.0f, 0.0f};
                    correction = findCorrection(mat, view);
                    //cout << correction << endl;
                    glColor4f(1.0, 1.0, 1.0, correction);
                    glTexCoord3f(0.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, -0.5);
                    glTexCoord3f(1.0, 0.0, sliceZ+0.5f); glVertex3f(-0.5, -sliceZ, 0.5);
                    glTexCoord3f(1.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, 0.5);
                    glTexCoord3f(0.0, 1.0, sliceZ+0.5f); glVertex3f(0.5, -sliceZ, -0.5);
                    }
                }
            }
            else
            {
                if (mat[2] > 0)
                {
                    for (sliceZ = -0.5f; sliceZ <= 0.5f; sliceZ += 1.0f / (float)sliceNum)
                    {
                      float view[3] = {-1.0f, 0.0f,0.0f};
                      correction = findCorrection(mat, view);
                      //cout << correction << endl;
                      glColor4f(1.0, 1.0, 1.0, correction);
                      glTexCoord3f(0.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, -0.5);
                      glTexCoord3f(1.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, 0.5);
                      glTexCoord3f(1.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, 0.5);
                      glTexCoord3f(0.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, -0.5);
                    }
                }
                else
                {
                    for (sliceZ = 0.5f; sliceZ >= -0.5f; sliceZ -= 1.0f / (float)sliceNum)
                    {
                      float view[3] = {-1.0f, 0.0f,0.0f};
                      correction = findCorrection(mat, view);
                      //cout << correction << endl;
                      glColor4f(1.0, 1.0, 1.0, correction);
                      glTexCoord3f(0.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, -0.5);
                      glTexCoord3f(1.0, sliceZ+0.5f, 1.0); glVertex3f(sliceZ, -0.5, 0.5);
                      glTexCoord3f(1.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, 0.5);
                      glTexCoord3f(0.0, sliceZ+0.5f, 0.0); glVertex3f(sliceZ, 0.5, -0.5);
                    }
                }
            }

            }
            else if (settings == 2)
            {

               float pos[3] = {-0.5f, -0.5f, 0};
               glColor4f(1.0, 1.0, 1.0, 0.1);
               for (float i = -0.5f; i <= 0.5f; i += 1.0 / (float)sliceNum)
               {
               pos[0] = 1.5f;
               pos[1] = 1.5f;
               pos[2] = i;
               crossProductPos(mat,pos, tempo);
               glTexCoord3f(tempo[2] + 0.5, tempo[0] + 0.5, -tempo[1]+ 0.5); glVertex3f(tempo[0], tempo[1], tempo[2]);


               pos[0] = -1.5f;
               crossProductPos(mat,pos, tempo);
               glTexCoord3f(tempo[2] + 0.5, tempo[0] + 0.5, -tempo[1]+ 0.5); glVertex3f(tempo[0], tempo[1], tempo[2]);


               pos[1] = -1.5f;
               crossProductPos(mat,pos, tempo);
               glTexCoord3f(tempo[2] + 0.5, tempo[0] + 0.5, -tempo[1]+ 0.5); glVertex3f(tempo[0], tempo[1], tempo[2]);


               pos[0] = 1.5f;
               crossProductPos(mat,pos, tempo);
               glTexCoord3f(tempo[2] + 0.5, tempo[0] + 0.5, -tempo[1]+ 0.5); glVertex3f(tempo[0], tempo[1], tempo[2]);

                }
            }
       glEnd();


      }

       glUseProgram(0);

       glFlush();
       ++iterations;


    //Debugging stuff.
/*
    for (int i = 0; i < 16; i++)
    {
      cout << mat[i] << " ";
      if (i > 0 && i % 4 == 3)
            cout << endl;
    }

    cout << sliceDir << endl;

    cout << endl;
*/
}

void OpenGLCanvas::mousePressEvent(QMouseEvent* pQME_Event)
{

    button = pQME_Event->button();

    dragX = pQME_Event->x();
    dragY = pQME_Event->y();
    dX = 0;
    dY = 0;
    paintGL();
    update();
}

void OpenGLCanvas::mouseReleaseEvent(QMouseEvent* pQME_Event)
{
    int x = pQME_Event->x();
    int y = pQME_Event->y();

    if (button == Qt::LeftButton)
    {
    dX = x - dragX;
    dY = dragY - y;
    if(dX!=0||dY!=0)
       isSpinning = 1;
    else
       isSpinning = 0;

    ticks1 = clock();
    isSpinning = 0;
    just_up = 1;
    }
    paintGL();
    update();
}

void OpenGLCanvas::mouseMoveEvent(QMouseEvent* pQME_Event)
{
    int x = pQME_Event->x();
    int y = pQME_Event->y();


    if (button == Qt::LeftButton) {
          dX = x - dragX;
          dY = dragY - y;
          glMatrixMode(GL_MODELVIEW);
          doRotation(dX, dY);
          dragX = x;
          dragY = y;
          }
    if (button == Qt::MidButton) {
          tX = x - dragX;
          tY = dragY - y;
          ttX += tX;
          ttY += tY;
          dragX = x;
          dragY = y;
          doTranslation(tX, tY, 0);
          }
    if (button == Qt::RightButton) {
          tZ = x - dragX;
          ttZ += tZ;
          tW = y - dragY;
          ttW += tW;
          dragX = x;
          dragY = y;
          doTranslation(0, 0, tZ);
            if (settings == 0)
            {
              sliceZ += (float)tW / 200.0f;
              if (sliceZ > 0.5)
                    sliceZ = 0.5;
              else if (sliceZ < -0.5)
                    sliceZ = -0.5;
            }
          }

       ticks3 = clock();
       tt = (double)(ticks3 - ticks4)/(double)CLOCKS_PER_SEC;
       paintGL();
       update();
}





inline int round(const float a) {return int (a + 0.5);}

void OpenGLCanvas::doTranslation(int tX, int tY, int tZ) {

// Multiply on the right instead of the left

    makeCurrent();
   float m[16];
   glMatrixMode(GL_MODELVIEW);
   glGetFloatv(GL_MODELVIEW_MATRIX, m);
   glLoadIdentity();
   glTranslatef(transfac*tX, transfac*tY, transfac*tZ);
   glMultMatrixf(m);
   }

//Find opacity coefficent
float OpenGLCanvas::findCorrection(float m[16], float w[3])
{
  float v[3];

  v[0] = -m[2];
  v[1] = -m[6];
  v[2] = -m[10];

  float cosine = vdot(v, w);
  float correction = (cosine != 0.0f) ?
        1.0f/cosine : 1.0f;

  return fabs(correction);

}


void OpenGLCanvas::myRotated(double a, double X, double Y, double Z) {

// Multiply on the right instead of the left
makeCurrent();
   float m[16];
   glMatrixMode(GL_MODELVIEW);
   glGetFloatv(GL_MODELVIEW_MATRIX, m);
   glLoadIdentity();

   glTranslatef(transfac*ttX, transfac*ttY, transfac*ttZ);
   glRotated(a, X, Y, Z);
   glTranslatef(-transfac*ttX, -transfac*ttY, -transfac*ttZ);
   glMultMatrixf(m);
   }

void OpenGLCanvas::doRotation(double dX, double dY) {
    double offX = 2.0*(double)dragX/(double)width-1.0;
    double offY = 1.0-2.0*(double)dragY/(double)height;
    double offZ = 0.25;
    double X, Y, Z, a;
    X = -offZ*dY;
    Y = offZ*dX;
    Z = offX*dY - offY*dX;
    a = 180.*1.5*sqrt(dX*dX + dY*dY)/(PI*winRadius);
    myRotated(a, X, Y, Z);
    return;
    }

void OpenGLCanvas::vcross(double v[3], double w[3], double a[3]) {
   a[0] = v[1]*w[2] - v[2]*w[1];
   a[1] = v[2]*w[0] - v[0]*w[2];
   a[2] = v[0]*w[1] - v[1]*w[0];
   }

//Dot product of two vectors
float OpenGLCanvas::vdot(float v[3], float w[3])
{
  float temp;

  temp = v[0] * w[0] + v[1] * w[1] + v[2] * w[2];

  return temp;
}

void OpenGLCanvas::readFile(const char *file)
{
        maxValue = -10000;
        minValue = 10000;
        short temp;
        int k = 0;
        ifstream myFile;


        makeCurrent();
        myFile.open(file, ios::in|ios::binary);

        while(!myFile.eof())
        {
                myFile.read((char*)&temp, 2);
                data[k] = temp;
                k++;
                if (minValue > temp)
                        minValue = temp;
                if (maxValue < temp)
                        maxValue = temp;

        }
        cout << minValue << " " << maxValue << endl;

        fileIsRead = 1;

        updateTexture3D();
        //reloadShaders();
        paintGL();
        update();
}

void OpenGLCanvas::crossProductPos(float m[16], float v[3], float p[3])
{

    p[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
    p[1] = m[4] * v[0] + m[5] * v[1] + m[6] * v[2];
    p[2] = m[8] * v[0] + m[9] * v[1] + m[10] * v[2];

}

void OpenGLCanvas::drawBox()
{

    float sizex = 0.499f;
    float sizez = 0.499f;
    float sizey = 0.499f;

    makeCurrent();
    glUseProgram(0);

    glBegin(GL_LINES);
                    glColor3f(0, 1, 0);
                    glVertex3f(-0.499,-0.499,-0.499);
                    glVertex3f(-0.499,sizey,-0.499);

                    glColor3f(1, 0, 0);
                    glVertex3f(-0.499,-0.499,-0.499);
                    glVertex3f(sizex,-0.499,-0.499);

                    glColor3f(0, 0, 1);
                    glVertex3f(-0.499,-0.499,-0.499);
                    glVertex3f(-0.499,-0.499,sizez);

                    glColor3f(1, 1, 1);
                    glVertex3f(sizex,sizey,sizez);
                    glVertex3f(sizex,-0.499,sizez);

                    glVertex3f(sizex,sizey,sizez);
                    glVertex3f(sizex,sizey,-0.499);

                    glVertex3f(sizex,sizey,sizez);
                    glVertex3f(-0.499,sizey,sizez);

                    glVertex3f(-0.499,sizey,-0.499);
                    glVertex3f(sizex,sizey,-0.499);

                    glVertex3f(-0.499,sizey,-0.499);
                    glVertex3f(-0.499,sizey,sizez);

                    glVertex3f(sizex,-0.499,sizez);
                    glVertex3f(-0.499,-0.499,sizez);

                    glVertex3f(sizex,-0.499,sizez);
                    glVertex3f(sizex,-0.499,-0.499);

                    glVertex3f(-0.499,-0.499,sizez);
                    glVertex3f(-0.499,sizey,sizez);

                    glVertex3f(sizex,-0.499,-0.499);
                    glVertex3f(sizex,sizey,-0.499);


            glEnd();


}

void OpenGLCanvas::updateTexture3D()
{
    int value;

    delete[] modelTexture;

    modelTexture = new GLubyte[Nz*Ny*Nx];

    for (int i = 0; i < Nz*Ny*Nx; i++)
    {
            value = data[i];
            value = (short)((double)((value - minValue)*255)/(double)(maxValue-minValue));

            modelTexture[i] = (GLubyte) value;

    }

    makeCurrent();

    glGenTextures(2, texName);
    glBindTexture(GL_TEXTURE_3D, texName[0]);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);


    makeCurrent();
    glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, Nx, Ny, Nz-1, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, modelTexture);

    makeColorMap();
}

//Calculate the color for a value of f
void OpenGLCanvas::c(float f, float& R, float& G, float& B)
{
        const float dx = 0.8;
        f = (f<0)? 0 : (f>1)? 1: f;
        float g = (6-2*dx)*f + dx;
        R = max(0.0f,(float)(3-fabs(g-4)-fabs(g-5))/2);
        G = max(0.0f,(float)(4-fabs(g-2)-fabs(g-4))/2);
        B = max(0.0f,(float)(3-fabs(g-1)-fabs(g-2))/2);

}

//Make a color texture.
void OpenGLCanvas::makeColorMap(void)
{
  int j;


  for (j = 0; j < 256; j++)
  {

      gradientTexture[4*j] = (GLubyte) j;
      gradientTexture[4*j+1] = (GLubyte) j;
      gradientTexture[4*j+2] = (GLubyte) j;
      gradientTexture[4*j+3] = (GLubyte) j;
  }

  makeCurrent();

  glBindTexture(GL_TEXTURE_1D, texName[1]);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  makeCurrent();
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, gradientTexture);

  reloadShaders();

  emit updatedTexture(gradientTexture);

}

void OpenGLCanvas::reloadShaders()
{
    makeCurrent();
    QFile fileF;
    if (shader == 0)
        fileF.setFileName("colorMapShader.frag");
    else
        fileF.setFileName("diffuseShader.frag");
    fileF.open(QIODevice::ReadOnly);
    QByteArray arrF = fileF.readAll();
    const char* dataF = arrF.data();
    const int sizeF = arrF.size();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    makeCurrent();
    glShaderSource(fragmentShader, 1, &dataF, &sizeF);
    glCompileShader(fragmentShader);
    GLint compiledF;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiledF);

    if (compiledF != 1)
    {
        qDebug()<< "Shader did not compile correctly!";
    }

    makeCurrent();
    program = glCreateProgram();

    glAttachShader(program, fragmentShader);
    makeCurrent();
    glLinkProgram(program);
    glUseProgram(program);

    GLint texture, colorTexture, trans;

    texture = glGetUniformLocation(program, "volume");
    colorTexture = glGetUniformLocation(program, "lookupTable");
    trans = glGetUniformLocation(program, "sliceTrans");


    glActiveTexture(GL_TEXTURE0 + texName[0]);
    glBindTexture(GL_TEXTURE_3D, texName[0]);
    glUniform1i(texture, texName[0]);

    glActiveTexture(GL_TEXTURE0 + texName[1]);
    glBindTexture(GL_TEXTURE_1D, texName[1]);
    glUniform1i(colorTexture, texName[1]);

    glUniform1f(trans, sliceTrans);

    glUseProgram(program);

}

void OpenGLCanvas::changeSliceTrans(double i)
{
    sliceTrans = i;
}

void OpenGLCanvas::toggleBlend()
{
    makeCurrent();
    if (blending == 0)
    {
        glEnable(GL_BLEND);
        blending = 1;
    }
    else
    {
        glDisable(GL_BLEND);
        blending = 0;
    }

    emit changeBlendButton(blending);
    update();
}

void OpenGLCanvas::normalBlend()
{
    makeCurrent();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendEquationEXT(GL_FUNC_ADD);
    update();
}

void OpenGLCanvas::minusBlend()
{
    makeCurrent();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquationEXT(GL_FUNC_ADD);
    update();
}

void OpenGLCanvas::mipBlend()
{
    makeCurrent();
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquationEXT(GL_MAX_EXT);
    update();
}

void OpenGLCanvas::setDefaultShader()
{
    makeCurrent();
    shader = 0;
    reloadShaders();
    update();
}

void OpenGLCanvas::setDiffuseShader()
{
    makeCurrent();
    shader = 1;
    reloadShaders();
    update();
}

