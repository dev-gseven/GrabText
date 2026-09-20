#ifndef SCREENSHOTOVERLAY_H
#define SCREENSHOTOVERLAY_H

#include "language.h"

#include <QWidget>
#include <QClipboard>
#include <tesseract/baseapi.h>
#include <QApplication>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>
#include <QString>

class ScreenshotOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenshotOverlay(Language &language, QWidget *parent = nullptr);

    int getCurrentIndex() const;
    void setCurrentIndex(int index);

private:
    QPixmap m_screenshot;
    QPoint m_origin;
    QPoint m_current;
    bool m_selecting;

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    QPixmap grabDesktop() const;
    QRect normalizedSelection() const;
    void copySelectionToClipboard();

    Language &ref_language;
    tesseract::TessBaseAPI tesseract;

signals:
    void captureFinished();
};

#endif // SCREENSHOTOVERLAY_H
