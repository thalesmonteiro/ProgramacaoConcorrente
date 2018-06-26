#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    updateStatus();
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Adicionar Cliente"),
                                         tr("IP:"),
                                         QLineEdit::Normal,
                                         tr("127.0.0.1"), &ok);
    if (ok && !name.isEmpty())
    {
        /*
         * Nesse momento a parte de adicionar cliente deve ser inserida
         */
        qDebug() << "Adicionando novo cliente!";
        Task* task = new Task(name);
        connect(task, &Task::removed, this,
                &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this,
                &MainWindow::taskStatusChanged);
        //connect(task, &Task::nameClient, this, )
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removeTask(Task* task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(0);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task* /*task*/)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount = 0;
    for(auto t : mTasks){
        if (t->isCompleted()){
            completedCount++;
        }
    }

    int todoCount = mTasks.size() - completedCount;

    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                .arg(todoCount)
                .arg(completedCount));
}
