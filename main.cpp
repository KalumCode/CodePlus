#include "mainwindow.h"
#include "DBLogin.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBLogin login;
    MainWindow w;

    if(login.exec()==LOGINSUCCESS)
    {
        qDebug()<<"login"<<endl;
        w.show();
    }

    return a.exec();
}
