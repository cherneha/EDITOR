#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "theglwidget.h"
//#include "ui_mainwindow.h"
#include <string>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

  //  void on_pushButton_3_clicked();

  //  void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

private slots:
    void resendValues();
    void resendValuesPrism();
    void labelEdit(int);
    void resendDegreeY();
    void resendDegreeX();
    void resendDegreeZ();
    void on_color_clicked();
    void on_ResizePlus_clicked();
    void on_ResizeMinus_clicked();
};

#endif // MAINWINDOW_H
