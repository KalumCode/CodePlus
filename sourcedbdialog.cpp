#include "sourcedbdialog.h"
#include "ui_sourcedbdialog.h"

SourceDbDialog::SourceDbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceDbDialog)
{
    ui->setupUi(this);
}

SourceDbDialog::~SourceDbDialog()
{
    delete ui;
}
