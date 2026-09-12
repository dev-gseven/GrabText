#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, qNetManager(this)
{
    connect(&qNetManager, &QNetworkAccessManager::finished, this, &NetworkManager::finished);
//    connect(&qNetManager, &QNetworkAccessManager::finished, this, &NetworkManager::onDownloadFinished);
}

void NetworkManager::fetchLanguages(){
    QNetworkRequest request(QUrl("https://api.github.com/repos/tesseract-ocr/tessdata/contents"));
    qNetManager.get(request);
}

void NetworkManager::downloadLanguage(const QString &url, const QString &language)
{
    currentLanguage = language;

//    QString path = "../Resources/languages/" + language + ".traineddata";
//    QString path = "/Users/felipemorais/Workspace/" + currentLanguage;
    QString path = "../Resources/languages/" + currentLanguage;

    currentFile.setFileName(path);

    if (!currentFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erro ao abrir arquivo:"
                 << currentFile.fileName();

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
        qDebug() << "Download concluído:"
                 << currentFile.fileName();

        emit downloadFinished();
    }
    else
    {
        qDebug() << "Erro no download:"
                 << currentReply->errorString();

        // Se houve erro, remove o arquivo incompleto.
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
