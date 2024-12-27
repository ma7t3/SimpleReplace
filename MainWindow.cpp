#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionFileQuit, &QAction::triggered, qApp, &QGuiApplication::quit);
}

MainWindow::~MainWindow() {
    delete ui;
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
