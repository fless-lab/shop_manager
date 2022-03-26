#ifndef FACTUREDIALOGFEN_H
#define FACTUREDIALOGFEN_H

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
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>

class factureDialogFen : public QDialog
{
    Q_OBJECT
public:
    factureDialogFen(QWidget *parent);

private slots:
    void ajouterFacture();

private:
    QSpinBox *quantiteArticle;
    QComboBox *listeClient;
    QComboBox *listeArticle;

    QFormLayout *formLayout;

    QVBoxLayout *layoutPrincipal;

    QPushButton *ajouter;

    QLabel *entete;
};

#endif // FACTUREDIALOGFEN_H
