#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QVector>
#include <QDirIterator>
#include <QCoreApplication>

class Language
{
public:
    Language();

    void setCurrentIndex(int index);
    int getCurrentIndex() const;
    int getCurrentLenght() const;

    QString getCurrentLang(int index) const;
    QString getLanguagePath() const;

    void populateLangsVector();
private:
    int currentIndex;

    QString languagePath;
    QString tesseractPath;

    QVector<QString> langs;
};

#endif // LANGUAGE_H
