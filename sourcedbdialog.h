#ifndef SOURCEDBDIALOG_H
#define SOURCEDBDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class SourceDbDialog;
}

class SourceDbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SourceDbDialog(QWidget *parent = nullptr);
    ~SourceDbDialog();

private slots:
    void on_btBox_accepted();

    void on_btBox_rejected();

private:
    Ui::SourceDbDialog *ui;
    QSqlDatabase db;
    bool connected;

};

#endif // SOURCEDBDIALOG_H
