#ifndef RENT_HH
#define RENT_HH

#include <QDialog>
#include "functions.hh"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class Rent;
}

class Rent : public QDialog
{
    Q_OBJECT

public:
    explicit Rent(QWidget *parent = nullptr);
    ~Rent();

    void showTableModel();
    void showRelTableModel();

    void searchTableModel(const QString &book, const QString &writer);
    void searchRelTableModel(const QString &book, const QString &writer, const QString &id);

private slots:

    void on_next_clicked();

    void on_Back_clicked();

    void on_book_textEdited(const QString &text);

    void on_writer_textEdited(const QString &text);

    void on_rentBack_clicked();

    void on_table_clicked(const QModelIndex &index);

    void on_showBooksMember_toggled(bool checked);

    void on_id_textEdited(const QString &text);

private:
    Ui::Rent *ui;
    QSqlTableModel *model;
    QSqlRelationalTableModel *modelRel;

};

#endif // RENT_HH
