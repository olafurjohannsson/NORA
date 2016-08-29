
#include <QApplication>
#include "mainwindow.h"
#include <unistd.h>
#include <stdio.h>
#include "system.h"

#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <sys/sysctl.h>
#endif

#include <limits.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}





