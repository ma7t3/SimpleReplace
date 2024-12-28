#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringConverter>

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
    void on_pbExcludeDirectories_clicked();
    void on_pbFileMask_clicked();
    void on_pbExcludeFileMask_clicked();

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
    QStringList _codecs;
};
#endif // MAINWINDOW_H
