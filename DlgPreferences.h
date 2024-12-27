#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include <QDialog>
#include <QStyleFactory>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class DlgPreferences;
}

class DlgPreferences : public QDialog {
    Q_OBJECT

public:
    explicit DlgPreferences(QWidget *parent = nullptr);
    ~DlgPreferences();

protected:
    void loadThemes();
    void loadLanguages();

protected slots:
    void finish();

private:
    Ui::DlgPreferences *ui;

    QString currentTheme, currentLanguage;

    QStringList themes;
    QStringList languages = {"en_US", "de_DE"};

    QSettings settings;
};

#endif // DLGPREFERENCES_H
