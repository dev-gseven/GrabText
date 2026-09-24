#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    populateComboBox();

    ui->comboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateComboBox(){
    language.populateLangsVector();
    ui->comboBox->clear();

    for (int i=0;i<language.getCurrentLenght();i++){
        ui->comboBox->addItem(language.getCurrentLang(i));
    }

    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_printButton_clicked(bool checked)
{
    hide();
    QTimer::singleShot(100, this, [this](){
        auto *overlay = new ScreenshotOverlay(language, this);
        overlay->show();

        connect(overlay, &ScreenshotOverlay::captureFinished,
                this, &MainWindow::onCaptureFinished);
    });

}

void MainWindow::on_langButton_clicked(bool checked)
{
    auto *downloadWindow = new DownloadWindow(nullptr);
    downloadWindow->show();

    connect(downloadWindow, &DownloadWindow::downloadFinished, this, &MainWindow::onDownloadFinished);
}

void MainWindow::on_comboBox_activated(int index)
{
    language.setCurrentIndex(index);
}

void MainWindow::onCaptureFinished()
{
    show();
    activateWindow();
    raise();
}

void MainWindow::onDownloadFinished(){
    populateComboBox();
}
