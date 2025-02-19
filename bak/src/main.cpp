#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    function_trace();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
