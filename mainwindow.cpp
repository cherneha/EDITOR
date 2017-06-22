#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(resendValues()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(resendValuesPrism()));
    connect(ui->xRotate, SIGNAL(clicked(bool)), this, SLOT(resendDegreeX()));
    connect(ui->rotateY, SIGNAL(clicked(bool)), this, SLOT(resendDegreeY()));
    connect(ui->rotateZ, SIGNAL(clicked(bool)), this, SLOT(resendDegreeZ()));
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

    emit ui->openGLWidget->addPrism(p1, p2, p3, p4, ui->prismHeights->value());
}

void MainWindow::labelEdit(int p)
{
    QString s = QString::number(p);
    ui->chosenNum->setText(s);
}

void MainWindow::resendDegreeY()
{
    int deg = ui->spinBox->value();
    emit ui->openGLWidget->rotateChosenYAxis(deg);
}

void MainWindow::resendDegreeX()
{
    int deg = ui->spinBox->value();
    emit ui->openGLWidget->rotateChosenXAxis(deg);
}

void MainWindow::resendDegreeZ()
{
    int deg = ui->spinBox->value();
    emit ui->openGLWidget->rotateChosenZAxis(deg);
}

void MainWindow::on_color_clicked()
{
    QColor figureColor = QColorDialog::getColor(Qt::black, this);
    if(figureColor.isValid()){
        QList <GLfloat> colors ({(float)figureColor.red()/255.0, (float)figureColor.green()/255.0, (float)figureColor.blue()/255.0, 1.0});
        emit ui->openGLWidget->changeColors(&colors);
    }
}

void MainWindow::on_ResizePlus_clicked()
{
    emit ui->openGLWidget->changeSize(1);
}

void MainWindow::on_ResizeMinus_clicked()
{
    emit ui->openGLWidget->changeSize(0);
}

void MainWindow::on_restoreFromDB_clicked()
{
    // file open dialog

    QFileDialog *dialog = new QFileDialog(this);
    dialog->setNameFilter(tr("Database (*.sqlite)"));

    dialog->setFileMode(QFileDialog::ExistingFile);
    QString file;
    if(dialog->exec()){
        file = dialog->selectedFiles().at(0);
    }
    if(file == ui->openGLWidget->db){
        qDebug() << "this database is just created!";
        return;
    }

    // declaring and opening database

        QSqlDatabase dbToRestore = QSqlDatabase::addDatabase("QSQLITE", "readFrom");
        dbToRestore.setDatabaseName(file);

    if (!dbToRestore.open())
       {
          qDebug() << "Error: connection with database fail " << dbToRestore.lastError();
       }
       else
       {
          qDebug() << "Database: connection ok";
       }

QSqlQuery getInfoQuery(dbToRestore);
QSqlQuery  getPrismsQuery(dbToRestore);

        // getting data Cones

        if(!getInfoQuery.exec("SELECT id, r1, r2, heights, dotX, dotY, dotZ FROM cones")){
            qDebug() << getInfoQuery.lastError();
        }
        while(getInfoQuery.next())  {
            dbToRestore.close();
            emit ui->openGLWidget->addNewCone(getInfoQuery.value(4).toDouble(), getInfoQuery.value(5).toDouble(),
                                              getInfoQuery.value(6).toDouble(), getInfoQuery.value(2).toDouble(),
                                              getInfoQuery.value(1).toDouble(), getInfoQuery.value(3).toDouble());

             dbToRestore.open();
            }

            if(!getPrismsQuery.exec("SELECT dot1X, dot1Y, dot1Z, dot2X, dot2Y, dot2Z,"
                                  "dot3X, dot3Y, dot3Z, dot4X, dot4Y, dot4Z, heights FROM prism")){
                qDebug() << getPrismsQuery.lastError();
            }

     //getting data Prisms

      while(getPrismsQuery.next()) {
            emit ui->openGLWidget->addPrism(new Dot(getPrismsQuery.value(0).toDouble(), getPrismsQuery.value(1).toDouble(), getPrismsQuery.value(2).toDouble()),
                                      new Dot(getPrismsQuery.value(3).toDouble(), getPrismsQuery.value(4).toDouble(), getPrismsQuery.value(5).toDouble()),
                                      new Dot(getPrismsQuery.value(6).toDouble(), getPrismsQuery.value(7).toDouble(), getPrismsQuery.value(8).toDouble()),
                                      new Dot(getPrismsQuery.value(9).toDouble(), getPrismsQuery.value(10).toDouble(), getPrismsQuery.value(11).toDouble()),
                                      getPrismsQuery.value(12).toInt());
      }

    dbToRestore.close();


  }
