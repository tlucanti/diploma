#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

