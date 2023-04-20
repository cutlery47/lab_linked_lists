#include "firstwindow.h"
#include "ui_firstwindow.h"
#include "utilities.h"

FirstWindow::FirstWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstWindow)
{
    ui->setupUi(this);

    gender = 1;
    group = 2372;
    allowed = false;

}

FirstWindow::~FirstWindow()
{
    delete ui;
}


void FirstWindow::on_quitBtn_clicked()
{
    close();
}


void FirstWindow::on_startBtn_clicked()
{
    secondWindow = new class secondWindow();
    secondWindow->setWindowState(Qt::WindowFullScreen);

    secondWindow->show();
    this->close();
}

