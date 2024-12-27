#include "DlgListEditor.h"
#include "ui_DlgListEditor.h"

DlgListEditor::DlgListEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgListEditor) {
    ui->setupUi(this);
}

DlgListEditor::~DlgListEditor() {
    delete ui;
}

QString DlgListEditor::string() const {
    QStringList items;
    for(int i = 0; i < ui->listWidget->count(); i++)
        items << ui->listWidget->item(i)->text();

    return items.join(",");
}

void DlgListEditor::setString(const QString &string) {
    QStringList items = string.split(",", Qt::SkipEmptyParts);
    for(QString current : items) {
        ui->listWidget->addItem(newEditableItem(current));
    }
}

QListWidgetItem *DlgListEditor::newEditableItem(const QString &text) {
    QListWidgetItem *itm = new QListWidgetItem(text);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    return itm;
}

void DlgListEditor::on_pbAdd_clicked() {
    int currentIndex = ui->listWidget->currentRow();
    if(currentIndex == -1)
        currentIndex = ui->listWidget->count() - 1;

    ui->listWidget->clearSelection();

    QListWidgetItem *itm = newEditableItem();
    ui->listWidget->insertItem(currentIndex + 1, itm);
    ui->listWidget->setCurrentItem(itm);
    ui->listWidget->editItem(itm);
}

void DlgListEditor::on_pbRemove_clicked() {
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    for(QListWidgetItem *itm : items)
        delete ui->listWidget->takeItem(ui->listWidget->row(itm));
}

void DlgListEditor::on_pbMoveUp_clicked() {
    int currentIndex = ui->listWidget->currentRow();
    if(currentIndex < 1)
        return;

    QListWidgetItem *itm = ui->listWidget->takeItem(currentIndex);
    ui->listWidget->insertItem(currentIndex - 1, itm);
    ui->listWidget->setCurrentItem(itm);
}

void DlgListEditor::on_pbMoveDown_clicked() {
    int currentIndex = ui->listWidget->currentRow();
    if(currentIndex >= ui->listWidget->count() - 1)
        return;

    QListWidgetItem *itm = ui->listWidget->takeItem(currentIndex);
    ui->listWidget->insertItem(currentIndex + 1, itm);
    ui->listWidget->setCurrentItem(itm);
}
