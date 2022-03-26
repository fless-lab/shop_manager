#include "mysqlconnect.h"
#include <QSqlQuery>
#include <QDebug>
MysqlConnect::MysqlConnect()
{
    factureDB = QSqlDatabase::addDatabase("QMYSQL");

    factureDB.setHostName("localhost");
    factureDB.setDatabaseName("QtFactureDB");
    factureDB.setUserName("root");
    factureDB.setPassword("");


    if(factureDB.open()){
        qDebug()<<"Ok - Ouverture de la base de données";

        QSqlQuery requete;
        if(requete.exec("SELECT * FROM QtFactureDB")){
            qDebug()<<"Ok - requete";

            while(requete.next()){
                qDebug()<<requete.value("nom")<<" "<<requete.value("prenom")<<" "<<requete.value("quartier")<<" "<<requete.value("rue")<<" "<<requete.value("numero_maison");
            }
        }else{
            qDebug()<<"Echec de la requete";
            qDebug()<<requete.lastError();
        }
        factureDB.close();

    }else{
        qDebug()<<"Echec d'ouverture de la db";
        qDebug()<<factureDB.lastError();
    }
}
