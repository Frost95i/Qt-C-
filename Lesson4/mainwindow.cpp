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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_N){
        on_new_pushButton_pressed();
    }

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_O){
        FileOpen();
    }

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S){
        FileSave();
    }

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Q){
        on_close_pushButton_pressed();
    }
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


void MainWindow::FileOpenReadOnly(){

    QString str = QFileDialog::getOpenFileName(this, "Открыть файл", QDir::current().path(), filter);
    if (str.length() > 0)
    {
        int index = str.indexOf(".txt");
        QFile file(str);
        if (file.open(QIODevice::ReadOnly))
        {
           QByteArray byteArray = file.readAll();
           ui->textEdit->setPlainText(byteArray.data());
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


void MainWindow::on_radioBtnENG_clicked()
{
    ui->new_pushButton->setText("New");
    ui->open_pushButton->setText("Open");
    ui->openRead_pushButton->setText("Open read only");
    ui->save_pushButton->setText("Save");
    ui->close_pushButton->setText("Close");
    ui->help_pushButton->setText("Help");
}


void MainWindow::on_radioBtnRU_clicked()
{
    ui->new_pushButton->setText("Создать");
    ui->open_pushButton->setText("Открыть");
    ui->openRead_pushButton->setText("Открыть для чтения");
    ui->save_pushButton->setText("Сохранить");
    ui->close_pushButton->setText("Закрыть");
    ui->help_pushButton->setText("Справка");
}


void MainWindow::on_openRead_pushButton_clicked()
{
    currentFileSave();
    FileOpenReadOnly();

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(false);
}

