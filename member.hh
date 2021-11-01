#ifndef MEMBER_HH
#define MEMBER_HH

#include <QDialog>

namespace Ui {
class Member;
}

class Member : public QDialog
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = nullptr);
    ~Member();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Member *ui;
};

#endif // MEMBER_HH
