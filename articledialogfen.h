#ifndef ARTICLEDIALOGFEN_H
#define ARTICLEDIALOGFEN_H

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

class articleDialogFen : public QDialog
{
    Q_OBJECT
public:
    articleDialogFen(QWidget *parent);

private slots:
    void ajouterArticle();

private:
    QLineEdit *reference;
    QLineEdit *libelle;
    QLineEdit *categorie;
    QLineEdit *prixUnitaire;

    QFormLayout *formLayout;

    QVBoxLayout *layoutPrincipal;

    QPushButton *ajouter;

    QLabel *entete;
};

#endif // ARTICLEDIALOGFEN_H
