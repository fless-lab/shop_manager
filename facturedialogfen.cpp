#include "facturedialogfen.h"
#include "fenprincipale.h"
#include <QSpinBox>
#include <QMessageBox>
#include <QDateTime>
#include "facture.h"

factureDialogFen::factureDialogFen(QWidget *parent) : QDialog(parent)
{
    //Connection
    FenPrincipale conn;

    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(client class)";
    }else{
        qDebug()<<"Connection estabished (Facture)";
    }


    setWindowTitle(QString::fromUtf8("Ajout d'une nouvelle facture"));
    setFixedSize(650,500);

    quantiteArticle = new QSpinBox;
    listeArticle = new QComboBox;
    listeClient = new QComboBox;




    //quantiteArticle->setValidator(new QIntValidator(1,1000,this));

    formLayout = new QFormLayout;
    formLayout->addRow("Choisissez le client : ",listeClient);
    formLayout->addRow("Choiosissez l'article : ",listeArticle);
    formLayout->addRow("Quelle est la quantité de l'article  : ",quantiteArticle);


    entete = new QLabel("Veuillez renseigner les champs ci-dessous pour enregistrer une nouvelle facture\n\n");

    //Client comboList
    QSqlQueryModel *queryModelFacture_client = new QSqlQueryModel();
    QSqlQuery *queryFacture_client = new QSqlQuery(conn.mydb);

    queryFacture_client->prepare("select nom from clients");
    queryFacture_client->exec();
    queryModelFacture_client->setQuery(*queryFacture_client);

    listeClient->setModel(queryModelFacture_client);

    //Article comboList
    QSqlQueryModel *queryModelFacture_article = new QSqlQueryModel();
    QSqlQuery *queryFacture_article = new QSqlQuery(conn.mydb);

    queryFacture_article->prepare("select libelle from articles");
    queryFacture_article->exec();
    queryModelFacture_article->setQuery(*queryFacture_article);

    listeArticle->setModel(queryModelFacture_article);

    ajouter = new QPushButton("Valider la facture");
    ajouter->setCursor(Qt::PointingHandCursor);

    layoutPrincipal = new QVBoxLayout;

    layoutPrincipal->addWidget(entete,Qt::AlignLeading);
    layoutPrincipal->addLayout(formLayout,Qt::AlignCenter);
    layoutPrincipal->addWidget(ajouter);

    setLayout(layoutPrincipal);
    QWidget::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterFacture()));
}

void factureDialogFen::ajouterFacture(){
    FenPrincipale conn;

    int id_article,id_client,qte;

    qte = quantiteArticle->value();
    id_article = listeArticle->currentIndex();
    id_client = listeClient->currentIndex();
    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(add facture btn)";
    }

    QSqlQuery query;
    QDateTime timestamp = QDateTime::currentDateTimeUtc();
    QString created_at = timestamp.toString("dd-MM-yyyy hh:mm:ss");
    qDebug()<<"Before insert query";
    query.prepare("INSERT INTO factures (id_article,id_client,quantite_article,created_at)"
        " VALUES(?,?,?,?)");
    query.addBindValue(id_article);
    query.addBindValue(id_client);
    query.addBindValue(qte);
    query.addBindValue(created_at);
    qDebug()<<"After insert query";
    qDebug()<<timestamp;



    if(query.exec()){
        qDebug()<<"Client Inserted successfuly";
        QMessageBox::about(0,"Enregistrement reussie","La facture à été enregistré avec succès");
        conn.sqliteConClose();
    }else{
        qDebug()<<"Client insertion error";
        qDebug()<< query.lastError();
        QMessageBox::critical(0, "Erreur d'enregistrement" , query.lastError().text());
    }
}



