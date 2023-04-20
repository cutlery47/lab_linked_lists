#include "windows.h"
#include "ui_secondwindow.h"
#include "utilities.h"

QString student = "";
int group;
int gender;
bool allowed;
QString txt_group;

secondWindow::secondWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondWindow)
{
    ui->setupUi(this);

    ui->label_5->hide();
    //если не ввел значения - нельзя идти дальше
    if (allowed == 0) {
        ui->gradesBtn->setDisabled(1);
        ui->calendarBtn->setDisabled(1);
    } else {
        ui->label_4->setText("Отредактировать данные");
    }

    //выводим сохраненные данные
    ui->textEdit->setText(student);
    ui->spinBox->setValue(group);
    if (gender == 1) {
        ui->sexBtn->setChecked(1);
    } else if (gender == 2) {
        ui->sexBtn2->setChecked(1);
    } else if (gender == 3) {
        ui->sexBtn3->setChecked(1);
    }
}

secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::on_confButton_clicked() {
    QString nums[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    QString name;

    name = ui->textEdit->toPlainText();

    if (name.size() == 0) {
        return;
    }

    for (int i = 0; i < 10; ++i) {
        if (name.contains(nums[i])) {
            ui->label_5->show();
            ui->textEdit->setStyleSheet("QTextEdit { background-color : red; }");

            allowed = false;
            ui->gradesBtn->setEnabled(0);
            ui->calendarBtn->setEnabled(0);

            return;
        }
    }
    student = name;

    ui->textEdit->setStyleSheet("QTextEdit { background-color : rgb(255, 255, 255); }");
    ui->label_5->hide();

    //открываем доступ к другим окнам
    allowed = true;
    ui->gradesBtn->setEnabled(1);
    ui->calendarBtn->setEnabled(1);

    ui->label_4->setText("Отредактировать данные");

    //заносим новые данные

    if (ui->sexBtn->isChecked()) {
        gender = 1;
    } else      if (ui->sexBtn2->isChecked()) {
        gender = 2;
    } else      if (ui->sexBtn3->isChecked()) {
        gender = 3;
    }
    group = ui->spinBox->value();
    txt_group = ui->spinBox->text();
}

void secondWindow::on_quitBtn_clicked()
{
    close();
}

void secondWindow::on_calendarBtn_clicked()
{
    fourthWindow = new class fourthWindow();
    fourthWindow->setWindowState(Qt::WindowFullScreen);

    fourthWindow->show();
    close();
}

void secondWindow::on_gradesBtn_clicked()
{
    thirdWindow = new class thirdWindow();
    thirdWindow->setWindowState(Qt::WindowFullScreen);

    thirdWindow->show();
    close();
}
