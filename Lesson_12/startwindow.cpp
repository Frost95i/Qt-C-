#include "startwindow.h"

startWindow::startWindow(QWidget *parent)
    : QWidget(parent)
{
    mainGrid = new QGridLayout (this);
    buttonOne = new QPushButton (this);


    downloadManager = new DownloaderManager (this);
    downloadManager->setWindowFlag(Qt::Window);

    buttonOne->setText("Поиск");

    mainGrid->addWidget(buttonOne, 1, 1, 1, 1);

    connect(buttonOne, SIGNAL(clicked()), this, SLOT(buttonOne_clicked()));


    this->setLayout(mainGrid);
}

void startWindow::buttonOne_clicked()
{
    downloadManager->resize(QSize(500, 100));
    downloadManager->show();
}


