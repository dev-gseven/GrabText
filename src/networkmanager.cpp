#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, qNetManager(this)
{
    connect(&qNetManager, &QNetworkAccessManager::finished, this, &NetworkManager::fetchFinished);
}

void NetworkManager::fetchLanguages(){
    QNetworkRequest request(QUrl("https://api.github.com/repos/tesseract-ocr/tessdata/contents"));
    qNetManager.get(request);
}

void NetworkManager::downloadLanguage(const QString &url, const QString &language)
{

    QString path = m_language.getLanguagePath() + "/" + language;

    currentFile.setFileName(path);

    if (!currentFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    QNetworkRequest request((QUrl(url)));

    currentReply = qNetManager.get(request);

    connect(currentReply,
            &QNetworkReply::readyRead,
            this,
            &NetworkManager::onReadyRead);

    connect(currentReply,
            &QNetworkReply::finished,
            this,
            &NetworkManager::onDownloadFinished);
}

void NetworkManager::onDownloadFinished(){
    if (!currentReply)
        return;

    // Ainda pode haver dados disponíveis.
    currentFile.write(currentReply->readAll());

    currentFile.close();

    if (currentReply->error() == QNetworkReply::NoError)
    {
        emit downloadFinished();
    }
    else
    {
        emit downloadFailed();
        currentFile.remove();
    }

    currentReply->deleteLater();
    currentReply = nullptr;
}

void NetworkManager::onReadyRead()
{
    if (currentReply)
    {
        currentFile.write(currentReply->readAll());
    }
}
