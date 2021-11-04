#include "user.hh"
#include "ui_user.h"
#include "mainwindow.hh"
#include "functions.hh"
#include <QMessageBox>
#include <QString>
#include "member.hh"
#include "rent.hh"

User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
}

User::~User()
{
    delete ui;
}

void User::setLabelTitle(const QString &title)
{
    ui->username->setText(title);

}


void User::on_addBook_clicked()
{
    QString book = space(ui->Book->text());
    QString writer = space(ui->Writer->text());
    int year = ui->year->text().toInt();
    int number = ui->number->text().toInt();


    QSqlDatabase mydb;
    connOpen(mydb);

    QSqlQuery qry;

    if ( mydb.tables().contains( QLatin1String("book") )) {

        qry.prepare("select * from book "
                    "where book = '"+book+"' and writer ='"+writer+"' and year = '"+QString::number(year)+"'");

        if(qry.exec()){

            if(qry.next()) {
                qry.prepare("UPDATE book SET number = number + '"+QString::number(number)+"'"
                            "WHERE book = '"+book+"' and writer ='"+writer+"' and year = '"+QString::number(year)+"'");

                if(qry.exec())
                    ui->notice->setText(book + " added");            }
            else {
                qry.prepare("INSERT INTO book (book,writer, year, number) VALUES (?,?,?,?);");

                qry.addBindValue(book);
                qry.addBindValue(writer);
                qry.addBindValue(year);
                qry.addBindValue(number);

                if(qry.exec())
                    ui->notice->setText(book + " added");
            }
        }
        else
            ui->notice->setText(book + " not add");

    }
    else {
        qry.prepare("create table book "
                    "(book text, "
                    "writer text, "
                    "year integer, "
                    "number integer)");
        qry.exec();

        qry.prepare("INSERT INTO book (book,writer, year, number) VALUES (?,?,?,?);");

        qry.addBindValue(book);
        qry.addBindValue(writer);
        qry.addBindValue(year);
        qry.addBindValue(number);

        if(qry.exec())
            ui->notice->setText(book + " added");
        else
            ui->notice->setText(book + " not add");

    }

    connClose(mydb);

    ui->Book->setText("");
    ui->Writer->setText("");
    ui->number->setText("");
    ui->year->setText("");
}


void User::on_newMember_clicked()
{
    Member *member = new Member(this);
    member->show();
}


void User::on_logout_clicked()
{
    this->close();

    MainWindow *login = new MainWindow(this);
    login->show();
}




void User::on_rent_clicked()
{
    Rent *rent = new Rent(this);
    rent->show();
}

