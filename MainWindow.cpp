#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DlgPreferences.h"
#include "DlgListEditor.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker(new TWorker(this)) {
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

    connect(ui->actionFileQuit,           &QAction::triggered,      qApp,                   &QGuiApplication::quit);
    connect(ui->pbDirectoryBrowse,        &QPushButton::clicked,    this,                   &MainWindow::on_actionFileSelectDirectory_triggered);

    connect(ui->pbFindOnly,               &QPushButton::clicked,    ui->actionFileFindOnly, &QAction::trigger);
    connect(ui->pbFindAndReplace,         &QPushButton::clicked,    ui->actionFileFindOnly, &QAction::trigger);

    connect(ui->actionFileFindOnly,       &QAction::triggered,      this,                   &MainWindow::initResults);
    connect(ui->actionFileFindAndReplace, &QAction::triggered,      this,                   &MainWindow::initResults);

    connect(ui->actionFileFindOnly,       &QAction::triggered,      this,                   &MainWindow::startFindOnly);
    connect(ui->actionFileFindAndReplace, &QAction::triggered,      this,                   &MainWindow::startFindAndReplace);

    connect(worker,                       &QThread::started,        this,                   &MainWindow::disableUI);
    connect(worker,                       &QThread::finished,       this,                   &MainWindow::enableUI);
    connect(worker,                       &QThread::finished,       this,                   [this](){setProgressInfoVisible(false);});

    connect(worker,                       &TWorker::progressUpdate, this,                   &MainWindow::handleProgressUpdate);
    connect(worker,                       &TWorker::progressMax,    ui->progressBar,        &QProgressBar::setMaximum);
    connect(worker,                       &TWorker::fileFinished,   this,                   &MainWindow::handleFileFinished);

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

    setProgressInfoVisible(false);

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

void MainWindow::on_pbSwapConent_clicked() {
    QString tmp = ui->pteFind->toPlainText();
    ui->pteFind->setPlainText(ui->pteReplace->toPlainText());
    ui->pteReplace->setPlainText(tmp);
}

void MainWindow::initResults() {
    ui->twResults->clearContents();
    ui->twResults->setRowCount(0);
    ui->dwResults->setVisible(true);
}

void MainWindow::setProgressInfoVisible(const bool &b) {
    ui->lProgressText->setVisible(b);
    ui->progressBar->setVisible(b);
}

void MainWindow::updateWorkerConfig() {
    worker->setIncludeMode(ui->twSeachAreaOptions->currentIndex() == 0 ? TWorker::SimpleMode : TWorker::AdvancedMode);
    worker->setWorkingDir(ui->leDirectory->text());
    worker->setRecursive(ui->cbSearchRecursively->isChecked());
    worker->setExcludeDir(ui->leExcludeDirectories->text().split(','));
    worker->setFileMask(ui->leFileMask->text().split(','));
    worker->setExcludeFileMask(ui->leExcludeFileMask->text().split(','));
    worker->setAdvancedRegEx(ui->leRegEx->text());
    worker->setCaseInsensitive(ui->cbOptionCaseInsensitive->isChecked());
    worker->setUseRegex(ui->cbOptionUseRegEx->isChecked());
    worker->setEncoding(static_cast<QStringConverter::Encoding>(ui->cbOptionEncoding->currentIndex())); // Bandwurmcall
}

void MainWindow::startFindOnly() {
    updateWorkerConfig();
    worker->setWorkMode(TWorker::FindOnlyMode);
    setProgressInfoVisible(true);
    worker->start();
}

void MainWindow::startFindAndReplace() {
    updateWorkerConfig();
    worker->setWorkMode(TWorker::FindAndReplaceMode);
    setProgressInfoVisible(true);
    worker->start();
}

void MainWindow::enableUI() {
    changeUIEnabled(true);
}

void MainWindow::disableUI() {
    changeUIEnabled(false);
}

void MainWindow::changeUIEnabled(const bool &enabled) {
    ui->dwOptions->widget()->setEnabled(enabled);
    ui->gbDirectory->setEnabled(enabled);
    ui->gbFindeAndReplace->setEnabled(enabled);
}

void MainWindow::handleProgressUpdate(const int &value, const QString &text) {
    ui->progressBar->setValue(value);
    ui->lProgressText->setText(text);
}

void MainWindow::handleFileFinished(const QString &file, const int &occurences, const bool &success) {
    if(success && occurences == 0)
        return;

    int tableIndex = ui->twResults->rowCount();
    QTableWidgetItem *fileItem       = new QTableWidgetItem(file);
    QTableWidgetItem *occurencesItem = new QTableWidgetItem(QString::number(occurences));
    QTableWidgetItem *successItem    = new QTableWidgetItem(success ? "Success" : "Failed");
    ui->twResults->insertRow(tableIndex);
    ui->twResults->setItem(tableIndex, FileColumn,       fileItem);
    ui->twResults->setItem(tableIndex, OccurencesColumn, occurencesItem);
    ui->twResults->setItem(tableIndex, StatusColumn,     successItem);
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
