#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include "networkmanager.h"

#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValueRef>
#include <QTableWidget>
#include <QString>
#include <QVector>
#include <QWidget>

namespace Ui {
class DownloadWindow;
}

class DownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWindow(QWidget *parent = nullptr);
    ~DownloadWindow();

private slots:


    void on_downloadButton_clicked(bool checked);

private:
    QVector<QString> downloadLinks;
    QVector<QString> codenames;

    void onReplyFinished(QNetworkReply *reply);

    Ui::DownloadWindow *ui;
    NetworkManager netManager;
};

#endif // DOWNLOADWINDOW_H
