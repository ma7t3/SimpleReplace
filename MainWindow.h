#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringConverter>
#include <QToolBar>

#include "TWorker.h"


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

    void on_pbSwapConent_clicked();

    void initResults();
    void setProgressInfoVisible(const bool &);

    void updateWorkerConfig();
    void startFindOnly();
    void startFindAndReplace();

    void enableUI();
    void disableUI();
    void changeUIEnabled(const bool &enabled);
    void handleProgressUpdate(const int &value, const QString &text);
    void handleFileFinished(const QString &file, const int &occurences, const bool &success);

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

    TWorker *worker;

    enum ResultTableColumns {
        FileColumn,
        StatusColumn,
        OccurencesColumn
    };
};
#endif // MAINWINDOW_H
