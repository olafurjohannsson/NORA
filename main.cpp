
#include <QApplication>
#include "mainwindow.h"
#include <unistd.h>
#include <stdio.h>
<<<<<<< HEAD
#include "system.h"

#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <sys/sysctl.h>
#endif

=======
#include "environment/system.h"
#include <sys/sysctl.h>
>>>>>>> 1882838bd8c341fd8575ddec6115c25124031ddb
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





