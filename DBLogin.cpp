#include "DBLogin.h"
#include "ui_dblogin.h"

#include "QMessageBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

DBLogin::DBLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBLogin)
{
    ui->setupUi(this);
    ui->editPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    readINIFile();
}

DBLogin::~DBLogin()
{
    delete ui;
}

//https://www.wangt.cc/2021/02/qt5%E6%95%B0%E6%8D%AE%E5%BA%93postgresql%E5%BA%94%E7%94%A82/

void DBLogin::on_btBox_accepted()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(ui->editHost->text());
    db.setPort(ui->editPort->text().toUInt());
    db.setUserName(ui->editUserName->text());
    db.setPassword(ui->editPassword->text());
    db.setDatabaseName(ui->editDB->text());
    connected = db.open();
    if(!connected)
    {
        QString strError=db.lastError().text();
        QMessageBox::information(this,"error",strError);
        QDialog::done(LOGINFAILURE);
        return;
    }
    updateIniFile();

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

    QDialog::done(LOGINSUCCESS);
}

void DBLogin::on_btBox_rejected()
{
    this->close();
}

void DBLogin::readINIFile()
{
    QString fileName= QCoreApplication::applicationDirPath();
    fileName+="/DataBases.ini";
    //读取配置文件
    dbSettings=new QSettings(fileName,QSettings::IniFormat);
    ui->editHost->setText(dbSettings->value("DATA_BASE/host_name").toString());
    ui->editPort->setText(dbSettings->value("DATA_BASE/port").toString());
    ui->editUserName->setText(dbSettings->value("DATA_BASE/user_name").toString());
    ui->editPassword->setText(dbSettings->value("DATA_BASE/password").toString());
    ui->editDB->setText(dbSettings->value("DATA_BASE/database_name").toString());
}

void DBLogin::updateIniFile(){
    QString fileName= QCoreApplication::applicationDirPath();
    fileName+="/DataBases.ini";

    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("DATA_BASE/host_name", ui->editHost->text());
    settings.setValue("DATA_BASE/port", ui->editPort->text());
    settings.setValue("DATA_BASE/user_name", ui->editUserName->text());
    settings.setValue("DATA_BASE/password", ui->editPassword->text());
    settings.setValue("DATA_BASE/database_name", ui->editDB->text());
}
