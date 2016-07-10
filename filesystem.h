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

    QMap<QString, QString> GetDirectoriesAndFiles(const QString path);

private:
    QDir dir;
};

#endif // FILESYSTEM_H
