#include "language.h"

Language::Language():currentIndex(0),
    languagePath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/languages")

{
    QDir().mkpath(languagePath);
}

void Language::populateLangsVector(){
    langs.clear();

    QDirIterator dirIterator(languagePath,QDir::Files);

    while(dirIterator.hasNext()){
        dirIterator.next();

        langs.push_back(dirIterator.fileInfo().completeBaseName());
    }
}

QString Language::getLanguagePath() const{
    return languagePath;
}

QString Language::getCurrentLang(int index) const{
    return langs[index];
}

void Language::setCurrentIndex(int index){
    currentIndex = index;
}

int Language::getCurrentIndex() const{
    return currentIndex;
}

int Language::getCurrentLenght() const{
    return langs.size();
}
