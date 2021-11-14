#include "rent.hh"
#include "ui_rent.h"
#include <QTableView>

Rent::Rent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rent)
{
    ui->setupUi(this);

    ui->showBooksMember->setCheckable(true);

    showTableModel();
}

Rent::~Rent()
{
    delete ui;
}



void Rent::on_next_clicked()
{
    if(!ui->showBooksMember->isChecked()){

        QString book = space(ui->book->text());
        QString writer = space(ui->writer->text());

        QModelIndex index = ui->table->currentIndex();

        if(index.isValid()){
            for(int i = index.row()+1; i < ui->table->model()->rowCount(); i++){

                QModelIndex indexB = ui->table->model()->index(i,1);
                QModelIndex indexW = ui->table->model()->index(i,2);

                if((ui->table->model()->data(indexB).toString()).contains(book) &&
                        (ui->table->model()->data(indexW).toString()).contains(writer)) {

                    ui->table->setCurrentIndex(indexB);
                    return;
                }
            }
            for(int i = 0; i <= index.row(); i++){

                QModelIndex indexB = ui->table->model()->index(i,1);
                QModelIndex indexW = ui->table->model()->index(i,2);

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
    else {

        QString id = space(ui->id->text());

        QModelIndex index = ui->table->currentIndex();

        if(index.isValid()){
            for(int i = index.row()+1; i < ui->table->model()->rowCount(); i++){

                QModelIndex indexId = ui->table->model()->index(i,0);

                if((ui->table->model()->data(indexId).toString()).contains(id)) {

                    ui->table->setCurrentIndex(indexId);
                    return;
                }
            }
            for(int i = 0; i <= index.row(); i++){

                QModelIndex indexId = ui->table->model()->index(i,0);

                if((ui->table->model()->data(indexId).toString()).contains(id)) {

                    ui->table->setCurrentIndex(indexId);
                    return;
                }
            }
        }
        else {
            QMessageBox::warning(this, "Warning", "No cell selected!");
        }
    }
}


void Rent::on_Back_clicked()
{
    if(!ui->showBooksMember->isChecked()){

        QString book = space(ui->book->text());
        QString writer = space(ui->writer->text());

        QModelIndex index = ui->table->currentIndex();

        if(index.isValid()){
            for(int i = index.row()-1; i >= 0; i--){

                QModelIndex indexB = ui->table->model()->index(i,1);
                QModelIndex indexW = ui->table->model()->index(i,2);

                if((ui->table->model()->data(indexB).toString()).contains(book) &&
                        (ui->table->model()->data(indexW).toString()).contains(writer)) {

                    ui->table->setCurrentIndex(indexB);
                    return;
                }
            }
            for(int i = ui->table->model()->rowCount()-1; i >= index.row(); i--){

                QModelIndex indexB = ui->table->model()->index(i,1);
                QModelIndex indexW = ui->table->model()->index(i,2);

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

    else {
        QString id = space(ui->id->text());

        QModelIndex index = ui->table->currentIndex();

        if(index.isValid()){
            for(int i = index.row()-1; i >= 0; i--){

                QModelIndex indexId = ui->table->model()->index(i,0);

                if((ui->table->model()->data(indexId).toString()).contains(id)) {

                    ui->table->setCurrentIndex(indexId);
                    return;
                }
            }
            for(int i = ui->table->model()->rowCount()-1; i >= index.row(); i--){

                QModelIndex indexId = ui->table->model()->index(i,0);

                if((ui->table->model()->data(indexId).toString()).contains(id)) {

                    ui->table->setCurrentIndex(indexId);
                    return;
                }
            }
        }
        else {
            QMessageBox::warning(this, "Warning", "No cell selected!");
        }
    }
}


void Rent::on_book_textEdited(const QString &text)
{
    QString book = space(text);
    QString writer = space(ui->writer->text());
    QString id = space(ui->id->text());

    if(!ui->showBooksMember->isChecked()){

        searchTableModel(book, writer);
    }
    else {

        searchRelTableModel(book, writer, id);
    }

}


void Rent::on_writer_textEdited(const QString &text)
{
    QString writer = space(text);
    QString book = space(ui->book->text());
    QString id = space(ui->id->text());

    if(!ui->showBooksMember->isChecked()){

        searchTableModel(book,writer);
    }
    else {

        searchRelTableModel(book, writer, id);
    }
}


void Rent::on_rentBack_clicked()
{
    if(!ui->showBooksMember->isChecked()){

        QModelIndex index = ui->table->model()->index(ui->table->currentIndex().row(),0);
        int idBook = ui->table->model()->data(index).toInt();
        int idMember = ui->id->text().toInt();
        QModelIndex indexNum = ui->table->model()->index(index.row(),4);
        int number = ui->table->model()->data(indexNum).toInt();

        if(number <= 0){
            QMessageBox::warning(this,"Warning", "Have not book!");
            return;
        }

        QSqlDatabase mydb;
        connOpen(mydb);

        QSqlQuery qry;

        qry.prepare("select * from member where idMember = '"+QString::number(idMember)+"' ;");
        qry.exec();
        if(!qry.next()){
            connClose(mydb);
            QMessageBox::warning(this,"Warning", "Wrong idMember");
            return;
        }

        qry.prepare("select count(*) from rent where idMember = '"+QString::number(idMember)+"' ;");
        qry.exec();
        qry.next();
        if(qry.value(0).toInt() >= 10){

            connClose(mydb);
            QMessageBox::warning(this,"Warning", "Limit of books is 10!");
            return;
        }

        if ( !mydb.tables().contains( QLatin1String("rent") )) {

            qry.prepare("create table rent "
                        "(idMember integer, "
                        "idBook integer);");
            qry.exec();
        }

        qry.prepare("select count(*) from rent where idBook = '"+QString::number(idBook)+"' "
                                                "and idMember = '"+QString::number(idMember)+"' ;");
        qry.exec();
        qry.next();
        if(qry.value(0).toInt() != 0){

            connClose(mydb);
            QMessageBox::warning(this,"Warning", "You have this book!");
            return;
        }

        qry.prepare("INSERT INTO rent (idMember,idBook) VALUES (?,?);");

        qry.addBindValue(idMember);
        qry.addBindValue(idBook);

        if(qry.exec()){

            qry.prepare("UPDATE book SET number = number -1"
                        "WHERE idBook = '"+QString::number(idBook)+"';");

            qry.exec();

            ui->table->model()->setData(indexNum, number-1, Qt::EditRole);
            index = ui->table->model()->index(index.row(),1);
            ui->notice->setText(ui->table->model()->data(index).toString() + " rented.");
        }
        else{
            index = ui->table->model()->index(index.row(),1);
            ui->notice->setText(ui->table->model()->data(index).toString() + " not rent.");
            return;
        }

        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        ui->book->setText("");
        ui->writer->setText("");
        connClose(mydb);
    }


    else {
        QModelIndex index = ui->table->currentIndex();
        QModelIndex indexIdBook = ui->table->model()->index(index.row(),1);
        QModelIndex indexIdMember = ui->table->model()->index(index.row(),0);

        int idBook = ui->table->model()->data(indexIdBook).toInt();
        int idMember = ui->table->model()->data(indexIdMember).toInt();

        QSqlDatabase mydb;
        connOpen(mydb);

        QSqlQuery qry;

        qry.prepare("delete from rent where idMember = '"+QString::number(idMember)+"'"
                                         " and idBook = '"+QString::number(idBook)+"' ;");
        qry.exec();

        qry.prepare("UPDATE book SET number = number + 1 WHERE idBook = '"+QString::number(idBook)+"' ;");
        if(qry.exec())
            qDebug() << 1;

        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        ui->book->setText("");
        ui->writer->setText("");
        connClose(mydb);

        showRelTableModel();

    }
}


void Rent::on_table_clicked(const QModelIndex &index)
{
    if(!ui->showBooksMember->isChecked()){

        ui->book->setText(ui->table->model()->data(ui->table->model()->index(index.row(), 1)).toString());
        ui->writer->setText(ui->table->model()->data(ui->table->model()->index(index.row(), 2)).toString());
    }
    else {
        ui->book->setText(ui->table->model()->data(ui->table->model()->index(index.row(), 2)).toString());
        ui->writer->setText(ui->table->model()->data(ui->table->model()->index(index.row(), 3)).toString());
        ui->id->setText(ui->table->model()->data(ui->table->model()->index(index.row(), 0)).toString());
    }
}


void Rent::on_showBooksMember_toggled(bool checked)
{
    if(checked){
        showRelTableModel();
    }
    else {
        showTableModel();
    }

    ui->id->setText("");
    ui->book->setText("");
    ui->writer->setText("");
}


void Rent::showTableModel(){
    model = new QSqlTableModel();

    QSqlDatabase mydb;
    connOpen(mydb);

    model = new QSqlTableModel();
    model->setTable("book");
    model->select();

    ui->table->setModel(model);
    ui->table->model()->sort(2);

    connClose(mydb);
}

void Rent::showRelTableModel()
{
    modelRel = new QSqlRelationalTableModel();

    QSqlDatabase mydb;
    connOpen(mydb);

    modelRel = new QSqlRelationalTableModel();
    modelRel->setTable("rent");
    modelRel->setRelation(1, QSqlRelation("book", "idBook","idBook, book, writer, year"));
    modelRel->select();

    ui->table->setModel(modelRel);
    ui->table->model()->sort(0);

    ui->notice->setText("");

    connClose(mydb);
}

void Rent::searchTableModel(const QString &book, const QString &writer)
{
    if (book.isEmpty() && writer.isEmpty()){
        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        return;
    }

    for (int i=0; i < ui->table->model()->rowCount(); i++){
        QModelIndex indexB = ui->table->model()->index(i,1);
        QModelIndex indexW = ui->table->model()->index(i,2);

        if((ui->table->model()->data(indexB).toString()).contains(book) &&
                (ui->table->model()->data(indexW).toString()).contains(writer)) {

            ui->table->setCurrentIndex(ui->table->model()->index(i,0));
            return;
        }
        else {
            QModelIndex *noIndex = new QModelIndex();
            ui->table->setCurrentIndex(*noIndex);
        }
    }
}

void Rent::searchRelTableModel(const QString &book, const QString &writer, const QString &id)
{
    if (book.isEmpty() && writer.isEmpty() && id.isEmpty()){
        QModelIndex *noIndex = new QModelIndex();
        ui->table->setCurrentIndex(*noIndex);

        return;
    }

    for (int i=0; i < ui->table->model()->rowCount(); i++){

        QModelIndex indexB = ui->table->model()->index(i,2);
        QModelIndex indexW = ui->table->model()->index(i,3);
        QModelIndex indexId = ui->table->model()->index(i,0);

        if((ui->table->model()->data(indexB).toString()).contains(book) &&
                (ui->table->model()->data(indexW).toString()).contains(writer) &&
                (ui->table->model()->data(indexId).toString()).contains(id)) {

            ui->table->setCurrentIndex(indexId);
            return;
        }
        else {
            QModelIndex *noIndex = new QModelIndex();
            ui->table->setCurrentIndex(*noIndex);
        }
    }
}


void Rent::on_id_textEdited(const QString &text)
{
    QString writer = space(ui->writer->text());
    QString book = space(ui->book->text());
    QString id = space(text);

    if(ui->showBooksMember->isChecked()){

        searchRelTableModel(book, writer, id);
    }
}

