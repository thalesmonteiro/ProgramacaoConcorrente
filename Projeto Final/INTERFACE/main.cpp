#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <unistd.h>
#include "Consumidor.h"
#include "Produtor.h"
#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{

    //Produtor *p = new Produtor;
    //Consumidor *c = new Consumidor(*p);
    //Consumidor *c1 = new Consumidor(*p);

    /*p->addConsumidor(c);
    p->addConsumidor(c1);
    c->start(4000);
    c1->start(5000);
    p->start();
*/

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Proxy de Vídeo");
    w.show();

    //sleep(2000000);

    return a.exec();
}
