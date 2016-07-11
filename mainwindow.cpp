#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QStringBuilder>
#include <QTextBrowser>
#include "filesystem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setup UI
    ui->setupUi(this);


    //connect(ui->btnFetchUrl, SIGNAL(clicked(bool)), this, SLOT(FetchUrlClicked(bool)));
    //connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(close(QObject*)));

    // create manager
    //this->requestManager = new RequestManager(this);

    // setup connection between http manager and window
    //connect(this->requestManager, SIGNAL(sendSignal(QString)), this, SLOT(ReceiveString(QString)));

    // Read from filesystem
    FileSystem fs;
    QVector<QFileInfo> files;
    fs.PopulateDirectoriesAndFiles("/Users/olafurj/Dropbox", files);

    auto *model = new QStringListModel(this);
    QStringList list;
    foreach (QFileInfo file, files) {
        list << file.fileName();
    }
    model->setStringList(list);

    ui->lvItems->setModel(model);
    ui->textFileList->setText("asdf");

    //delete model;
}

void MainWindow::FetchUrlClicked(bool clicked)
{
    if (true || clicked)
    {
        ui->label->setText("Fetching: " + ui->lineUrl->text());
        this->requestManager->GET(ui->lineUrl->text());


        //request->deleteLater();
    }




    //this->requestManager->deleteLater();
}

void MainWindow::close(QObject *data)
{
    qDebug() << "close";

}

MainWindow::~MainWindow()
{
    qDebug() << "dtor";
    //disconnect(this->requestManager, SIGNAL(sendSignal(QString)), this, SLOT(ReceiveString(QString)));

    delete this->requestManager;

    delete ui;
}


void MainWindow::ReceiveString(QString data)
{
    QTextBrowser *browser = this->findChild<QTextBrowser*>("txtBrowser");

    browser->setText(data);
}
