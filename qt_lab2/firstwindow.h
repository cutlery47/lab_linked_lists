#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class FirstWindow; }
QT_END_NAMESPACE

class FirstWindow : public QMainWindow

{
    Q_OBJECT

public:
    FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();

private slots:
    void on_quitBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::FirstWindow *ui;
    secondWindow *secondWindow;
};

#endif // FIRSTWINDOW_H
