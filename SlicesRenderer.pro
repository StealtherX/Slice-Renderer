# -------------------------------------------------
# Project created by QtCreator 2011-03-02T15:06:06
# -------------------------------------------------
QT += opengl
TARGET = SlicesRenderer
TEMPLATE = app
SOURCES += main.cpp \
    MainWindow.cpp \
    OpenGLCanvas.cpp \
    colormap.cpp
HEADERS += MainWindow.h \
    MainWindow.h \
    OpenGLCanvas.h \
    colormap.h \
    structs.h
FORMS += mainwindow.ui
OTHER_FILES += colorMapShader.frag \
    diffuseShader.frag
