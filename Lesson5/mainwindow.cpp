#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"
#include "viewer.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QLibraryInfo>
#include <QEvent>
#include <QClipboard>
#include <QShortcut>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      openedFileName("")
{
    ui->setupUi(this);
    init();
    this->setStyleSheet("QPushButton {background-color: lightGray; color: black;} "
                        "QMainWindow{background-color:gray;}"
                        "QRadioButton {color: black}"
                        "QTextEdit {background-color: white; color: black;}"
                        "QGroupBox {color: black};"
                        "QCursor {color: red};");


    this->aDirList = new QFileInfoList();

    this->model = new QListViewExplorerModel();

    this->currentFolder = QDir(QDir::currentPath());

    this->model->getFolderList(this->currentFolder.absolutePath(),this->aDirList);


    this->ui->listView->setModel(model);

    this->ui->lineEdit->setText(QDir::currentPath());

    this->ui->listView->setWordWrap(true);
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
    ui->groupBox->setTitle("Control");
    ui->groupBoxLang->setTitle("Language");
    ui->groupBoxStyle->setTitle("Style");
    ui->radioButtonDark->setText("Dark");
    ui->radioButtonLight->setText("Light");
}


void MainWindow::on_radioBtnRU_clicked()
{
    ui->new_pushButton->setText("Создать");
    ui->open_pushButton->setText("Открыть");
    ui->openRead_pushButton->setText("Открыть для чтения");
    ui->save_pushButton->setText("Сохранить");
    ui->close_pushButton->setText("Закрыть");
    ui->help_pushButton->setText("Справка");
    ui->groupBox->setTitle("Управление");
    ui->groupBoxLang->setTitle("Язык");
    ui->groupBoxStyle->setTitle("Стиль");
    ui->radioButtonDark->setText("Темная");
    ui->radioButtonLight->setText("Светлая");
}


void MainWindow::on_openRead_pushButton_clicked()
{
    currentFileSave();
    FileOpenReadOnly();

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(false);
}


void MainWindow::on_radioButtonLight_clicked()
{
    this->setStyleSheet("QPushButton {background-color: lightGray; color: black;} "
                        "QMainWindow{background-color:gray;}"
                        "QRadioButton {color: black}"
                        "QTextEdit {background-color: white; color: black;}"
                        "QGroupBox {color: black};"
                        "QCursor {color: red};"
                        "QLineEdit {background-color: white; color: black;}"
                        "QListView {background-color: white;}");
}


void MainWindow::on_radioButtonDark_clicked()
{
   this->setStyleSheet("QPushButton {background-color: lightGray; color: black;} "
                       "QMainWindow{background-color: black;}"
                       "QRadioButton {color: white}"
                       "QTextEdit {background-color: lightGray; color: black;}"
                       "QGroupBox {color: white};"
                       "QCursor {color: red};"
                       "QLineEdit {background-color: lightGray; color: black;}"
                       "QListView {background-color: lightGray;}");
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (this->aDirList->at(index.row()).isDir())
    {
        QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
        model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(),this->aDirList);
        this->ui->lineEdit->setText(tmp);
    } else {
        QDesktopServices::openUrl(QUrl(this->aDirList->at(index.row()).absoluteFilePath()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    currentFolder.cdUp();

    this->ui->lineEdit->setText(currentFolder.absolutePath());
    model->getFolderList(currentFolder.absolutePath(),this->aDirList);
}


void MainWindow::on_pushButton_3_clicked()
{
    this->ui->listView->setUniformItemSizes(false);
    this->ui->listView->setViewMode(QListView::ListMode);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->ui->listView->setUniformItemSizes(true);
    this->ui->listView->setViewMode(QListView::IconMode);
}
