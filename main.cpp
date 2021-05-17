#include "mainwindow.h"
#include "DBLogin.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBLogin login;

    if(login.exec()==LOGINSUCCESS)
    {
        MainWindow w;
        w.show();
    }

    return a.exec();
}
