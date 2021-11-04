#include "rent.hh"
#include "ui_rent.h"
#include <QTableView>

Rent::Rent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rent)
{
    ui->setupUi(this);

    model = new QSqlTableModel();

    QSqlDatabase mydb;
    connOpen(mydb);
    QSqlQuery *qry = new QSqlQuery(mydb);

    qry->prepare("select * from book");
    qry->exec();

    model = new QSqlTableModel();
    model->setTable("book");
    model->select();

    ui->table->setModel(model);
    ui->table->model()->sort(1);

    connClose(mydb);

}

Rent::~Rent()
{
    delete ui;
}



void Rent::on_next_clicked()
{
    QString book = space(ui->book->text());
    QString writer = space(ui->writer->text());

    QModelIndex index = ui->table->currentIndex();

    if(index.isValid()){
        for(int i = index.row()+1; i < ui->table->model()->rowCount(); i++){

            QModelIndex indexB = ui->table->model()->index(i,0);
            QModelIndex indexW = ui->table->model()->index(i,1);

            if((ui->table->model()->data(indexB).toString()).contains(book) &&
                    (ui->table->model()->data(indexW).toString()).contains(writer)) {

                ui->table->setCurrentIndex(indexB);
                return;
            }
        }
        for(int i = 0; i <= index.row(); i++){

            QModelIndex indexB = ui->table->model()->index(i,0);
            QModelIndex indexW = ui->table->model()->index(i,1);

            if((ui->table->model()->data(indexB).toString()).contains(book) &&
                    (ui->table->model()->data(indexW).toString()).contains(writer)) {

                ui->table->setCurrentIndex(indexB);
                return;
            }
        }
    }
    else {
        QMessageBox::warning(this, "Warning", "No cell selected!");
    }

}


void Rent::on_Back_clicked()
{
    QString book = space(ui->book->text());
    QString writer = space(ui->writer->text());

    QModelIndex index = ui->table->currentIndex();

    if(index.isValid()){
        for(int i = index.row()-1; i >= 0; i--){

            QModelIndex indexB = ui->table->model()->index(i,0);
            QModelIndex indexW = ui->table->model()->index(i,1);

            if((ui->table->model()->data(indexB).toString()).contains(book) &&
                    (ui->table->model()->data(indexW).toString()).contains(writer)) {

                ui->table->setCurrentIndex(indexB);
                return;
            }
        }
        for(int i = ui->table->model()->rowCount()-1; i >= index.row(); i--){

            QModelIndex indexB = ui->table->model()->index(i,0);
            QModelIndex indexW = ui->table->model()->index(i,1);

            if((ui->table->model()->data(indexB).toString()).contains(book) &&
                    (ui->table->model()->data(indexW).toString()).contains(writer)) {

                ui->table->setCurrentIndex(indexB);
                return;
            }
        }
    }
    else {
        QMessageBox::warning(this, "Warning", "No cell selected!");
    }
}


void Rent::on_book_textEdited(const QString &text)
{
    QString book = space(text);
    QString writer = space(ui->writer->text());

    if (book.isEmpty() && writer.isEmpty()){
        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        return;
    }

    for (int i=0; i < ui->table->model()->rowCount(); i++){

        QModelIndex indexB = ui->table->model()->index(i,0);
        QModelIndex indexW = ui->table->model()->index(i,1);

        if((ui->table->model()->data(indexB).toString()).contains(book) &&
                (ui->table->model()->data(indexW).toString()).contains(writer)) {

            ui->table->setCurrentIndex(indexB);
            return;
        }
        else {
            QModelIndex *noIndex = new QModelIndex();
            ui->table->setCurrentIndex(*noIndex);
        }
    }

}


void Rent::on_writer_textEdited(const QString &text)
{
    QString writer = space(text);
    QString book = space(ui->book->text());


    if (book.isEmpty() && writer.isEmpty()){
        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        return;
    }

    for (int i=0; i < ui->table->model()->rowCount(); i++){

        QModelIndex indexB = ui->table->model()->index(i,0);
        QModelIndex indexW = ui->table->model()->index(i,1);

        if((ui->table->model()->data(indexB).toString()).contains(book) &&
                (ui->table->model()->data(indexW).toString()).contains(writer)) {

            ui->table->setCurrentIndex(indexB);
            return;
        }
        else {
            QModelIndex *noIndex = new QModelIndex();
            ui->table->setCurrentIndex(*noIndex);
        }
    }
}


void Rent::on_rentBook_clicked()
{

}


void Rent::on_showBooks_clicked()
{
    model = new QSqlTableModel();

    QSqlDatabase mydb;
    connOpen(mydb);
    QSqlQuery *qry = new QSqlQuery(mydb);

    qry->prepare("select * from book");
    qry->exec();

    model = new QSqlTableModel();
    model->setTable("book");
    model->select();

    ui->table->setModel(model);
    ui->table->model()->sort(1);

    connClose(mydb);
}


void Rent::on_showMember_clicked()
{
    model = new QSqlTableModel();

    QSqlDatabase mydb;
    connOpen(mydb);
    QSqlQuery *qry = new QSqlQuery(mydb);

    qry->prepare("select * from member");
    qry->exec();

    model = new QSqlTableModel();
    model->setTable("member");
    model->select();

    ui->table->setModel(model);
    ui->table->model()->sort(0);

    connClose(mydb);
}


void Rent::on_table_clicked(const QModelIndex &index)
{
    ui->book->setText(ui->table->model()->data(ui->table->model()->index(index.row(),0)).toString());
    ui->writer->setText(ui->table->model()->data(ui->table->model()->index(index.row(),1)).toString());

}

