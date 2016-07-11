#include "filesystem.h"
#include <QDirIterator>
#include <QVector>

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

void FileSystem::PopulateDirectoriesAndFiles(const QString path, QVector<QFileInfo> &files)
{
    QDirIterator iterator(path, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        // Get file info
        QFileInfo fileInfo(QFile(iterator.next()).fileName());
        files.append(fileInfo);
    }
}

