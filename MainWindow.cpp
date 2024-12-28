#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DlgPreferences.h"
#include "DlgListEditor.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // setup shortcuts
    ui->actionFileSelectDirectory->setShortcut(QKeySequence::Open);
    ui->actionFileFindOnly->setShortcut(QKeySequence::Find);
    ui->actionFileFindAndReplace->setShortcut(QKeySequence::Replace);
    ui->actionFileQuit->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Q));

    ui->actionProfileNew->setShortcut(QKeySequence::New);
    ui->actionProfileSave->setShortcut(QKeySequence::Save);
    ui->actionProfileSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionProfileSwitchProfile->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_P));
    ui->actionProfileImport->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_I));
    ui->actionProfileExport->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_E));
    ui->actionProfileManageProfiles->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_M));
    ui->actionSettingsPreferences->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Comma));
    ui->actionHelpAbout->setShortcut(QKeySequence(Qt::Key_F1));

    _codecs = QStringConverter::availableCodecs();
    for(const QString &current : _codecs) {
        if(current == "ISO-8859-1")
            ui->cbOptionEncoding->addItem("Windows-1252");
        else
            ui->cbOptionEncoding->addItem(current);
    }

    ui->dwResults->setVisible(false);

    connect(ui->actionFileQuit, &QAction::triggered, qApp, &QGuiApplication::quit);
    connect(ui->pbDirectoryBrowse, &QPushButton::clicked, this, &MainWindow::on_actionFileSelectDirectory_triggered);

    connect(ui->pbFindOnly,               &QPushButton::clicked, ui->actionFileFindOnly, &QAction::trigger);
    connect(ui->pbFindAndReplace,         &QPushButton::clicked, ui->actionFileFindOnly, &QAction::trigger);

    connect(ui->actionFileFindOnly,       &QAction::triggered,   this,                   &MainWindow::initResults);
    connect(ui->actionFileFindAndReplace, &QAction::triggered,   this,                   &MainWindow::initResults);

    QToolBar *generalToolbar = addToolBar(tr("General"));
    generalToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction *optionsToogleAction = ui->dwOptions->toggleViewAction();
    QAction *resultsToogleAction = ui->dwResults->toggleViewAction();

    optionsToogleAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentProperties));
    resultsToogleAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::FormatJustifyLeft));

    optionsToogleAction->setText(tr("Options"));
    resultsToogleAction->setText(tr("Results"));

    optionsToogleAction->setShortcut(QKeySequence(Qt::ALT|Qt::Key_O));
    resultsToogleAction->setShortcut(QKeySequence(Qt::ALT|Qt::Key_R));

    ui->menuView->addAction(optionsToogleAction);
    ui->menuView->addAction(resultsToogleAction);

    generalToolbar->addAction(optionsToogleAction);
    generalToolbar->addAction(resultsToogleAction);
    generalToolbar->addSeparator();

    QToolBar *profileToolbar = addToolBar(tr("Profiles"));
    profileToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    profileToolbar->addAction(ui->actionProfileNew);
    profileToolbar->addAction(ui->actionProfileSave);
    profileToolbar->addAction(ui->actionProfileSwitchProfile);
    profileToolbar->addSeparator();
    profileToolbar->addAction(ui->actionProfileImport);
    profileToolbar->addAction(ui->actionProfileExport);
    profileToolbar->addAction(ui->actionProfileManageProfiles);
    profileToolbar->addSeparator();
    //TODO: Last Used Profiles here

    ui->twSeachAreaOptions->setCurrentIndex(0);

    ui->twResults->setColumnWidth(      FileColumn, 500);
    ui->twResults->setColumnWidth(    StatusColumn, 100);
    ui->twResults->setColumnWidth(OccurencesColumn, 100);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pbExcludeDirectories_clicked() {
    DlgListEditor dlg;
    dlg.setString(ui->leExcludeDirectories->text());
    dlg.exec();
    ui->leExcludeDirectories->setText(dlg.string());
}

void MainWindow::on_pbFileMask_clicked() {
    DlgListEditor dlg;
    dlg.setString(ui->leFileMask->text());
    dlg.exec();
    ui->leFileMask->setText(dlg.string());
}

void MainWindow::on_pbExcludeFileMask_clicked() {
    DlgListEditor dlg;
    dlg.setString(ui->leExcludeFileMask->text());
    dlg.exec();
    ui->leExcludeFileMask->setText(dlg.string());
}

void MainWindow::initResults() {
    ui->twResults->clearContents();
    ui->twResults->setRowCount(0);
    ui->dwResults->setVisible(true);
}

void MainWindow::on_actionFileSelectDirectory_triggered() {
    QString path = QFileDialog::getExistingDirectory(this, "", ui->leDirectory->text());
    if(path.isEmpty())
        return;

    ui->leDirectory->setText(path);
}

void MainWindow::on_actionSettingsPreferences_triggered() {
    DlgPreferences dlg(this);
    dlg.exec();
}

void MainWindow::on_actionHelpDocumentation_triggered() {
    QMessageBox::critical(this, tr("Documentation not available"), tr("The documentation is not available now!"));
}

void MainWindow::on_actionHelpAbout_triggered() {
    QMessageBox msg;
    msg.setWindowTitle(tr("About SimpleReplace"));
    msg.setText(tr("<h1>About SimpleReplace</h1><p><i>Created by ma7t3</i></p><table><tr><td><b>Version: </b></td><td>%1</td></tr><tr><td><b>License: </b></td><td><a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GNU General Public License V3</a></td></tr></table>"));
    msg.setIconPixmap(QPixmap(":/resources/Icon_128x128.png"));
    msg.exec();
}

void MainWindow::on_actionHelpAboutQt_triggered() {
    QMessageBox::aboutQt(this);
}
