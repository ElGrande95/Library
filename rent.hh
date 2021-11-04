#ifndef RENT_HH
#define RENT_HH

#include <QDialog>
#include "functions.hh"
#include <QStandardItemModel>
#include <QMessageBox>


namespace Ui {
class Rent;
}

class Rent : public QDialog
{
    Q_OBJECT

public:
    explicit Rent(QWidget *parent = nullptr);
    ~Rent();

private slots:

    void on_next_clicked();

    void on_Back_clicked();

    void on_book_textEdited(const QString &text);

    void on_writer_textEdited(const QString &text);

    void on_rentBook_clicked();

    void on_showBooks_clicked();

    void on_showMember_clicked();

    void on_table_clicked(const QModelIndex &index);

private:
    Ui::Rent *ui;
    QSqlTableModel *model;

};

#endif // RENT_HH
