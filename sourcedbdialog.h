#ifndef SOURCEDBDIALOG_H
#define SOURCEDBDIALOG_H

#include <QDialog>

namespace Ui {
class SourceDbDialog;
}

class SourceDbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SourceDbDialog(QWidget *parent = nullptr);
    ~SourceDbDialog();

private:
    Ui::SourceDbDialog *ui;
};

#endif // SOURCEDBDIALOG_H
