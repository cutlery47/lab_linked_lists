#include "windows.h"
#include "ui_thirdwindow.h"
#include "utilities.h"
#include <QAxObject>
#include <QFileDialog>
#include <QItemDelegate>

std::vector<QString> grades(5);
std::vector<QString> subjects = {"Мат.Анализ", "АиГ", "Программирование", "Англ. Язык", "Физ. Культура"};



thirdWindow::thirdWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thirdWindow)
{
    ui->setupUi(this);
    ui->label_2->setText(student);
    ui->label_3->setText("Группа: " + txt_group);
    for (size_t i = 0; i < subjects.size(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(subjects[i]);
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i, 0, item);
    }

    for (size_t i = 0; i < grades.size(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(grades[i]);
        ui->tableWidget->setItem(i, 1, item);
    }
}

void thirdWindow::goofy_ahh_sort(std::vector<QString> major, std::vector<QString> addit, int mode) {
    QString buffer_1;
    QString buffer_2;
    int m_col, a_col;

    if (mode == 1) {
        m_col = 0, a_col = 1;
    } else {
        m_col = 1, a_col = 0;
    }

    for (size_t i = 0; i < major.size() - 1; ++i) {
        for (size_t j = 0; j < major.size() - 1; ++j) {
            if ((major[j] > major[j + 1] && mode == 1) || (mode == 2 && major[j] < major[j + 1])) {
                buffer_1 = major[j];
                buffer_2 = addit[j];
                major[j] = major[j + 1];
                addit[j] = addit[j + 1];
                major[j + 1] = buffer_1;
                addit[j + 1] = buffer_2;
            }
        }
    }


    for (size_t i = 0; i < major.size(); ++ i) {
        ui->tableWidget->setItem(i, m_col, new QTableWidgetItem(major[i]));
    }

    for (size_t i = 0; i < addit.size(); ++i) {
        ui->tableWidget->setItem(i, a_col, new QTableWidgetItem(addit[i]));
    }
}



thirdWindow::~thirdWindow()
{
    delete ui;
}

void thirdWindow::on_quitBtn_clicked() {
    close();
}

void thirdWindow::on_pushButton_clicked() {
    thirdWindow::goofy_ahh_sort(subjects, grades, 1);

}

void thirdWindow::on_pushButton_2_clicked() {
    thirdWindow::goofy_ahh_sort(grades, subjects, 2);
}

void thirdWindow::on_pushButton_4_clicked() {
    for (int i = 0; i < 5; ++i) {
        subjects[i] = ui->tableWidget->item(i, 0)->text();
        grades[i] = ui->tableWidget->item(i, 1)->text();
    }



}

void thirdWindow::on_pushButton_3_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save file", QDir::currentPath(), ".xlsx");
    filename.replace("/", "\\");

    auto excel     = new QAxObject("Excel.Application");
    auto workbooks = excel->querySubObject("Workbooks");
    auto workbook  = workbooks->querySubObject("Add");
    auto sheets    = workbook->querySubObject("Worksheets");
    auto sheet     = sheets->querySubObject("Item(int)",1);

    sheet->querySubObject("Columns")->setProperty("ColumnWidth", 50);

    sheet->querySubObject("Cells(Int,Int)", 1, 1)->setProperty("Value", "Предмет");
    sheet->querySubObject("Cells(Int,Int)", 1, 2)->setProperty("Value", "Оценка");


    for (size_t i = 2; i < subjects.size() + 2; ++i) {
        sheet->querySubObject("Cells(Int,Int)", i, 1)->setProperty("Value", subjects[i - 2].toStdString().c_str());
    }

    for (size_t i = 2; i < grades.size() + 2; ++i) {
        sheet->querySubObject("Cells(Int,Int)", i, 2)->setProperty("Value", grades[i - 2].toStdString().c_str());
    }

    workbook->dynamicCall("SaveAs(QString&)", filename);
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    delete excel;
    delete workbooks;
    delete workbook;
    delete sheets;
    delete sheet;
}

void thirdWindow::on_studBtn_clicked()
{
    secondWindow = new class secondWindow();
    secondWindow->setWindowState(Qt::WindowFullScreen);

    secondWindow->show();
    close();
}

void thirdWindow::on_calendarBtn_clicked()
{
    fourthWindow = new class fourthWindow();
    fourthWindow->setWindowState(Qt::WindowFullScreen);

    fourthWindow->show();
    close();
}
