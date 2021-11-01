#include "rent.hh"
#include "ui_rent.h"

Rent::Rent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rent)
{
    ui->setupUi(this);
}

Rent::~Rent()
{
    delete ui;
}
