#############################################################################
# Makefile for building: SlicesRenderer
# Generated by qmake (2.01a) (Qt 4.7.4) on: Thu Nov 3 14:12:03 2011
# Project:  SlicesRenderer.pro
# Template: app
# Command: /home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/qmake -spec ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/linux-g++-32 CONFIG+=debug -o Makefile SlicesRenderer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -m32 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m32 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/linux-g++-32 -I. -I../../../QtSDK/Desktop/Qt/474/gcc/include/QtCore -I../../../QtSDK/Desktop/Qt/474/gcc/include/QtGui -I../../../QtSDK/Desktop/Qt/474/gcc/include/QtOpenGL -I../../../QtSDK/Desktop/Qt/474/gcc/include -I/usr/X11R6/include -I. -I.
LINK          = g++
LFLAGS        = -m32 -Wl,-rpath,/home/kevin/QtSDK/Desktop/Qt/474/gcc/lib
LIBS          = $(SUBLIBS)  -L/home/kevin/QtSDK/Desktop/Qt/474/gcc/lib -L/usr/X11R6/lib -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		MainWindow.cpp \
		OpenGLCanvas.cpp \
		colormap.cpp moc_MainWindow.cpp \
		moc_OpenGLCanvas.cpp \
		moc_colormap.cpp
OBJECTS       = main.o \
		MainWindow.o \
		OpenGLCanvas.o \
		colormap.o \
		moc_MainWindow.o \
		moc_OpenGLCanvas.o \
		moc_colormap.o
DIST          = ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/g++.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/linux.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf \
		SlicesRenderer.pro
QMAKE_TARGET  = SlicesRenderer
DESTDIR       = 
TARGET        = SlicesRenderer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: SlicesRenderer.pro  ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/linux-g++-32/qmake.conf ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/g++.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/linux.conf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf \
		../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/linux-g++-32 CONFIG+=debug -o Makefile SlicesRenderer.pro
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/g++.conf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/linux.conf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf:
../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf:
qmake:  FORCE
	@$(QMAKE) -spec ../../../QtSDK/Desktop/Qt/474/gcc/mkspecs/linux-g++-32 CONFIG+=debug -o Makefile SlicesRenderer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/SlicesRenderer1.0.0 || $(MKDIR) .tmp/SlicesRenderer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/SlicesRenderer1.0.0/ && $(COPY_FILE) --parents MainWindow.h MainWindow.h OpenGLCanvas.h colormap.h structs.h .tmp/SlicesRenderer1.0.0/ && $(COPY_FILE) --parents main.cpp MainWindow.cpp OpenGLCanvas.cpp colormap.cpp .tmp/SlicesRenderer1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/SlicesRenderer1.0.0/ && (cd `dirname .tmp/SlicesRenderer1.0.0` && $(TAR) SlicesRenderer1.0.0.tar SlicesRenderer1.0.0 && $(COMPRESS) SlicesRenderer1.0.0.tar) && $(MOVE) `dirname .tmp/SlicesRenderer1.0.0`/SlicesRenderer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/SlicesRenderer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainWindow.cpp moc_MainWindow.cpp moc_OpenGLCanvas.cpp moc_colormap.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainWindow.cpp moc_MainWindow.cpp moc_OpenGLCanvas.cpp moc_colormap.cpp
moc_MainWindow.cpp: MainWindow.h
	/home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

moc_MainWindow.cpp: MainWindow.h
	/home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

moc_OpenGLCanvas.cpp: structs.h \
		OpenGLCanvas.h
	/home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) OpenGLCanvas.h -o moc_OpenGLCanvas.cpp

moc_colormap.cpp: structs.h \
		colormap.h
	/home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) colormap.h -o moc_colormap.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui \
		OpenGLCanvas.h \
		colormap.h \
		structs.h \
		structs.h
	/home/kevin/QtSDK/Desktop/Qt/474/gcc/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

MainWindow.o: MainWindow.cpp MainWindow.h \
		ui_mainwindow.h \
		OpenGLCanvas.h \
		structs.h \
		colormap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o MainWindow.cpp

OpenGLCanvas.o: OpenGLCanvas.cpp OpenGLCanvas.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o OpenGLCanvas.o OpenGLCanvas.cpp

colormap.o: colormap.cpp colormap.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o colormap.o colormap.cpp

moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainWindow.o moc_MainWindow.cpp

moc_OpenGLCanvas.o: moc_OpenGLCanvas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_OpenGLCanvas.o moc_OpenGLCanvas.cpp

moc_colormap.o: moc_colormap.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_colormap.o moc_colormap.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

