#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Consumidor.h"
#include "Produtor.h"

#include <QMainWindow>
#include <QDebug>
#include <QString>

class Produtor;
class Consumidor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Produtor *p;
    Consumidor *c1;
    Consumidor *c2;
    Consumidor *c3;
    Consumidor *c4;
    Consumidor *c5;
    Consumidor *c6;

private slots:
    void on_botaoServidor_clicked();

    void on_botaoCliente1_clicked();

    void on_botaoCliente2_clicked();

    void on_botaoCliente3_clicked();

    void on_botaoCliente4_clicked();

    void on_botaoCliente5_clicked();

    void on_botaoCliente6_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
