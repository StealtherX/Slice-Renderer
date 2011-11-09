#ifndef __OpenGLCanvas_h__
#define __OpenGLCanvas_h__


// NOTE: GL_GLEXT_PROTOTYPES has to be defined before include QGLWidget on Linux boxes
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#endif // __linux__
#include <QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QFile>
#include <iostream>
#include <fstream>
#include <QPoint>
#include "structs.h"
#include <vector>
using namespace std;

#define Nz 113
#define Ny 256
#define Nx 256
#define PI 3.14159265358979323

class QColor;

const double pi = 3.14159;


class OpenGLCanvas : public QGLWidget
{
   Q_OBJECT

   public:
      OpenGLCanvas(QWidget* pQW_Parent=NULL);
      ~OpenGLCanvas();
      void readFile(const char *file);


      short settings;

      QSize minimumSizeHint() const;


   public slots:
      void refreshDraw();
      void updateTexture(color* map);
      void updateSliceNum(int num) {sliceNum = num; paintGL(); update();}
      void changeSliceTrans(double i);
      void toggleBlend();
      void mipBlend();
      void normalBlend();
      void minusBlend();
      void setDefaultShader();
      void setDiffuseShader();


   signals:
      void SizeChanged(QSize QS_NewSize);
      void MousePositionChanged(QPoint QP_NewPosition);
      void progress(int a);
      void updatedTexture(GLubyte *tex);
      void changeBlendButton(bool a);


   protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int iWidth, int iHeight);
      void mousePressEvent(QMouseEvent* pQME_Event);
      void mouseMoveEvent(QMouseEvent* pQME_Event);
      void mouseReleaseEvent(QMouseEvent* pQME_Event);

   private:
      void doTranslation(int tX, int tY, int tZ);
      float findCorrection(float m[16], float w[3]);
      void myRotated(double a, double X, double Y, double Z);
      void doRotation(double dX, double dY);
      void vcross(double v[3], double w[3], double a[3]);
      float vdot(float v[3], float w[3]);
      void crossProductPos(float m[16], float v[3], float p[3]);
      void drawBox();
      void updateTexture3D();
      //Calculate the color for a value of f
      void c(float f, float& R, float& G, float& B);
      void makeColorMap(void);
      void reloadShaders();


      unsigned char* _pucBuffer;
      int bufferSize;
      QPoint _QPt_CurrentPosition;
      int halfWidth;
      int halfHeight;

      int button, state, mousex, mousey, dragX, dragY, cube;
      int width, height, isSpinning, lmax, do_neighbors,tX, tY, tZ, ttX, ttY, ttZ, just_up,tW, ttW;
      double winRadius, dX, dY;
      double tt, transfac, rad, sumx, sumy, sumz;
      double xxmin, xxmax, ymin, ymax, zmin, zmax, large;
      clock_t ticks1, ticks2, ticks3, ticks4;
      int iterations, delay;
      int use_checkImage, single_slice;
      float mm[16];
      bool fileIsRead;




      short data[Nz*Ny*Nx];
      GLubyte *modelTexture;
      GLubyte *gradientTexture;
      short maxValue;
      short minValue;


      float sliceZ;
      int sliceNum;
      float sliceTrans;
      bool blending;
      int shader;

      GLuint texName[2];
      GLuint lookupTex;
      GLuint fragmentShader;
      GLuint program;


};

#endif // __OpenGLCanvas_h__
