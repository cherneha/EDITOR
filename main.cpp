#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QApplication::setDesktopSettingsAware(false);
    w.show();

    return a.exec();
}
