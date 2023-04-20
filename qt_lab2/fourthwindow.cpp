#include "windows.h"
#include "ui_fourthwindow.h"
#include <QTimer>
#include <QTime>

fourthWindow::fourthWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourthWindow)
{
    ui->setupUi(this);

    startTimer(1000);
}

void fourthWindow::timerEvent(QTimerEvent *event){
    ui->timeEdit->setTime(QTime::currentTime());
}

fourthWindow::~fourthWindow()
{
    delete ui;
}

void fourthWindow::on_quitBtn_clicked() {
    close();
}


void fourthWindow::on_gradesBtn_clicked()
{
    thirdWindow = new class thirdWindow();
    thirdWindow->setWindowState(Qt::WindowFullScreen);

    thirdWindow->show();
    close();
}

void fourthWindow::on_studBtn_clicked()
{
    secondWindow = new class secondWindow();
    secondWindow->setWindowState(Qt::WindowFullScreen);

    secondWindow->show();
    close();
}
