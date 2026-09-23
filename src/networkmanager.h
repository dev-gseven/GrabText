#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "language.h"

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QFile>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void fetchLanguages();
    void downloadLanguage(const QString &url, const QString &language);

signals:
    void fetchFinished(QNetworkReply *reply);
//    void downloadFinished(QNetworkReply *reply);
    void downloadFinished();
    void downloadFailed();

private slots:
    void onReadyRead();
    void onDownloadFinished();

private:
//    void onDownloadFinished(QNetworkReply *reply);
    QNetworkAccessManager qNetManager;
    QNetworkReply *currentReply = nullptr;
    QFile currentFile;
    Language m_language;
};

#endif // NETWORKMANAGER_H
