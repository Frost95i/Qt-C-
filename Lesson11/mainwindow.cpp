#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    viewqml = new QQuickView();
    container = QWidget::createWindowContainer(viewqml, this);
    viewqml->setSource(QUrl("qrc:/main.qml"));
    this->setCentralWidget(container);
    container->setMinimumSize(450,300);
    container->setMaximumSize(450,300);
}

MainWindow::~MainWindow()
{
    delete viewqml;
    delete container;
}

