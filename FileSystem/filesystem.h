#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

class PhysicalDirectory
{
public:
    PhysicalDirectory(const QString newPath);
    ~PhysicalDirectory();
    const QString GetPath();
    const QVector<QString> GetFiles();
    bool SetPath(const QString newPath);

private:
    void ChangeCurrentDirectory(const QString newPath);
    QVector<QString> files;
    QString path;
};

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
