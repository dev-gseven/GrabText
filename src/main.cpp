#include "mainwindow.h"

#include <QApplication>

#ifdef __WIN32

#include <QStyleFactory>
#include <QPalette>
#include <QColor>
#include <windows.h>

bool isDarkMode()
{
    DWORD value = 1; // default = white
    DWORD dataSize = sizeof(value);

    if (RegGetValueW(
            HKEY_CURRENT_USER,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
            L"AppsUseLightTheme",
            RRF_RT_REG_DWORD,
            nullptr,
            &value,
            &dataSize) == ERROR_SUCCESS)
    {
        return value == 0; // 0 = dark
    }
    return false;
}

void setDarkMode(QApplication &a){
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(32, 32, 32));
    darkPalette.setColor(QPalette::WindowText, QColor(240, 240, 240));

    darkPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ButtonText, QColor(240, 240, 240));

    darkPalette.setColor(QPalette::Base, QColor(32, 32, 32));
    darkPalette.setColor(QPalette::Text, QColor(240, 240, 240));

    a.setPalette(darkPalette);
}

#endif

int main(int argc, char *argv[])
{

#ifdef __WIN32

    if (isDarkMode()){
        qputenv("QT_QPA_PLATFORM", "windows:darkmode=1");
    }

#endif

    QApplication a(argc, argv);

#ifdef __WIN32

    if (isDarkMode()){
        setDarkMode(a);
    }

#endif

    MainWindow w;
    w.show();
    return a.exec();
}
