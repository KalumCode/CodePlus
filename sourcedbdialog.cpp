#include "sourcedbdialog.h"
#include "ui_sourcedbdialog.h"

#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

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

//https://www.wangt.cc/2021/02/qt5%E6%95%B0%E6%8D%AE%E5%BA%93postgresql%E5%BA%94%E7%94%A82/

void SourceDbDialog::on_btBox_accepted()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(ui->editHost->text());
    db.setPort(5432);
    db.setUserName(ui->editUserName->text());
    db.setPassword(ui->editPassword->text());
    db.setDatabaseName(ui->editDB->text());
    connected = db.open();
    if(!connected)
    {
        QString strError=db.lastError().text();
        QMessageBox::information(this,"error",strError);
        return;
    }

    QSqlQuery query;
    if(query.exec("select datname from pg_database;"))
    {
        while(query.next())
            {
                QString strDb=query.value(0).toString();
                qDebug()<<strDb<<endl;
        }
    }

    if(query.exec("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public';"))
    {
        while(query.next())
            {
                QString strDb=query.value(0).toString();
                qDebug()<<strDb<<endl;
        }
    }

    if(query.exec("SELECT column_name FROM information_schema.columns WHERE table_name ='newtable';"))
    {
        while(query.next())
            {
                QString strDb=query.value(0).toString();
                qDebug()<<strDb<<endl;
        }
    }
    db.close();
}

void SourceDbDialog::on_btBox_rejected()
{
    this->close();
}
