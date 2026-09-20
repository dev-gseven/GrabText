#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "screenshotoverlay.h"
#include "downloadwindow.h"

#include <QMainWindow>
#include <QComboBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_printButton_clicked(bool checked);

    void on_langButton_clicked(bool checked);

    void on_comboBox_activated(int index);

    void on_refreshButton_clicked(bool checked);

private:
    void onCaptureFinished();
    void populateComboBox();

    Ui::MainWindow *ui;
    Language language;
};
#endif // MAINWINDOW_H
