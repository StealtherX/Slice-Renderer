#include "MainWindow.h"


#include <QApplication>
#include <QCloseEvent>
#include <QFileDialog>
#include <QGLFormat>
#include <QMenuBar>  // <QMenu>, <QAction>
#include <QMessageBox>
#include <QMessageBox>
#include <QString>
#include <fstream>
#include <stdlib.h>
#include <cmath>

#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget* pQW_Parent)
   : QMainWindow(pQW_Parent)
{
   // Check OpenGL support
   _CheckOpenGL();

   // Create GUIs
   myGui = new Ui::mainWindowGui();
   myGui->setupUi(this);



}

void MainWindow::_CheckOpenGL()
{
   // Check OpenGL support
   if(!QGLFormat::hasOpenGL())
   {
      qCritical("Error: This program requires OpenGL!");

      exit(ERR_OPENGL_NOT_SUPPORTED);
   }
}


void MainWindow::closeEvent(QCloseEvent* pQCE)
{
   QMessageBox::StandardButton QMB_SB_Choice=QMessageBox::warning(this, "Slice Renderer", "Do you really want to quit this application?", QMessageBox::Yes|QMessageBox::No);

   if(QMessageBox::Yes==QMB_SB_Choice)
   {
      pQCE->accept();

      _Exit();
   }
   // else if(QMessageBox::No==QMB_SB_Choice)
   {
      pQCE->ignore();

      return;
   }
}

void MainWindow::_Exit()
{
   qApp->quit();
}

void MainWindow::_FileOpen()
{
    string name;
   // TODO: More than one file?
   const QString& kQStr_FileName=QFileDialog::getOpenFileName(this, "Select a data file", ".", "Datasets (*)");

   if(!kQStr_FileName.isEmpty())
   {
      //emit openTheFile(kQStr_FileName);

   }
   else // i.e. cQStr_FileName.isEmpty()
   {
      qWarning("Warning: No file selected!");
      return;
   } // if(!kQStr_FileName.isEmpty())




   name = kQStr_FileName.toStdString();

   myGui->graphics->readFile(name.c_str());

}

void MainWindow::renderSingleSlice()
{
    myGui->graphics->settings = 0;
    emit refresh();
}

void MainWindow::renderAxisSlice()
{
    myGui->graphics->settings = 1;
    emit refresh();
}

void MainWindow::renderViewSlice()
{
    myGui->graphics->settings = 2;
    emit refresh();


}

void MainWindow::toggleBlendingButton(bool a)
{
    if (a)
    {
        myGui->pushButton_5->setText(QString("Enabled"));
    }
    else
        myGui->pushButton_5->setText(QString("Disabled"));
}




