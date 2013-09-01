#include <QtGui>
#include <QApplication>
#include "mainwindow.h"
#include <QMetaObject>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    
    return a.exec();
}
