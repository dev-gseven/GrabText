#include "screenshotoverlay.h"

ScreenshotOverlay::ScreenshotOverlay(Language &language, QWidget *parent)
    : QWidget{parent}, m_screenshot(grabDesktop()), m_selecting(false),ref_language(language)
{
    const QRect desktopGeometry = QGuiApplication::primaryScreen()->virtualGeometry();

    setWindowFlags(Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);
    setMouseTracking(true);
    setCursor(Qt::CrossCursor);
    setGeometry(desktopGeometry);
}


void ScreenshotOverlay::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
        return;
    }

    QWidget::keyPressEvent(event);
}

void ScreenshotOverlay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    m_origin = event->pos();
    m_current = event->pos();
    m_selecting = true;
    update();
}

void ScreenshotOverlay::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_selecting) {
        return;
    }

    m_current = event->pos();
    update();
}

void ScreenshotOverlay::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || !m_selecting) {
        return;
    }

    m_current = event->pos();
    m_selecting = false;
    copySelectionToClipboard();

    emit captureFinished();
    close();
}

void ScreenshotOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.drawPixmap(rect(), m_screenshot);
    painter.fillRect(rect(), QColor(0, 0, 0, 130));

    const QRect selection = normalizedSelection();
    if (selection.isValid()) {
        painter.drawPixmap(selection, m_screenshot, selection);

        QPen borderPen(QColor(80, 180, 255));
        borderPen.setWidth(2);
        painter.setPen(borderPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(selection.adjusted(0, 0, -1, -1));
    }
}

QPixmap ScreenshotOverlay::grabDesktop() const
{
    const QRect virtualGeometry = QGuiApplication::primaryScreen()->virtualGeometry();
    QPixmap desktop(virtualGeometry.size());
    desktop.fill(Qt::transparent);

    QPainter painter(&desktop);
    for (QScreen *screen : QGuiApplication::screens()) {
        const QRect screenGeometry = screen->geometry();
        const QPixmap screenCapture = screen->grabWindow(0);
        const QRect targetRect(screenGeometry.topLeft() - virtualGeometry.topLeft(),
                               screenGeometry.size());
        painter.drawPixmap(targetRect, screenCapture);
    }

    return desktop;
}

QRect ScreenshotOverlay::normalizedSelection() const
{
    return QRect(m_origin, m_current)
        .normalized()
        .intersected(rect());
}

void ScreenshotOverlay::copySelectionToClipboard()
{
    const QRect selection = normalizedSelection();
    if (selection.width() < 2 || selection.height() < 2) {
        return;
    }

    // initialize tesseract
    if (tesseract.Init(ref_language.getLanguagePath().toStdString().c_str(), ref_language.getCurrentLang(ref_language.getCurrentIndex()).toStdString().c_str())){
        return;
    }


    const QPixmap capture = m_screenshot.copy(selection);
    const QImage image = capture.toImage();
    tesseract.SetImage(
        image.bits(),
        image.width(),
        image.height(),
        image.depth() / 8,
        image.bytesPerLine()
        );

    char* outText = tesseract.GetUTF8Text();

    QString text = outText;

    QApplication::clipboard()->setText(text);

    delete[] outText;

    tesseract.End();
}

