#include "functions.hh"
#include <QDebug>

void connClose(QSqlDatabase& mydb)
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    qDebug() << "Close database connection";

}

bool connOpen(QSqlDatabase& mydb)
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/elgrande/Desktop/Qt/Library/library.db");
    if(!mydb.open()){
        qDebug() << "Faild database connection";
        return false;
    }
        else {
        qDebug() << "Succes database connection";
        return true;
    }
}




QString space(const QString &s)
{
    QString s2="";
    int n= s.size();

    for(int i=0; i < n; i++){
        if (s[i] != ' '){
            while (s[i] != ' ') {

                s2 += s[i];
                i++;
                if (i==n)
                    return s2;
            }
        s2+=' ';
        }
    }
    return s2.remove(s2.size()-1, 1);
}


