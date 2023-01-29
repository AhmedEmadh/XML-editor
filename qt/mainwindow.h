#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
using namespace std;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_actionNew_triggered();

        void on_actionOpen_triggered();




        void on_actionExit_triggered();

        void on_actionSave_triggered();

        void on_actionCopy_triggered();

        void on_actionCut_triggered();

        void on_actionPaste_triggered();

        void on_actionUndo_triggered();

        void on_actionRedo_triggered();
         std::string minify(std::string xml);


        std::string  Formating(std::string xml);

        void on_actionSave_as_triggered();

        void on_actionminify_triggered();

        void on_actioncompression_triggered();
        std::string  buildHuffmanTree( std::string text );
        std::string x2json(std::string XMLStr,int level);
        void on_actionformat_triggered();

        void on_actionXMLtoJSON_triggered();

        void on_actionMinify_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile="";

};
#endif // MAINWINDOW_H
