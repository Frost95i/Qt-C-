#include "downloader.h"

#include <QNetworkReply>
#include <QMessageBox>

Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotFininshed(QNetworkReply*)));
}

void Downloader::download(const QUrl &url)
{
//    QNetworkRequest request(url);
//    QNetworkReply *reply =
    networkManager->get(QNetworkRequest(url));
}

void Downloader::slotFininshed(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NetworkError::NoError) {
     //  QMessageBox::critical(this, "", "");
       QMessageBox::critical(nullptr, "Error", "Error!");
    }
    else emit done(reply->url(), reply->readAll());
    reply->deleteLater();
}
