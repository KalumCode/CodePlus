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
    readINIFile();
    selectAllDataBase();
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

void MainWindow::selectAllDataBase(){
    connected = db.open();
    if(!connected)
    {
        QString strError=db.lastError().text();
        QMessageBox::information(this,"error",strError);
        return;
    }

    ui->treeDatabase->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeDatabase->setStyle(QStyleFactory::create("windows"));

    //构造QTreeView的Model
    QStandardItemModel* model = new QStandardItemModel(ui->treeDatabase);

    //构造1级节点
    QStandardItem* item1 = new QStandardItem(QStringLiteral("数据库"));
    model->appendRow(item1);	//加入model

    //构造2级节点
    QSqlQuery query;
    if(query.exec("select datname from pg_database;"))
    {
        while(query.next())
        {
            //构造2级节点
            QString strDb=query.value(0).toString();
            if(strDb=="template0" || strDb=="template1"){
                continue;
            }
            QStandardItem* itemDb=new QStandardItem(strDb);
            item1->appendRow(itemDb);	//加入1级节点
            qDebug()<<"db:"+strDb<<endl;
        }
    }
    db.close();

    ui->treeDatabase->setHeaderHidden(true);	//设置隐藏表头
    ui->treeDatabase->setModel(model); //为QTreeView应用model
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
    if(query.exec("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public';"))
    {
        while(query.next())
        {
            QString strDb=query.value(0).toString();
            qDebug()<<"tb="+strDb<<endl;
        }
    }
    db.close();
}
