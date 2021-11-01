#ifndef USER_HH
#define USER_HH

#include <QDialog>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

    void setLabelTitle(const QString& title);

private slots:
    void on_addBook_clicked();


    void on_newMember_clicked();

    void on_logout_clicked();


    void on_rent_clicked();

private:
    Ui::User *ui;


};

#endif // USER_HH
