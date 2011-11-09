#ifndef COLORMAP_H
#define COLORMAP_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include "structs.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
using namespace std;

class colormap : public QGLWidget
{
    Q_OBJECT
public:
    colormap(QWidget *parent);

public slots:
    void updateMap(GLubyte *tex);
    void updateNode(color node);
    void setNodeRed(int red);
    void setNodeBlue(int blue);
    void setNodeGreen(int green);
    void setNodeAlpha(int alpha);
    void refresh();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setAlpha(int alpha);
    void sendTexture(color* map);

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void updateStops();
    float interpolate(float low, int lowPos, float high, int hiPos, int pos);
    void buildMap();

    color currMap[256];
    //float alpha[256];
    //int stops[5];
    //color stopsColor[5];
    float alphaStops[5];
    vector<colorPoint> stops;
    int numStops;
    int currStop;

};

#endif // COLORMAP_H
