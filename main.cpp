#include <QApplication>
#include <QStyleFactory>
#include "fenprincipale.h"

int main(int argc , char *argv[]){
    QApplication app(argc,argv);

    FenPrincipale fenetre;
    QApplication::setStyle(QStyleFactory::create("fusion")); //Un nouveau look
    fenetre.show();

    return app.exec();
}
