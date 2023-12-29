#include "mainwindow.h"
#include <fstream>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::string filePath = "dontcares.txt";

    std::ofstream file(filePath);
    file.close();

    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

    MainWindow w;
    w.show();

    return a.exec();
}
