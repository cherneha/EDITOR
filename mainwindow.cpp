#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(resendValues()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(resendValuesPrism()));
    connect(ui->openGLWidget, SIGNAL(changeLabel(int)), this, SLOT(labelEdit(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resendValues()
{
    emit ui->openGLWidget->addNewCone(ui->cendotX->value(), ui->cendotY->value(), ui->cendotZ->value(), ui->coneBaseRadius->value(), ui->coneTopRadius->value(), ui->coneHeights->value());
}

void MainWindow::resendValuesPrism()
{
    Dot *p1 = new Dot(ui->dot1X->value(), ui->dot1Y->value(), ui->dot1Z->value());
    Dot *p2 = new Dot(ui->dot2X->value(), ui->dot2Y->value(), ui->dot2Z->value());
    Dot *p3 = new Dot(ui->dot3X->value(), ui->dot3Y->value(), ui->dot3Z->value());
    Dot *p4 = new Dot(ui->dot4X->value(), ui->dot4Y->value(), ui->dot4Z->value());
    Prism *toAdd = new Prism(p1, p2, p3, p4, ui->prismHeights->value());
    emit ui->openGLWidget->addPrism(toAdd);
}

void MainWindow::labelEdit(int p)
{
    ui->info->setText("it passes");
}
