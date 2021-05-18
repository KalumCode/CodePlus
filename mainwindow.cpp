#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbLogin=new DBLogin(this);

    configFileName="DataBases.ini";
    dataBasesName="";

    sqlQuery=NULL;
    db = QSqlDatabase::addDatabase("QPSQL");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    dbLogin->show();
}

void MainWindow::readINIFile()
{
    QString fileName= QCoreApplication::applicationDirPath();
    fileName+="/"+configFileName;
    //读取配置文件
    dbSettings=new QSettings(fileName,QSettings::IniFormat);
    db.setHostName(dbSettings->value("DATA_BASE/host_name").toString());
    db.setPort(dbSettings->value("DATA_BASE/port").toString().toUInt());
    db.setUserName(dbSettings->value("DATA_BASE/user_name").toString());
    db.setPassword(dbSettings->value("DATA_BASE/password").toString());
    db.setDatabaseName(dbSettings->value("DATA_BASE/database_name").toString());
}

void MainWindow::selectTable(){
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
    db.close();
}

void MainWindow::selectAllDataBase(){
    connected = db.open();
    if(!connected)
    {
        QString strError=db.lastError().text();
        QMessageBox::information(this,"error",strError);
        return;
    }

    QSqlQuery query;
    if(query.exec("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public';"))
    {
        while(query.next())
        {
            QString strDb=query.value(0).toString();
            qDebug()<<strDb<<endl;
        }
    }
    db.close();
}
