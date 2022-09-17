#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      openedFileName("")
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::init(){

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
}

void MainWindow::currentFileSave(){

    if(!ui->textEdit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Сохранить файл", "Сохранить текущий файл перед закрытием?", QMessageBox::Yes | QMessageBox::No);
        if (QMessageBox::Yes == reply)
        {
            if (!openedFileName.isEmpty())
            {
                FileSave();
            }
        }
    }
}

void MainWindow::FileSave(){

    QString str = QFileDialog::getSaveFileName(this, "Сохранить", QDir::current().path(), "*.txt");
    if (str.length() > 0)
    {
        QString ext = QString(&(str.data()[str.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(str);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                openedFileName = str;
            }
        }
    }
}


void MainWindow::FileOpen(){

    QString str = QFileDialog::getOpenFileName(this, "Открыть файл", QDir::current().path(), filter);
    if (str.length() > 0)
    {
        int index = str.indexOf(".txt");
        QFile file(str);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && str.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                openedFileName = str;
                file.close();
            }
        }
    }
}

void MainWindow::on_new_pushButton_pressed(){

    currentFileSave();
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
    ui->textEdit->clear();
    openedFileName = "text";
}

void MainWindow::on_close_pushButton_pressed(){

    currentFileSave();
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
    ui->textEdit->clear();
    openedFileName = "";
    close();
}

void MainWindow::on_open_pushButton_pressed(){

    currentFileSave();
    FileOpen();

    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
}

void MainWindow::on_save_pushButton_pressed(){

    FileSave();
}


void MainWindow::on_help_pushButton_pressed(){
    HelpForm* help = new HelpForm(this);
    if(help){

        help->show();
    }
}

