#include "articledialogfen.h"
#include "fenprincipale.h"
#include <QDateTime>
#include <QMessageBox>

articleDialogFen::articleDialogFen(QWidget *parent) : QDialog(parent)
{
    //Connection
    FenPrincipale conn;

    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(article class)";
    }else{
        qDebug()<<"Connection estabished";
    }



    setWindowTitle(QString::fromUtf8("Ajout d'un nouvel article"));
    setFixedSize(650,300);


    reference = new QLineEdit;
    libelle = new QLineEdit;
    categorie = new QLineEdit;
    prixUnitaire = new QLineEdit;

    prixUnitaire->setValidator(new QDoubleValidator(this));

    formLayout = new QFormLayout;
    formLayout->addRow("Reference de l'article : ",reference);
    formLayout->addRow("Libelle de l'article : ",libelle);
    formLayout->addRow("Categorie de l'article : ",categorie);
    formLayout->addRow("Prix unitaire de l'article : ",prixUnitaire);


    ajouter = new QPushButton("Ajouter");
    ajouter->setCursor(Qt::PointingHandCursor);


    entete = new QLabel("Veuillez renseigner les champs ci-dessous pour ajouter un nouvel article à la catalogue\n\n");

    QWidget::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterArticle()));

    layoutPrincipal = new QVBoxLayout;

    layoutPrincipal->addWidget(entete,Qt::AlignLeading);
    layoutPrincipal->addLayout(formLayout,Qt::AlignCenter);
    layoutPrincipal->addWidget(ajouter);

    setLayout(layoutPrincipal);
}

void articleDialogFen::ajouterArticle(){
    FenPrincipale conn;

    QString vreference,vlibelle,vcategorie,vprixUnitaire;
    vreference = reference->text();
    vlibelle = libelle->text();
    vcategorie = categorie->text();
    vprixUnitaire = prixUnitaire->text();

    if(!conn.sqliteConOpen()){
        qDebug()<<"Connection error(add client btn)";
    }

    QSqlQuery query;

    QDateTime timestamp = QDateTime::currentDateTimeUtc();
    QString created_at = timestamp.toString("dd-MM-yyyy hh:mm:ss");
    qDebug()<<"Before insert query";
    query.prepare("INSERT INTO articles (reference,libelle,categorie,prixUnitaire,created_at)"
        " VALUES(?,?,?,?,?)");
    query.addBindValue(vreference);
    query.addBindValue(vlibelle);
    query.addBindValue(vcategorie);
    query.addBindValue(vprixUnitaire);
    query.addBindValue(created_at);
    qDebug()<<"After insert query";
    qDebug()<<timestamp;

    if(query.exec()){
        qDebug()<<"Client Inserted successfuly";
        QMessageBox::about(0,"Enregistrement reussie","L'article a bien été ajouté avec succès");
        conn.sqliteConClose();
    }else{
        qDebug()<<"Article insertion error";
        qDebug()<< query.lastError();
        QMessageBox::critical(0, "Erreur d'enregistrement" , query.lastError().text());
    }
}

