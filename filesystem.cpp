#include "filesystem.h"
#include <QDirIterator>

FileSystem::FileSystem()
{
    qDebug() << "FileSystem ctor";
    /*
    QDirIterator  iterator("C:\\Users\\olafurj", QDir::Files, QDirIterator::Subdirectories);

    while (iterator.hasNext()) {
        qDebug() << "next(): " << iterator.next();
    }

    QDir d("C:\\");
    QDir *dd = new QDir("C:\\Users\\Olafurj");

    QFileInfoList list = dd->drives();
    QString rootPath = dd->rootPath();
    qDebug() << "rootPath: " << rootPath;
    foreach (QFileInfo info, list) {
        qDebug() << "baseName: " << info.baseName();
    }
    */
}

FileSystem::~FileSystem()
{
    qDebug() << "FileSystem dtor";
}

QMap<QString, QString> FileSystem::GetDirectoriesAndFiles(const QString path)
{
    qDebug() << "getDirFiles";
}
