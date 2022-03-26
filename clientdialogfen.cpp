#include "clientdialogfen.h"
#include <QValidator>
#include <QMessageBox>
#include <QVector>
#include "fenprincipale.h"
#include <QDateTime>

clientDialogFen::clientDialogFen(QWidget *parent) : QDialog(parent)
{
    //Connection
    FenPrincipale conn;

    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(client class)";
    }else{
        qDebug()<<"Connection estabished";
    }



    setWindowTitle(QString::fromUtf8("Ajout d'un nouveau client"));
    setFixedSize(650,300);


    nom = new QLineEdit;
    prenom = new QLineEdit;
    quartier = new QLineEdit;
    rue = new QLineEdit;
    numMaison = new QLineEdit;

    numMaison->setValidator(new QIntValidator(this));

    formLayout = new QFormLayout;
    formLayout->addRow("Votre &nom : ",nom);
    formLayout->addRow("Votre &prenom : ",prenom);
    formLayout->addRow("Votre &quartier : ",quartier);
    formLayout->addRow("Votre &rue : ",rue);
    formLayout->addRow("Votre &numero_de_maison : ",numMaison);


    ajouter = new QPushButton("Ajouter");
    ajouter->setCursor(Qt::PointingHandCursor);


    entete = new QLabel("Veuillez renseigner les champs ci-dessous pour ajouter un nouveau client\n\n");

    QWidget::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterClient()));

    layoutPrincipal = new QVBoxLayout;

    layoutPrincipal->addWidget(entete,Qt::AlignLeading);
    layoutPrincipal->addLayout(formLayout,Qt::AlignCenter);
    layoutPrincipal->addWidget(ajouter);

    setLayout(layoutPrincipal);

    //TO DO : IL ME  faut rajouter un bouton qui permet de rafraichir la tableview lorsqu'une nouvelle donnée est inseré...ou rendre ça automatique avec un signal (emit) lorsqu'une données est insérée .. enfin bon..
}


void clientDialogFen::ajouterClient(){
    FenPrincipale conn;

    QString vnom,vprenom,vquartier,vrue,vnum_maison;
    //int vnum_maison;
    vnom = nom->text();
    vprenom = prenom->text();
    vquartier = quartier->text();
    vrue = rue->text();
    vnum_maison = numMaison->text();

    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(add client btn)";
    }

    QSqlQuery query;

    QDateTime timestamp = QDateTime::currentDateTimeUtc();
    QString created_at = timestamp.toString("dd-MM-yyyy hh:mm:ss");
    qDebug()<<"Before insert query";
    query.prepare("INSERT INTO clients (nom,prenom,quartier,rue,num_maison,created_at)"
        " VALUES(?,?,?,?,?,?)");
    query.addBindValue(vnom);
    query.addBindValue(vprenom);
    query.addBindValue(vquartier);
    query.addBindValue(vrue);
    query.addBindValue(vnum_maison);
    query.addBindValue(created_at);
    qDebug()<<"After insert query";
    qDebug()<<timestamp;


    if(query.exec()){
        qDebug()<<"Client Inserted successfuly";
        QMessageBox::about(0,"Enregistrement reussie","Le client à été enregistré avec succès");
//        emit clientAdded();
        conn.sqliteConClose();
    }else{
        qDebug()<<"Client insertion error";
        qDebug()<< query.lastError();
        QMessageBox::critical(0, "Erreur d'enregistrement" , query.lastError().text());
    }


}

