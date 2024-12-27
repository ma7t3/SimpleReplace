#include "DlgPreferences.h"
#include "ui_DlgPreferences.h"

DlgPreferences::DlgPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPreferences),
    settings("ma7t3", "SimpleReplace") {
    ui->setupUi(this);

    loadThemes();
    loadLanguages();

    connect(this, &QDialog::accepted, this, &DlgPreferences::finish);
}

DlgPreferences::~DlgPreferences() {
    delete ui;
}

void DlgPreferences::loadThemes() {
    themes = QStyleFactory::keys();
    themes.removeAll("windows11");

    currentTheme = settings.value("pref_theme", "windowsvista").toString();

    for(QString name : themes) {
        QString friendlyname;

        if(name == "windowsvista")
            friendlyname = "Windows (Default)";
        else if(name == "Windows")
            friendlyname = "Windows XP";
        else
            friendlyname = name;
        ui->cbTheme->addItem(friendlyname);

        if(name == currentTheme)
            ui->cbTheme->setCurrentText(friendlyname);
    }
}

void DlgPreferences::loadLanguages() {
    currentLanguage = settings.value("pref_lang", "en_US").toString();

    for(QString langKey : languages) {
        QLocale locale(langKey);
        ui->cbLanguage->addItem(locale.nativeLanguageName());

        if(langKey == currentLanguage)
            ui->cbLanguage->setCurrentText(locale.nativeLanguageName());
    }
}

void DlgPreferences::finish() {
    if(languages[ui->cbLanguage->currentIndex()] != currentLanguage)
        QMessageBox::information(this, tr("Restart required"), tr("Some settings only take effect after a restart."));

    qApp->setStyle(QStyleFactory::create(themes[ui->cbTheme->currentIndex()]));

    settings.setValue("pref_theme", themes[ui->cbTheme->currentIndex()]);
    settings.setValue("pref_lang",  languages[ui->cbLanguage->currentIndex()]);
}
