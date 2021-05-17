#ifndef DBLOGIN_H
#define DBLOGIN_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QFile>

#define  LOGINSUCCESS 0
#define  LOGINFAILURE 1

namespace Ui {
class DBLogin;
}

class DBLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DBLogin(QWidget *parent = nullptr);
    ~DBLogin();

private slots:
    void on_btBox_accepted();

    void on_btBox_rejected();

private:
    Ui::DBLogin *ui;
    QSqlDatabase db;
    bool connected;

    QSettings *dbSettings;

    //读取配置文件
    void readINIFile();
    void updateIniFile();

};

#endif // DBLOGIN_H
