#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "DlgPreferences.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
     /////////////
    // MENUBAR //
   /////////////
    // FILE
    void on_actionFileSelectDirectory_triggered();

    // PROFILE

    // SETTINGS
    void on_actionSettingsPreferences_triggered();

    // HELP
    void on_actionHelpDocumentation_triggered();
    void on_actionHelpAbout_triggered();
    void on_actionHelpAboutQt_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
