#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
class FenPrincipale : public QMainWindow
{
    Q_OBJECT
public:
    FenPrincipale();
    QSqlDatabase mydb ;
    void sqliteConClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool sqliteConOpen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        const QString path("/Users/fless/QtProjects/FactureQt/db/factureDB.sqlite");

        mydb.setDatabaseName(path);

        if(!mydb.open()){
            qWarning()<<"ERROR : "<<mydb.lastError();
            return false;
        }else{
            qDebug()<<"Connected...";
            return true;
        }
    }
    QString queryDoer(){

    }
private slots:
    void afficherClientModal();
    void loadClientData();
    void afficherArticleModal();
    void loadArticleData();
    void afficherFactureModal();
    void loadFactureData();
    void genererFactBtnClicked();
//    void refreshClientTable();
private:
    QTabWidget *onglets;

    QWidget *articlesUI;
    QWidget *facturesUI;
    QWidget *clientsUI;

    QVBoxLayout *clientLayout;
    QVBoxLayout *factureLayout;
    QVBoxLayout *articleLayout;

    QPushButton *showAddClientFormBtn;
    QPushButton *loadClientDataBtn;
    QPushButton *showAddArticleFormBtn;
    QPushButton *loadArticleDataBtn;
    QPushButton *showAddFactureFormBtn;
    QPushButton *loadFactureDataBtn;

    //QTableWidget *tableau;
    QTableView *tableauClient;
    QTableView *tableauArticle;
    QTableWidget* tableauFacture ;

};

#endif // FENPRINCIPALE_H
