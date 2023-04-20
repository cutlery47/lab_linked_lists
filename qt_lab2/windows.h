#ifndef WINDOWS_H
#define WINDOWS_H
#include <QWidget>

//студенты
class secondWindow;
//оценки
class thirdWindow;
//календарь
class fourthWindow;

//окно студентов
namespace Ui {
class secondWindow;
}

class secondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    ~secondWindow();



private slots:
    void on_quitBtn_clicked();

    void on_calendarBtn_clicked();

    void on_gradesBtn_clicked();

    void on_confButton_clicked();

private:
    Ui::secondWindow *ui;
    fourthWindow *fourthWindow; //календарь
    thirdWindow *thirdWindow; //студенты
};



//окно оценок
namespace Ui {
class thirdWindow;
}

class thirdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit thirdWindow(QWidget *parent = nullptr);
    ~thirdWindow();

private slots:
    void on_quitBtn_clicked();

    void on_studBtn_clicked();

    void on_calendarBtn_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void goofy_ahh_sort(std::vector<QString> subj, std::vector<QString> grad, int mode);
private:
    Ui::thirdWindow *ui;
    fourthWindow *fourthWindow; //календарь
    secondWindow *secondWindow; //студенты
};



//окно с календарем
namespace Ui {
class fourthWindow;
}

class fourthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit fourthWindow(QWidget *parent = nullptr);
    ~fourthWindow();

private slots:
    void on_quitBtn_clicked();

    void on_gradesBtn_clicked();

    void on_studBtn_clicked();

    void timerEvent(QTimerEvent *event);
private:
    Ui::fourthWindow *ui;
    secondWindow *secondWindow; //студенты
    thirdWindow *thirdWindow; //оценки
};

#endif // WINDOWS_H
