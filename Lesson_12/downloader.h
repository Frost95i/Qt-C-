#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void download(const QUrl &url);

signals:
    void done(const QUrl&, const QByteArray&);
  //  void error();

private slots:
    void slotFininshed(QNetworkReply*);

private:
    QNetworkAccessManager* networkManager {nullptr};
};

#endif // DOWNLOADER_H
