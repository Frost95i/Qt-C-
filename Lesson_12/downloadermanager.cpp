#include "downloadermanager.h"
#include <QMessageBox>
#include <QFile>
#include <QLabel>
#include <QRandomGenerator>
#include <algorithm>
#include <iostream>

DownloaderManager::DownloaderManager(QWidget *parent)
    : QWidget{parent}
{
    mainGrid = new QGridLayout (this);
    btn = new QPushButton ("->", this);
    le = new QLineEdit(this);
    le->setText("кот");
    QLabel *lb = new QLabel{"Введите запрос:", this};



    mainGrid->addWidget(lb, 0,0,1,3);
    mainGrid->addWidget(le, 1, 0, 1, 2);
    mainGrid->addWidget(btn, 1, 2);

    connect(btn, &QPushButton::clicked, this, &DownloaderManager::on_pushButton_btn);


    this->setLayout(mainGrid);
}

void DownloaderManager::showPixMap(const QString &path)
{
    Downloader *downloadPix = new Downloader(this);
    connect(downloadPix, SIGNAL(done(const QUrl&, const QByteArray&)),
            this, SLOT(doneDownloadPix(const QUrl&, const QByteArray&)));
    downloadPix->download(path);
}

void DownloaderManager::parseQuery(const QString path, const int count)
{
    QFile file(path); //взяли 1 секцию с конца, т.е. имя файла с расширением
    if (!file.open(QIODevice::ReadOnly)) return;
    QString file_str = file.readAll();
    file.close();

    //собираем рандомные номера картинок, чтобы не выводилиь одинаковые разных размеров
    std::srand( time( 0 ) );
    QList<int> list;
    for (int i=0; i < count ;i++ ) {
        int value = std::rand() % (count*10);
        list << value;
    }
    std::sort(list.begin(), list.end());
    qDebug() << list;

    long long newPosPix = 0;
    int numberLink = 0;

    for (int i = 0;i < count ; i++ ) {
        newPosPix = file_str.indexOf("\"url\":\"", newPosPix) + 7;
        qDebug() << "Номер позиции: " + QString::number(newPosPix) + " символ: [" + file_str[newPosPix] + "]";
        if(newPosPix == -1) return;
        QString urlPixMap;

        do {
            urlPixMap += file_str[newPosPix];
            newPosPix++;
        }   while (file_str[newPosPix] != '\"');

        if(urlPixMap.indexOf(".jpg") == -1) {i--; continue;}
        if(numberLink == list[i]) {
            qDebug() << urlPixMap;
            showPixMap(urlPixMap);
        } else {
            numberLink++;
            i--;
        }
    }
}

QString DownloaderManager::saveFile(const QUrl &url, const QByteArray &ba)
{
    QFile file(url.path().section('/', -1)); //взяли 1 секцию с конца, т.е. имя файла с расширением
    if (!file.open(QIODevice::WriteOnly)) return QString();
    file.write(ba);
    file.close();
    qDebug() << "Файл сохранен: " + file.fileName();
    return file.fileName();
}

void DownloaderManager::on_pushButton_btn()
{
    QUrl url = QUrl("https://yandex.ru/images/search?text=" + le->text());
    QString nameFile = url.path().section('/', -1);
    //потом запустим парсер, который передаст 3 пути в download
    Downloader *download = new Downloader(this);
    connect(download, SIGNAL(done(const QUrl&, const QByteArray&)),
            this, SLOT(doneDownload(const QUrl&, const QByteArray&)));
    download->download(url);
}

void DownloaderManager::doneDownload(const QUrl &url, const QByteArray &ba)
{
    QString fileName = saveFile(url, ba);
    parseQuery(fileName, 3);
}

void DownloaderManager::doneDownloadPix(const QUrl &url, const QByteArray &ba)
{
    QString fileName = saveFile(url, ba);

    QPixmap pix(fileName);
    pix = pix.scaled(pix.size()/3);
    QLabel* lbl = new QLabel(this);
    lbl->setWindowFlag(Qt::Window);
    lbl->setPixmap(pix);
    lbl->setFixedSize(pix.size());
    qDebug() << "Открываем файл: " + fileName;
    lbl->show();
}

