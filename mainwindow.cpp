#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::close(QObject *data)
{
    qDebug() << "close";
}

MainWindow::~MainWindow()
{
    QObject::connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(close(QObject*)));
    delete ui;
}


void MainWindow::ReceiveString(QString data)
{
    QTextBrowser *browser = this->findChild<QTextBrowser*>("txtBrowser");

    browser->setText(data);
}
