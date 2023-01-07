#include "mainwindow.h"
#include <QQmlApplicationEngine>
#include <QApplication>
#include "TaskClass.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<TaskClass>("com.workclass", 1,0, "WorkClass");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
