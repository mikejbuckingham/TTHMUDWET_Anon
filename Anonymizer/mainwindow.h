#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Folder_triggered();

    void on_action_Open_triggered();

    void on_actionClose_triggered();

    void on_newPushButton_clicked();

    void on_setStringsButton_clicked();

private:
    Ui::MainWindow *ui;
    bool firstInput;
    std::string nameString;
    std::string dateString;
};

#endif // MAINWINDOW_H
