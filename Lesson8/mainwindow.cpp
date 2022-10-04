#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"
#include "viewer.h"
#include "threadfinder.h"

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
//#include <QPrinter>
#include <QPrintDialog>
#include <QDir>
#include <QStatusBar>

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

    if (QSysInfo::productType() == "windows") // Для ОС Windows
    {
        QFileInfoList infolist = QDir::drives();
        int amount = infolist.count();
        for (int i = 0; i < amount; i++)
        {
            ui->selDrive->addItem(infolist.at(i).path());
        }
    }
    else { // Для UNIX-подобных систем
        QStringList str = {"/", "/home/", "/mount/", "/opt/"};
        int amount = str.count();
        for (int i = 0; i < amount; i++)
        {
            ui->selDrive->addItem(str.at(i));
        }
    }
    //****************
    connect(ui->startFindButton, SIGNAL(clicked()), this, SLOT(findFileSlot()));
    controllerl = new Controller(this);
    statusLabel = new QLabel(this);
    QStatusBar *statusBar = this->statusBar();
    statusBar->addWidget(statusLabel);
    connect(controllerl, SIGNAL(changFindPath(QString)), this,
            SLOT(changStatusLabel(QString)));
    connect(controllerl, SIGNAL(genPathOfFile(QString)), this,
            SLOT(printFindFile(QString)));
    connect(controllerl, SIGNAL((newFind())), ui->infoText, SLOT(clear()));
}
MainWindow::~MainWindow(){

    delete ui;
}
void MainWindow::init(){

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
}

void MainWindow::insertDate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QTime time = dateTime.time();
    QDate date = dateTime.date();
    const QString month[] = {"", " января " , " февраля ", " марта ",
                             " апреля ", " мая ", " июня ",
                             " июля ", " августа ", " сентября ",
                             " октября ", " ноября ", " декабря ",
                            }; // Месяцы отсчитываются от 1, поэтому первый
    // элемент - пустая строка
    QString dstr = QString::number(date.day()) + month[date.month()] +
            QString::number(date.year()) + " " + QString::number(time.hour()) + ":" + QString::number(time.minute());
    ui->textEdit->textCursor().insertText(dstr);
    ui->textEdit->setFocus();
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
    ui->textEdit->setFocus();
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
    ui->actionNew->setText("New");
    ui->actionLight->setText("Light");
    ui->actionClose->setText("Close");
    ui->actionDark->setText("Dark");
    ui->actionOpen->setText("Open");
    ui->actionSave->setText("Save");
    ui->actionPrint->setText("Print");
    ui->actionReadOnly->setText("Read only");
    ui->actionEng->setText("English");
    ui->actionRu->setText("Russian");
    ui->actionHelp->setText("Help");
    ui->menuMain->setTitle("File");
    ui->menuLang->setTitle("Language");
    ui->menuOpen->setTitle("Open");
    ui->menuStyle->setTitle("Style");
    ui->menuHelp->setTitle("Help");
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
    ui->actionNew->setText("Создать");
    ui->actionLight->setText("Светлая");
    ui->actionClose->setText("Закрыть");
    ui->actionDark->setText("Темная");
    ui->actionOpen->setText("Открыть");
    ui->actionSave->setText("Сохранить");
    ui->actionPrint->setText("Печать");
    ui->actionReadOnly->setText("Только для чтения");
    ui->actionEng->setText("Английский");
    ui->actionRu->setText("Русский");
    ui->actionHelp->setText("Справка");
    ui->menuMain->setTitle("Файл");
    ui->menuLang->setTitle("Язык");
    ui->menuOpen->setTitle("Открыть");
    ui->menuStyle->setTitle("Стиль");
    ui->menuHelp->setTitle("Справка");
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
void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog* pPrintDialog = new QPrintDialog(&printer);
    if(pPrintDialog->exec() == QDialog::Accepted) {

    }
    delete pPrintDialog;
}
void MainWindow::on_actionNew_triggered()
{
    on_new_pushButton_pressed();
}
void MainWindow::on_actionOpen_triggered()
{
    on_open_pushButton_pressed();
}
void MainWindow::on_actionReadOnly_triggered()
{
    on_openRead_pushButton_clicked();
}
void MainWindow::on_actionSave_triggered()
{
    on_save_pushButton_pressed();
}
void MainWindow::on_actionClose_triggered()
{
    on_close_pushButton_pressed();
}
void MainWindow::on_actionLight_triggered()
{
    on_radioButtonLight_clicked();
}
void MainWindow::on_actionDark_triggered()
{
    on_radioButtonDark_clicked();
}
void MainWindow::on_actionRu_triggered()
{
    on_radioBtnRU_clicked();
}
void MainWindow::on_actionHelp_triggered()
{
    on_help_pushButton_pressed();
}
void MainWindow::on_actionEng_triggered()
{
    on_radioBtnENG_clicked();
}

void MainWindow::sizeFont()
{
    QTextCharFormat fmt;

}

void MainWindow::setFont()
{
    QFont font = ui->textEdit->textCursor().charFormat().font(); // получаем текущий шрифт
    QFontDialog fntDlg(font,this);
    bool b[] = {true};
    font = fntDlg.getFont(b); // Запускаем диалог настройки шрифта
    if (b[0]) // Если нажата кнопка OK, применяем новые
        // настройки шрифта
    {
        QTextCharFormat fmt;
        fmt.setFont(font);
        ui->textEdit->textCursor().setCharFormat(fmt);

    }
}

void MainWindow::copyStyle()
{
    copyFont = ui->textEdit->textCursor().charFormat().font();
    copyForeground = ui->textEdit->textCursor().charFormat().foreground();
    copyBackground = ui->textEdit->textCursor().charFormat().background();
}

void MainWindow::pasteStyle()
{
    QTextCharFormat fmt;
    fmt.setFont(copyFont);
    fmt.setForeground(copyForeground);
    fmt.setBackground(copyBackground);
    ui->textEdit->textCursor().setCharFormat(fmt);
    ui->textEdit->textCursor().charFormat().setFont(copyFont);
}
void MainWindow::on_pushButtonFont_clicked()
{
    setFont();
}
void MainWindow::on_pushButtonAlignLeft_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}
void MainWindow::on_pushButtonAlignMid_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}
void MainWindow::on_pushButtonAlignRight_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}
void MainWindow::on_pushButtonCopyStyle_clicked()
{
    copyStyle();
}
void MainWindow::on_pushButtonPasteStyle_clicked()
{
    pasteStyle();
}


void MainWindow::on_date_pushButton_clicked()
{
    insertDate();
}

void MainWindow::findFileSlot()
{
    QString linesearch = ui->searchEdit->text();
    if (linesearch.length() == 0) return;
    controllerl->startFind(ui->selDrive->currentText(), linesearch);

}

void MainWindow::changStatusLabel(QString line)
{
    statusLabel->setText(line);
}

void MainWindow::printFindFile(QString str)
{
    ui->infoText->append(str);
}

