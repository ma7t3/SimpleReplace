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

    QStringList styles = QStyleFactory::keys();
    if(styles.contains("Fusion")) {
        QStyle *s = QStyleFactory::create("Fusion");
        a.setStyle(s);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
