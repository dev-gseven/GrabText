#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void fetchLanguages();
    void downloadLanguage(const QString &url, const QString &language);

signals:
    void finished(QNetworkReply *reply);
//    void downloadFinished(QNetworkReply *reply);
    void downloadFinished();

private slots:
    void onReadyRead();
    void onDownloadFinished();

private:
//    void onDownloadFinished(QNetworkReply *reply);
    QNetworkAccessManager qNetManager;
    QString currentLanguage;
    QNetworkReply *currentReply = nullptr;
    QFile currentFile;
};

#endif // NETWORKMANAGER_H
