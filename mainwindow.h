#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
#include <QStandardItemModel>
#include <QStyleFactory>

#include "DBLogin.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DBLogin *dbLogin;

    QSettings *dbSettings;

    QSqlDatabase db;//数据库
    QSqlQuery *sqlQuery;//数据库执行指针
    bool connected;

    QString configFileName;//配置文件名称
    QString dataBasesName;

    //查询所有数据库
    void selectAllDataBase();

    //查询当前数据中的表
    void selectTable();    

    //读取配置文件
    void readINIFile();

};
#endif // MAINWINDOW_H
