#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Lesson5");
    w.show();
    return a.exec();
}
