#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SimpleReplace_" + QLocale(locale).name();
        if (translator.load(baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QSettings settings("ma7t3", "SimpleReplace");
    a.setStyle(QStyleFactory::create(settings.value("pref_theme", "windowsvista").toString()));

    MainWindow w;
    w.show();
    return a.exec();
}
