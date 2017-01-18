#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&client,SIGNAL(connected()),this,SLOT(connected()));
    connect(&client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(&client,SIGNAL(readyRead()),this,SLOT(readed()));
    connect(&client,SIGNAL(error(QAbstractSocket::SocketError)),this,
            SLOT(error(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString ip = ui->ipEdit->text();
    int port = ui->portEdit->text().toInt();
    client.connectToHost(ip,port);
    client.waitForConnected(10000);
}

void MainWindow::connected()
{
    ui->textBrowser->append("Connected\n");
}

void MainWindow::disconnected()
{
    ui->textBrowser->append("disconnected\n");
}

void MainWindow::readed()
{
    ui->textBrowser->append("read:\n");
    ui->textBrowser->append(QString(client.readAll()));
}

void MainWindow::error(QAbstractSocket::SocketError serr)
{
    ui->textBrowser->append(QString("error: ")+QString((int)serr)+QString("\n"));
}

void MainWindow::on_pushButton_3_clicked()
{
    client.close();
    //client.destroyed();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString text = ui->textEdit->toPlainText();
    client.write(text.toUtf8());
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::about(this,"О программе","Автор: javavirys");
    QDesktopServices::openUrl(QUrl("https://vk.com/javavirys"));
}
