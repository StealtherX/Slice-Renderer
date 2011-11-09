#include "colormap.h"

colormap::colormap(QWidget *parent) : QGLWidget(parent)
{

    colorPoint temp;
    for (int i = 0; i < 256; i++)
    {
        currMap[i].red = 0;
        currMap[i].green = 0;
        currMap[i].blue = 0;
        currMap[i].alpha = 0;

    }

    numStops = 2;
    temp.pos = 0;
    currStop = 0;
    temp.red = 0;
    temp.green = 0;
    temp.blue = 0;
    temp.alpha = 0;

    stops.push_back(temp);

    temp.pos = 256;
    temp.red = 1;
    temp.green = 1;
    temp.blue = 1;
    temp.alpha = 1;
    stops.push_back(temp);

    buildMap();


    updateGL();
}


void colormap::initializeGL()
{

    glClearColor(0, 0, 0, 1);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_3D);
    glDisable(GL_TEXTURE_2D);

    return;

}

void colormap::resizeGL(int w, int h)
{
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 255, 0, 3);
    glMatrixMode(GL_MODELVIEW);

    return;


}

void colormap::paintGL()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_TEXTURE_3D);
    glDisable(GL_TEXTURE_2D);

    glLoadIdentity();
    glColor4f(1,1,1,1);
    glBegin(GL_QUAD_STRIP);
        glColor4f(0,0,0,1);
        glVertex2f(-1,1);
        glVertex2f(-1,2);

        for (int i = 0; i < 256; i++)
        {
            glColor3f(currMap[i].red, currMap[i].green, currMap[i].blue);
            glVertex2f(i, 1);
            glVertex2f(i, 2);
        }

        glColor3f(0,0,0);
        glVertex2f(256, 1);
        glVertex2f(256, 2);
    glEnd();
makeCurrent();
    glBegin(GL_QUAD_STRIP);
       glColor4f(0,0,0,0);
       glVertex2f(-1,2);
       glVertex2f(-1,3);

        for (int i = 0; i < 256; i++)
        {
            glColor4f(1, 1, 1, currMap[i].alpha);
            glVertex2f(i, 2);
            glVertex2f(i, 3);
        }

        glColor4f(0,0,0,0);
        glVertex2f(256, 2);
        glVertex2f(256, 3);
    glEnd();

    updateStops();


}

void colormap::updateMap(GLubyte *tex)
{
    for (int i = 0; i < 256; i++)
    {
        currMap[i].red = (float)tex[4*i] / 256.0f;
        currMap[i].green = (float)tex[4*i + 1] / 256.0f;
        currMap[i].blue = (float)tex[4*i + 2] / 256.0f;
        currMap[i].alpha = (float)tex[4*i + 3] / 256.0f;
    }

    update();

}

void colormap::updateStops()
{
   makeCurrent();
    for (unsigned int i = 0; i < stops.size(); i++)
    {
        if ((int)i == currStop)
            glColor4f(0.0, 1.0, 1.0, 1.0);
        else
            glColor4f(1.0,1.0,1.0,1.0);

        glBegin(GL_TRIANGLES);
                glVertex2f(stops[i].pos, 1);
                glVertex2f(stops[i].pos+5, 0);
                glVertex2f(stops[i].pos-5, 0);
        glEnd();
    }
}

void colormap::mousePressEvent(QMouseEvent *event)
{
    bool found = false;
    float pos = event->x() / float(this->width());
    pos *= 256;

    for (unsigned int i = 0; i < stops.size(); i++)
    {
        if (pos < stops[i].pos + 5 && pos > stops[i].pos - 5)
        {
            currStop = i;
            emit (setRed(stops[currStop].red*255));
            emit (setGreen(stops[currStop].green*255));
            emit (setBlue(stops[currStop].blue*255));
            emit (setAlpha(stops[currStop].alpha*255));
            found = 1;
            break;
        }
    }


    if (!found && event->button() == Qt::LeftButton)
    {
            for (unsigned int i = 1; i < stops.size(); i++)
            {
                if (stops[i].pos > pos)
                {
                    colorPoint temp;
                    temp.red = 1;
                    temp.green = 1;
                    temp.blue = 1;
                    temp.alpha = 1;
                    temp.pos = pos;

                    stops.insert(stops.begin() + i, temp);
                    currStop = i;
                    emit (setRed(stops[currStop].red*255));
                    emit (setGreen(stops[currStop].green*255));
                    emit (setBlue(stops[currStop].blue*255));
                    emit (setAlpha(stops[currStop].alpha*255));
                    break;
                }
            }


    }

    if (found && event->button() == Qt::RightButton)
    {
        if ((unsigned int)currStop != stops.size() - 1)
        {
            stops.erase(stops.begin() + currStop);
            currStop--;
            emit (setRed(stops[currStop].red*255));
            emit (setGreen(stops[currStop].green*255));
            emit (setBlue(stops[currStop].blue*255));
            emit (setAlpha(stops[currStop].alpha*255));
        }
    }

    buildMap();
    update();
}

void colormap::mouseMoveEvent(QMouseEvent *event)
{
    float pos = event->x() / float(this->width());
    pos *= 256;

    if(currStop != 0 && (unsigned int)currStop != stops.size() - 1)
    {
        if (pos > stops[currStop-1].pos && pos < stops[currStop+1].pos)
        {
            stops[currStop].pos = pos;
            emit (setRed(stops[currStop].red*255));
            emit (setGreen(stops[currStop].green*255));
            emit (setBlue(stops[currStop].blue*255));
            emit (setAlpha(stops[currStop].alpha*255));
        }
    }

    buildMap();
    update();
}

float colormap::interpolate(float low, int lowPos, float high, int hiPos, int pos)
{
    int width = hiPos - lowPos;
    float leftPercent = float(pos - lowPos) / (float)width;
    float rightPercent = 1.0f - leftPercent;

    return (leftPercent * high) + (rightPercent * low);
}

void colormap::buildMap()
{
    for (unsigned int i = 0; i < stops.size() - 1; i++)
    {
        for (int j = stops[i].pos; j < stops[i+1].pos; j++)
        {
            currMap[j].red = interpolate(stops[i].red, stops[i].pos, stops[i+1].red, stops[i+1].pos, j);
            currMap[j].green = interpolate(stops[i].green, stops[i].pos, stops[i+1].green, stops[i+1].pos, j);
            currMap[j].blue = interpolate(stops[i].blue, stops[i].pos, stops[i+1].blue, stops[i+1].pos, j);
            currMap[j].alpha = interpolate(stops[i].alpha, stops[i].pos, stops[i+1].alpha, stops[i+1].pos, j);
        }
    }

    update();

}

void colormap::updateNode(color node)
{
    stops[currStop].red = node.red;
    stops[currStop].green = node.green;
    stops[currStop].blue = node.blue;
    stops[currStop].alpha = node.alpha;

    buildMap();
    update();
}

void colormap::setNodeRed(int red)
{
    stops[currStop].red = (float)red / 255.0f;

    buildMap();
    update();
}

void colormap::setNodeBlue(int blue)
{
    stops[currStop].blue = (float)blue / 255.0f;

    buildMap();
    update();
}

void colormap::setNodeGreen(int green)
{
    stops[currStop].green = (float)green / 255.0f;

    buildMap();
    update();
}

void colormap::setNodeAlpha(int alpha)
{
    stops[currStop].alpha = (float)alpha / 255.0f;

    buildMap();
    update();
}

void colormap::refresh()
{

    emit sendTexture(currMap);
}

