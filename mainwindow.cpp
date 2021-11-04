#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <functions.hh>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(600,300);

    QPixmap pix(":/resources/Img/login.jpg");
    int w = ui->picture->width();
    int h = ui->picture->height();
    ui->picture->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    QSqlDatabase mydb;

    connOpen(mydb);

    QSqlQuery qry;
    qry.prepare("select * from employed where username = '"+username+"' and password ='"+password+"'");

    if(qry.exec()){
        if (qry.next()) {

            hide();

            userDialog = new User(this);

            userDialog->setLabelTitle("Username " + username);

            userDialog->show();

       }
        else {
            ui->statusbar->showMessage("Username and password is not correct", 4000);
        }
    }
    connClose(mydb);
}

