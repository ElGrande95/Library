#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include <iostream>
#include <QString>
#include <QtSql>

QString space(const QString &s);

void connClose(QSqlDatabase& mydb);
bool connOpen(QSqlDatabase& mydb);

#endif // FUNCTIONS_HH
