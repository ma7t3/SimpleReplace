#ifndef DLGLISTEDITOR_H
#define DLGLISTEDITOR_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class DlgListEditor;
}

class DlgListEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgListEditor(QWidget *parent = nullptr);
    ~DlgListEditor();

    QString string() const;
    void setString(const QString &);

protected:
    QListWidgetItem *newEditableItem(const QString &text = "");

private slots:
    void on_pbAdd_clicked();
    void on_pbRemove_clicked();
    void on_pbMoveUp_clicked();
    void on_pbMoveDown_clicked();

private:
    Ui::DlgListEditor *ui;

    QStringList items;
};

#endif // DLGLISTEDITOR_H
