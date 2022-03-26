#ifndef CLIENTDIALOGFEN_H
#define CLIENTDIALOGFEN_H


#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

class clientDialogFen : public QDialog
{
    Q_OBJECT
public:
    clientDialogFen(QWidget *parent);

//signals:
//    void clientAdded();

private slots:
    void ajouterClient();

private:
    QLineEdit *nom;
    QLineEdit *prenom;
    QLineEdit *quartier;
    QLineEdit *rue;
    QLineEdit *numMaison;

    QFormLayout *formLayout;

    QVBoxLayout *layoutPrincipal;

    QPushButton *ajouter;

    QLabel *entete;

};

#endif // CLIENTDIALOGFEN_H
