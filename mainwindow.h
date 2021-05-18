#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
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

    static QSqlDatabase *database;//数据库指针
    static QSqlQuery *query;//数据库执行指针

    QString configFileName;//配置文件名称
    //查询当前数据中的表
    void selectTable();

};
#endif // MAINWINDOW_H
