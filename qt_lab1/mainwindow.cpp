#include "mainwindow.h"
#include "./ui_mainwindow.h"

QString line;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mainButton_clicked()
{
    line = ui->textEdit->toPlainText();
    ui->message->insertPlainText(line);

    ui->textEdit->clear();
}


void MainWindow::on_pushButton_clicked()
{
    ui->message->clear();
}

