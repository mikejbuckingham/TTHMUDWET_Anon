#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>

#include <filehandler.h>
#include <QFutureWatcher>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void saveZip();
    void saveFolder();
    ~MainWindow();

public slots:
    void updateProgress(double tick);
    void onComplete(bool);
    void dataLoaded();

private slots:
    void on_actionOpen_Folder_triggered();

    void on_actionClose_triggered();

    void on_newPushButton_clicked();

    void on_setStringsButton_clicked();

    void on_anonPushButton_clicked();

    void on_savePushButton_clicked();

    void on_openFolderPushButton_clicked();

    void on_closeFilePushbutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool firstInput;
    bool isAnon;
    std::string nameString;
    std::string dateString;
    std::vector<FileSizeTuple>* fileSizeVector;
    size_t nameLength;
    size_t dateLength;
    QStringList listOfDirs;
    bool doNotClose;
    QFutureWatcher<std::vector<FileSizeTuple>* > watcher;
};

#endif // MAINWINDOW_H
