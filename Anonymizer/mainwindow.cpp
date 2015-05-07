#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

#include <filehandler.h>

#include <string>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MUSIC Dicom Anonymisation Tool");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Folder_triggered()
{

    QString folderName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                           "/home",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File");
    FileHandler aFileHandler;
    size_t size = 0;
    char* memoryBlock = aFileHandler.getFileAsBinary(filename.toStdString(), size);

    if (!memoryBlock)
    {
        std::cout << "Couldn't open file: " << filename.toStdString() << std::endl;
        return;
    }

    // search for dicom tag (hardcoded to patient DOB)
    size_t dataLength = 0;
    char* name = aFileHandler.SeekDicomTag(memoryBlock, 0x00100030, size, dataLength);



    std::string aString(name, dataLength);
    std::cout << aString << std::endl;
}
