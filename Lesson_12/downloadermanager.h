#ifndef DOWNLOADERMANAGER_H
#define DOWNLOADERMANAGER_H

#include <QtWidgets>
#include <QtGui>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QStringList>

#include "downloader.h"

class DownloaderManager : public QWidget
{
    Q_OBJECT
public:
    explicit DownloaderManager(QWidget *parent = nullptr);

signals:

private:
    QGridLayout *mainGrid {nullptr};
    QLineEdit *le {nullptr};
    QPushButton *btn {nullptr};

    void showPixMap(const QString& path);
    void parseQuery(const QString path, const int count);
    QString saveFile(const QUrl &url, const QByteArray &ba);
private slots:
    void on_pushButton_btn();
    void doneDownload(const QUrl&, const QByteArray&);
    void doneDownloadPix(const QUrl &url, const QByteArray &ba);

};

#endif // DOWNLOADERMANAGER_H
