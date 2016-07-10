#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "requestmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ReceiveString(QString data);
    void close(QObject *data);
    void FetchUrlClicked(bool clicked);


private:
    Ui::MainWindow *ui;
    RequestManager *requestManager;
};

#endif // MAINWINDOW_H
