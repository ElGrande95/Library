#ifndef RENT_HH
#define RENT_HH

#include <QDialog>

namespace Ui {
class Rent;
}

class Rent : public QDialog
{
    Q_OBJECT

public:
    explicit Rent(QWidget *parent = nullptr);
    ~Rent();

private:
    Ui::Rent *ui;
};

#endif // RENT_HH
