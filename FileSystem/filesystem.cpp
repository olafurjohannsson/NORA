#include "filesystem.h"
#include <QDirIterator>
#include <QVector>

PhysicalDirectory::PhysicalDirectory()
{

}


QVector<QString> PhysicalDirectory::GetFiles()
{
    // get iterator on current path
    QDirIterator iterator(this->path, QDir::Files, QDirIterator::Subdirectories);

    // go through files
    QVector<QString> files;
    while (iterator.hasNext())
        files.append(iterator.next());
}

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

