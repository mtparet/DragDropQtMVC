#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QMetaObject>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();

    
    return a.exec();
}
