#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QLibraryInfo>
#include <QSettings>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSettings settings("ma7t3", "SimpleReplace");
    QString languageKey = settings.value("pref_lang", "en_US").toString();

    QTranslator translator;
    if (translator.load(":/translations/" + languageKey + ".qm")) {
        a.installTranslator(&translator);
    }

    QTranslator qtTranslator;
    if (qtTranslator.load(":/translations/" + languageKey + "_qt.qm")) {
        a.installTranslator(&qtTranslator);
    }

    a.setStyle(QStyleFactory::create(settings.value("pref_theme", "windowsvista").toString()));

    MainWindow w;
    w.show();
    return a.exec();
}
