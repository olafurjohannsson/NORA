
#include <QApplication>
#include "mainwindow.h"
#include <unistd.h>
#include <stdio.h>
#include "environment/system.h"
#include <sys/sysctl.h>
#include <limits.h>
#include <filesystem/filesystem.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileSystem fs;

    PhysicalDirectory pd;

    return a.exec();
}





