#include "fenprincipale.h"
#include <QPushButton>
#include <QDialog>
#include "clientdialogfen.h"
#include "articledialogfen.h"
#include "facturedialogfen.h"
#include <vector>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "facture.h"




FenPrincipale::FenPrincipale() : QMainWindow()
{

    setWindowTitle(QString::fromUtf8("Gestion des Factures d'une entreprise"));
    setFixedSize(750,500);

    onglets = new QTabWidget(this);

    //Connection
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    const QString path("/Users/fless/QtProjects/FactureQt/db/factureDB.sqlite");

    mydb.setDatabaseName(path);

    if(!mydb.open()){
        qWarning()<<"ERROR : "<<mydb.lastError();
    }else{
        qDebug()<<"Connected...";
    }

    QSqlQuery create_table_client("CREATE Table clients (id INTEGER PRIMARY KEY,nom VARCHAR(20) NOT NULL,prenom VARCHAR(20) NOT NULL,quartier VARCHAR(20) NOT NULL,rue VARCHAR(20) NOT NULL,num_maison VARCHAR(5) NOT NULL,created_at VARCHAR(30))");
    if(!create_table_client.isActive()){
        qWarning()<<"ERROR : "<<create_table_client.lastError().text();
    }else{
        qDebug()<<"Table clients created";
    }

    QSqlQuery create_table_article("CREATE Table articles (id INTEGER PRIMARY KEY,reference VARCHAR(15) UNIQUE NOT NULL,libelle VARCHAR(30) NOT NULL,categorie VARCHAR(20) NOT NULL,prixUnitaire VARCHAR(20) NOT NULL,created_at VARCHAR(30))");
    if(!create_table_article.isActive()){
        qWarning()<<"ERROR : "<<create_table_article.lastError().text();
    }else{
        qDebug()<<"Table articles created";
    }

    QSqlQuery create_table_facture("CREATE Table factures (id INTEGER PRIMARY KEY,id_article INTEGER(11),id_client INTEGER(11),quantite_article INTEGER(11),created_at VARCHAR(30))");
    if(!create_table_facture.isActive()){
        qWarning()<<"ERROR : "<<create_table_article.lastError().text();
    }else{
        qDebug()<<"Table factures created";
    }

    /************ CLIENT *************/
    clientsUI = new QWidget;

    clientLayout = new QVBoxLayout;

    QSqlQueryModel *queryModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(mydb);



    query->prepare("select * from clients");
    query->exec();
    queryModel->setQuery(*query);
    queryModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    queryModel->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    queryModel->setHeaderData(2,Qt::Horizontal,tr("Prenom"));
    queryModel->setHeaderData(3,Qt::Horizontal,tr("Quartier"));
    queryModel->setHeaderData(4,Qt::Horizontal,tr("Rue"));
    queryModel->setHeaderData(5,Qt::Horizontal,tr("Numero de maison"));
    queryModel->setHeaderData(6,Qt::Horizontal,tr("Date de creation"));

//    queryModel->setQuery(queryModel->query());

    tableauClient = new QTableView;
    tableauClient->setModel(queryModel);


    mydb.close();
    QHBoxLayout *layoutTableau = new QHBoxLayout;
    layoutTableau->addWidget(tableauClient);

    showAddClientFormBtn = new QPushButton("Ajouter un nouveau client");
    showAddClientFormBtn->setCursor(Qt::PointingHandCursor);
    loadClientDataBtn = new QPushButton("Charger les données");
    loadClientDataBtn->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *btnLayouts = new QHBoxLayout;


    btnLayouts->addWidget(showAddClientFormBtn);
    btnLayouts->addWidget(loadClientDataBtn);

    clientLayout->addLayout(btnLayouts);
    clientLayout->addWidget(loadClientDataBtn);
    clientLayout->addLayout(layoutTableau);

    clientsUI->setLayout(clientLayout);

    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxx */


    /************ ARTICLE *************/
    articlesUI = new QWidget;
    articleLayout = new QVBoxLayout;

    sqliteConOpen();
    QSqlQueryModel *queryModelArticle = new QSqlQueryModel();
    QSqlQuery *queryArticle = new QSqlQuery(mydb);

    queryArticle->prepare("select * from articles");
    queryArticle->exec();
    queryModelArticle->setQuery(*queryArticle);
    queryModelArticle->setHeaderData(0,Qt::Horizontal,tr("ID"));
    queryModelArticle->setHeaderData(1,Qt::Horizontal,tr("Reference"));
    queryModelArticle->setHeaderData(2,Qt::Horizontal,tr("Libelle"));
    queryModelArticle->setHeaderData(3,Qt::Horizontal,tr("Categorie"));
    queryModelArticle->setHeaderData(4,Qt::Horizontal,tr("Prix Unitaire"));
    queryModelArticle->setHeaderData(5,Qt::Horizontal,tr("Date d'ajout"));

    tableauArticle = new QTableView;
    tableauArticle->setModel(queryModelArticle);

    mydb.close();
    QHBoxLayout *layoutTableauArticle = new QHBoxLayout;
    layoutTableauArticle->addWidget(tableauArticle);

    showAddArticleFormBtn = new QPushButton("Ajouter un nouvel article");
    showAddArticleFormBtn->setCursor(Qt::PointingHandCursor);
    loadArticleDataBtn = new QPushButton("Charger les données");
    loadArticleDataBtn->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *btnLayoutsArticle = new QHBoxLayout;



    btnLayoutsArticle->addWidget(showAddArticleFormBtn);
    btnLayoutsArticle->addWidget(loadArticleDataBtn);

    articleLayout->addLayout(btnLayoutsArticle);
    articleLayout->addWidget(loadArticleDataBtn);
    articleLayout->addLayout(layoutTableauArticle);


    articlesUI->setLayout(articleLayout);
    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxx */


    /************ FACTURE *************/
//    mydb = QSqlDatabase::addDatabase("QSQLITE");
//    const QString path1("/Users/fless/QtProjects/FactureQt/db/factureDB.sqlite");

//    mydb.setDatabaseName(path1);
    sqliteConOpen();
    facturesUI = new QWidget;
    factureLayout = new QVBoxLayout;

    showAddFactureFormBtn = new QPushButton("Faire une nouvelle facture");
    showAddFactureFormBtn->setCursor(Qt::PointingHandCursor);
    loadFactureDataBtn = new QPushButton("Charger les données");
    loadFactureDataBtn->setCursor(Qt::PointingHandCursor);


    QHBoxLayout *btnLayoutsFacture = new QHBoxLayout;

    btnLayoutsFacture->addWidget(showAddFactureFormBtn);
    btnLayoutsFacture->addWidget(loadFactureDataBtn);

    tableauFacture = new QTableWidget();
    tableauFacture->setWindowTitle("Connect to Mysql Database Example");

    QSqlQuery queryFacture("SELECT * FROM factures");

    tableauFacture->setColumnCount(queryFacture.record().count()+1);
    tableauFacture->setRowCount(queryFacture.size());

    int index=0;
    while (queryFacture.next())
    {
//        qDebug()<<queryFacture.value(0).toString();
//        qDebug()<<queryFacture.value(1).toString();
//        qDebug()<<queryFacture.value(2).toString();
//        qDebug()<<"##############";

        tableauFacture->insertRow(index);
//        int id = queryFacture.value(0).toInt();
//        int id_article = queryFacture.value(1).toInt();
//        int id_client = queryFacture.value(2).toInt();
//        int qte = queryFacture.value(3).toInt();
//        qDebug()<<id_article;
//        QSqlQuery queryFA("SELECT libelle FROM articles WHERE id="+id_article);
//        queryFA.addBindValue(id_article);

//        qDebug()<<queryFA.exec();


        tableauFacture->setItem(index,0,new QTableWidgetItem(queryFacture.value(0).toString()));
        tableauFacture->setItem(index,1,new QTableWidgetItem(queryFacture.value(1).toString()));
        tableauFacture->setItem(index,2,new QTableWidgetItem( queryFacture.value(2).toString()));
        tableauFacture->setItem(index,3,new QTableWidgetItem(queryFacture.value(3).toString()));
        tableauFacture->setItem(index,4,new QTableWidgetItem(queryFacture.value(4).toString()));

        QPushButton *btnGenererFact;
        btnGenererFact = new QPushButton("Voir facture",tableauFacture);
        btnGenererFact->setObjectName(QString("%1").arg(tableauFacture->rowCount()));
        btnGenererFact->setCursor(Qt::PointingHandCursor);
        tableauFacture->setCellWidget(index,5,(QWidget*)btnGenererFact);

        connect(btnGenererFact,SIGNAL(clicked()),this,SLOT(genererFactBtnClicked()));

        index++;
    }

    tableauFacture->show();


    QHBoxLayout *layoutTableauFacture = new QHBoxLayout;
    layoutTableauFacture->addWidget(tableauFacture);

    factureLayout->addLayout(btnLayoutsFacture);
    //factureLayout->addWidget(loadFactureDataBtn);
    factureLayout->addLayout(layoutTableauFacture);

    facturesUI->setLayout(factureLayout);
    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxx */





    //Onglets...
    onglets->resize(width(),height());//Le qtabwidget prend la taille de la fenetre...je l'ai fixée :)
    onglets->addTab(articlesUI,"Articles");
    onglets->addTab(clientsUI,"Clients");
    onglets->addTab(facturesUI,"Factures");


    /*CONNECTION : SLOTS/SIGNALS*/
    connect(showAddClientFormBtn, SIGNAL(clicked()), this, SLOT(afficherClientModal()));
    connect(loadClientDataBtn, SIGNAL(clicked()), this, SLOT(loadClientData()));
    connect(showAddArticleFormBtn, SIGNAL(clicked()), this, SLOT(afficherArticleModal()));
    connect(loadArticleDataBtn, SIGNAL(clicked()), this, SLOT(loadArticleData()));
    connect(showAddFactureFormBtn, SIGNAL(clicked()), this, SLOT(afficherFactureModal()));
    connect(loadFactureDataBtn, SIGNAL(clicked()), this, SLOT(loadFactureData()));
}


//SLot qui declenche l'affichage du modal client
void FenPrincipale::afficherClientModal(){
    clientDialogFen *fen = new clientDialogFen(this);
    fen->exec();
}

void FenPrincipale::loadClientData(){

}


//SLot qui declenche l'affichage du modal client
void FenPrincipale::afficherArticleModal(){
    articleDialogFen *fen = new articleDialogFen(this);
    fen->exec();
}

void FenPrincipale::loadArticleData(){

}


void FenPrincipale::afficherFactureModal(){
    factureDialogFen *fen = new factureDialogFen(this);
    fen->exec();
}

void FenPrincipale::loadFactureData(){

}

void FenPrincipale::genererFactBtnClicked(){
    QPushButton *pb = qobject_cast<QPushButton *>(QObject::sender());
    int row = pb->objectName().toInt()-1;

    int id_facture = tableauFacture->item(row,0)->text().toInt();
    int id_article = tableauFacture->item(row,1)->text().toInt();
    int id_client = tableauFacture->item(row,2)->text().toInt();
    int quantite = tableauFacture->item(row,3)->text().toInt();
    QString dateFac = tableauFacture->item(row,4)->text();

    sqliteConOpen();
    QSqlQuery getClientQuery(mydb);
    getClientQuery.prepare("SELECT * FROM clients WHERE id=?");
    getClientQuery.addBindValue(id_client);
    if(!getClientQuery.exec()){
        qDebug()<<"SQL ERROR : "<<getClientQuery.lastError().text();
    }
    getClientQuery.first();

    QString nom_client = getClientQuery.value("nom").toString();
    QString prenom_client = getClientQuery.value("prenom").toString();
    QString qrt_client = getClientQuery.value("quartier").toString();
    QString rue_client = getClientQuery.value("rue").toString();
    QString num_maison_client = getClientQuery.value("num_maison").toString();



    QSqlQuery getArticleQuery(mydb);
    getArticleQuery.prepare("SELECT * FROM articles WHERE id=?");
    getArticleQuery.addBindValue(id_article);
    if(!getArticleQuery.exec()){
        qDebug()<<"SQL ERROR : "<<getArticleQuery.lastError().text();
    }
    getArticleQuery.first();

    int montant_facture = getArticleQuery.value("prixUnitaire").toString().toInt()*quantite;
    QString created_at = tableauFacture->item(row,4)->text();
    qDebug()<<quantite<<" "<<getArticleQuery.value("prixUnitaire").toString()<<" "<<montant_facture;

    facture *factureFen = new facture(this);
    factureFen->setFixedSize(350,300);

    QVBoxLayout *layoutFactFenPrincipale = new QVBoxLayout;

    QFormLayout *formLayoutFact;
    QFormLayout *formLayoutClient;
    QVBoxLayout *layoutPrincipal;
//    QGroupBox *refFacture;
//    QGroupBox *refClient;

    QLineEdit *numeroFacture = new QLineEdit;
    QLineEdit *dateFacture = new QLineEdit;
    QLineEdit *montantFacture = new QLineEdit;

    QLineEdit *nomClient = new QLineEdit;
    QLineEdit *prenomClient = new QLineEdit;
    QLineEdit *qrtClient = new QLineEdit;
    QLineEdit *rueCLient = new QLineEdit;
    QLineEdit *numMaisonClient = new QLineEdit;

    numeroFacture->setDisabled(1);
    dateFacture->setDisabled(1);
    montantFacture->setDisabled(1);
    nomClient->setDisabled(1);
    prenomClient->setDisabled(1);
    qrtClient->setDisabled(1);
    rueCLient->setDisabled(1);
    numMaisonClient->setDisabled(1);

    numeroFacture->setText(QString::number(id_facture));
    dateFacture->setText(dateFac);

    nomClient->setText(nom_client);
    prenomClient->setText(prenom_client);
    qrtClient->setText(qrt_client);
    rueCLient->setText(rue_client);
    numMaisonClient->setText(num_maison_client);

    formLayoutFact = new QFormLayout;
    formLayoutFact->addRow("Numero de Facture : ",numeroFacture);
    formLayoutFact->addRow("Date de Facture : ",dateFacture);
    formLayoutFact->addRow("Montant de Facture : ",montantFacture);

    formLayoutClient = new QFormLayout;
    formLayoutClient->addRow("Nom du client : ",nomClient);
    formLayoutClient->addRow("Prenom du client : ",prenomClient);
    formLayoutClient->addRow("Quartier du client : ",qrtClient);
    formLayoutClient->addRow("Rue du client : ",rueCLient);
    formLayoutClient->addRow("Numero de la maison du client : ",numMaisonClient);

//    refFacture = new QGroupBox("Informations sur la facture", this);
//    refClient = new QGroupBox("Informations sur le client", this);

//    refFacture->setLayout(formLayoutFact);
//    refClient->setLayout(formLayoutClient);

    layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(formLayoutFact);
    layoutPrincipal->addLayout(formLayoutClient);

    layoutFactFenPrincipale->addLayout(layoutPrincipal);
    factureFen->setLayout(layoutFactFenPrincipale);
    factureFen->exec();

//    QDialog descriptionFacture(this);
//    descriptionFacture.setWindowTitle(QString::fromUtf8("Ajout d'une nouvelle facture"));
//    descriptionFacture.setFixedSize(650,300);
//    descriptionFacture.show();
//    QMessageBox::about(0,"Détaile de la facture",getArticleQuery.value("libelle").toString());


//    qDebug()<<tableauFacture->item(row,1)->text();
}



