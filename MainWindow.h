#ifndef __MainWindow_h__
#define __MainWindow_h__


#include <QMainWindow>
#include <vector>
#include <string.h>
using namespace std;



class QAction;


#define ERR_OPENGL_NOT_SUPPORTED 1

namespace Ui{
    class mainWindowGui;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

   public:
      MainWindow(QWidget* pQW_Parent=NULL);


   signals:
    void refresh();


   protected:
      void closeEvent(QCloseEvent* pQCE);
      void updateList();


   private slots:
      void _FileOpen();
      void _Exit();
      //void CanvasSizeChanged(QSize QS_NewSize);
      void renderSingleSlice();
      void renderAxisSlice();
      void renderViewSlice();
      void toggleBlendingButton(bool a);




   private:
      void _CheckOpenGL();

      Ui::mainWindowGui *myGui;



      // Actions
      QAction* _pQA_File_Open;
      QAction* _pQA_File_Exit;
};

#endif // __MainWindow_h__
