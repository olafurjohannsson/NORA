
#include <QApplication>
#include "mainwindow.h"
#include <unistd.h>
#include <stdio.h>
#include "system.h"
#include <sys/sysctl.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}





