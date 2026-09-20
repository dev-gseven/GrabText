#include "downloadwindow.h"
#include "ui_downloadwindow.h"

DownloadWindow::DownloadWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::DownloadWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(&netManager, &NetworkManager::finished, this, &DownloadWindow::onReplyFinished);

    netManager.fetchLanguages();
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::onReplyFinished(QNetworkReply *reply){

    QByteArray data = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (const QJsonValue &value : array)
    {
        QJsonObject obj = value.toObject();

        QString codename = obj["name"].toString();

        if (!codename.endsWith(".traineddata")){
            continue;
        }

        codenames.push_back(codename);

        QString filename = codename;
        filename.chop(QString(".traineddata").length());

        QString download = obj["download_url"].toString();
        downloadLinks.push_back(download);

        float sizeMB = obj["size"].toInt();
        sizeMB = sizeMB / 1024 / 1024;

        //adds the languages to tableWidget

        int newLine = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newLine);
        ui->tableWidget->setItem(newLine, 0, new QTableWidgetItem(filename));
        ui->tableWidget->setItem(newLine, 1, new QTableWidgetItem(QString("%1 MB").arg(sizeMB, 0, 'f', 1)));
    }
}

void DownloadWindow::on_downloadButton_clicked(bool checked)
{
    int row = ui->tableWidget->currentRow();
    netManager.downloadLanguage(downloadLinks[row],codenames[row]);
}
