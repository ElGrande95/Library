#include "member.hh"
#include "ui_member.h"
#include "functions.hh"
#include <QString>

Member::Member(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Member)
{
    ui->setupUi(this);
}

Member::~Member()
{
    delete ui;
}

void Member::on_pushButton_clicked()
{
    QString name = space(ui->name->text());
    QString surname = space(ui->surname->text());
    int id;
    int contact = ui->contact->text().toInt();

    QSqlDatabase mydb;
    connOpen(mydb);

    QSqlQuery qry;


    if ( mydb.tables().contains( QLatin1String("member") )) {

        qry.prepare("select count(*) from member ");
        qry.exec();
        qry.next();
        id = qry.value(0).toInt()+1;

        qry.prepare("INSERT INTO member (idMember,name, surname, contact) VALUES (?,?,?,?);");

        qry.addBindValue(id);
        qry.addBindValue(name);
        qry.addBindValue(surname);
        qry.addBindValue(contact);

        if(qry.exec()){
            ui->notice->setText(name + " " + surname + " added");
        }
        else
            ui->notice->setText(name + " " + surname + " not add");

    }
    else {
        qry.prepare("create table member "
                    "(idMember integer, "
                    "name text, "
                    "surname text, "
                    "contact integer);");
        qry.exec();

        qry.prepare("INSERT INTO member (idMember,name, surname, contact) VALUES (?,?,?,?);");

        qry.addBindValue(1);
        qry.addBindValue(name);
        qry.addBindValue(surname);
        qry.addBindValue(contact);

        if(qry.exec()){
            ui->notice->setText(name + " " + surname + " added");
        }
        else
            ui->notice->setText(name + " " + surname + " not add");
    }

    connClose(mydb);

    ui->name->setText("");
    ui->surname->setText("");
    ui->contact->setText("");
}
