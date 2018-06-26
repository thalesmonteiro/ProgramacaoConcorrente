#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p = new Produtor();
    c1 = new Consumidor(*p);
    c2 = new Consumidor(*p);
    c3 = new Consumidor(*p);
    c4 = new Consumidor(*p);
    c5 = new Consumidor(*p);
    c6 = new Consumidor(*p);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botaoServidor_clicked()
{
    QString portaServidor(ui->portaServidor->text());
    qDebug() << "Iniciando servidor na porta: " << portaServidor;
    int pServidor = portaServidor.toInt();
    p->start(pServidor);
}

void MainWindow::on_botaoCliente1_clicked()
{
    p->addConsumidor(c1);
    QString portaCliente1(ui->portaCliente1->text());
    qDebug() << "Testando porta cliente1: " << portaCliente1;
    int pCliente1 = portaCliente1.toInt();
    c1->start(pCliente1);
}

void MainWindow::on_botaoCliente2_clicked()
{
    p->addConsumidor(c2);
    QString portaCliente2(ui->portaCliente2->text());
    qDebug() << "Testando porta cliente2: " << portaCliente2;
    int pCliente2 = portaCliente2.toInt();
    c2->start(pCliente2);
}

void MainWindow::on_botaoCliente3_clicked()
{
    p->addConsumidor(c3);
    QString portaCliente3(ui->portaCliente3->text());
    qDebug() << "Testando porta cliente3: " << portaCliente3;
    int pCliente3 = portaCliente3.toInt();
    c3->start(pCliente3);
}

void MainWindow::on_botaoCliente4_clicked()
{
    p->addConsumidor(c4);
    QString portaCliente4(ui->portaCliente4->text());
    qDebug() << "Testando porta cliente4: " << portaCliente4;
    int pCliente4 = portaCliente4.toInt();
    c4->start(pCliente4);
}

void MainWindow::on_botaoCliente5_clicked()
{
    p->addConsumidor(c5);
    QString portaCliente5(ui->portaCliente5->text());
    qDebug() << "Testando porta cliente5: " << portaCliente5;
    int pCliente5 = portaCliente5.toInt();
    c5->start(pCliente5);
}

void MainWindow::on_botaoCliente6_clicked()
{
    p->addConsumidor(c6);
    QString portaCliente6(ui->portaCliente6->text());
    qDebug() << "Testando porta cliente6: " << portaCliente6;
    int pCliente6 = portaCliente6.toInt();
    c6->start(pCliente6);
}
