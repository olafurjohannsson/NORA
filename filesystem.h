#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>

#ifndef FILESYSTEM_H
#define FILESYSTEM_H


class FileSystem
{
public:
    FileSystem();
    ~FileSystem();

    void PopulateDirectoriesAndFiles(const QString path, QVector<QFileInfo> &files);

private:
    QDir dir;
};

#endif // FILESYSTEM_H
