#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>

#include <filehandler.h>

#include <string>

#include <iostream>

#include <QDir>
#include <QDirIterator>

#include <QMessageBox>

#include <DirMaker.h>

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

const std::string OSSeperator = "/";
std::string newFolderName = "Anon";



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MUSIC Dicom Anonymisation Tool");
    this->firstInput = true;
    this->isAnon = false;
    this->ui->radioZip->setChecked(true);
    this->dateString = "NONE";
    this->nameString = "NONE";
    this->nameLength = 0;
    this->dateLength = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    // Get all files and read them into memory
    FileHandler aFileHandler;
    QString folderName;

    if (!fileSizeVector.empty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File already open!", "Close current file?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for (unsigned int i = 0; i < fileSizeVector.size(); i++)
                delete [] fileSizeVector[i].filePointer;

            fileSizeVector.clear();

        }
        else
            return;
    }

    fileSizeVector = aFileHandler.getFileSizeVector(this, folderName, listOfDirs);

    if (fileSizeVector.empty())
        return;

    // read first file and check max lengths of key tags (name and date of birth)
    size_t dataLength = 0;
    char* filePointer = fileSizeVector[0].filePointer;
    size_t size = fileSizeVector[0].size;

    aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);
    this->nameLength = dataLength;

    aFileHandler.SeekDicomTag(filePointer, 0x00100030, size, dataLength);
    this->dateLength = dataLength;

}

void MainWindow::on_action_Open_triggered()
{
    QString absoluteFilename;
    QFileDialog aQFileDialog;
    absoluteFilename = aQFileDialog.getOpenFileName(this, "Open File");

    QString filename = absoluteFilename;

    QFileInfo aFileInfo(filename);

    QString filenameFinal = filename.remove(aFileInfo.absoluteDir().absolutePath() + "/");

    std::cout << "Filename: " << filenameFinal.toStdString() << std::endl;
    if (filename.isNull())
        return;


    FileHandler aFileHandler;
    size_t size = 0;
    char* filePointer = aFileHandler.getFileAsBinary(absoluteFilename.toStdString(), size);

    if (!filePointer)
    {
        std::cout << "Couldn't open file: " << filename.toStdString() << std::endl;
        return;
    }
    FileSizeTuple aFileSizeTuple;
    aFileSizeTuple.filePointer = filePointer;
    aFileSizeTuple.size = size;
    aFileSizeTuple.filename = filename.toStdString();
    fileSizeVector.push_back(aFileSizeTuple);

    size_t dataLength = 0;

    aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);
    this->nameLength = dataLength;

    aFileHandler.SeekDicomTag(filePointer, 0x00100030, size, dataLength);
    this->dateLength = dataLength;
}

void MainWindow::on_actionClose_triggered()
{
    exit(0);
}

void MainWindow::on_newPushButton_clicked()
{
    // if we have already opened at least one file this session,
    // we need to prompt
    on_closeFilePushbutton_clicked();

    if (!firstInput && this->nameString != "NONE" && this->dateString != "NONE")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "New Session?", "Keep anonymisation key?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {

        }
        else
        {
            this->nameString = "NONE";
            this->dateString = "NONE";
            this->ui->nameAnonUI->setText(QString(this->nameString.c_str()));
            this->ui->dateAnonUI->setText(QString(this->dateString.c_str()));
        }
    }
    else
        firstInput = false;

    this->isAnon = false;
}

void MainWindow::on_setStringsButton_clicked()
{
    QString nameResult = QInputDialog::getText(0, "Enter string", "Name:");

    std::string nameResultStd = nameResult.toStdString();

    this->nameString = nameResultStd;

    QString dateResult = QInputDialog::getText(0, "Enter string", "Birthdate:");

    std::string dateResultStd = dateResult.toStdString();

    this->dateString = dateResultStd;

    this->ui->nameAnonUI->setText(QString(this->nameString.c_str()));
    this->ui->dateAnonUI->setText(QString(this->dateString.c_str()));

    this->firstInput = false;
}

void MainWindow::on_anonPushButton_clicked()
{
    FileHandler aFileHandler;
    if (this->dateString != "NONE" && this->nameString != "NONE")
    {
        if (fileSizeVector.empty())
        {
            QMessageBox aMessageBox;
            aMessageBox.setText("No files opened!");
            aMessageBox.exec();
        }
        if (this->dateString.length() > this->dateLength)
        {
            std::cout << "DateString too long!" << std::endl;
            return;
        }

        if (this->nameString.length() > this->nameLength)
        {
            std::cout << "NameString too long!";
            return;
        }

        for (unsigned int i = 0; i < fileSizeVector.size(); i++)
        {
            char* filePointer = fileSizeVector[i].filePointer;
            size_t size = fileSizeVector[i].size;
            size_t dataLength = 0;
            char* name = aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);
            char* date = aFileHandler.SeekDicomTag(filePointer, 0x00100030, size, dataLength);

            for (unsigned int i = 0; i < nameLength; i++)
            {
                // zero the content
                name[i] = 0;
            }

            for (unsigned int i = 0; i < dateLength; i++)
            {
                date[i] = 0;
            }

            for (unsigned int i = 0; i < nameString.length(); i++)
            {
                name[i] = nameString[i];
            }

            for (unsigned int i = 0; i < dateString.length(); i++)
            {
                date[i] = dateString[i];
            }
        }

        this->isAnon = true;

    }
    else
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("No anonymisation strings set!");
        aMessageBox.exec();
    }
}

void MainWindow::on_savePushButton_clicked()
{
    if (fileSizeVector.empty())
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("No data loaded!");
        aMessageBox.exec();
        return;
    }
    if (!this->isAnon)
    {
        // throw dialogue
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Data not anonymised!", "Continue anyway?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No)
            return;
    }
    if (this->ui->radioFolder->isChecked())
    {
        QString folderName = QFileDialog::getExistingDirectory(this, "Save Directory",
                                                           "/home",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);

        for (int p = 0; p < listOfDirs.size(); p++)
        {
            std::string newSubDir = folderName.toStdString() + this->listOfDirs[p].toStdString();

            if (!isDirExist(newSubDir))
            {
                makePath(newSubDir);
            }
        }

        FileHandler aFileHandler;
        for (unsigned int i = 0; i < this->fileSizeVector.size(); i++)
        {
            std::string newFilename = folderName.toStdString() + OSSeperator + fileSizeVector[i].filename;
            size_t size = fileSizeVector[i].size;
            char* filePointer = fileSizeVector[i].filePointer;

            aFileHandler.writeFileFromBinary(newFilename, size, filePointer);
        }


    }
    else if (this->ui->radioZip->isChecked())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "/home",
                                   tr("Zip (*.zip)"));

        std::cout << fileName.toStdString() << std::endl;

        QFileInfo aFileInfo(fileName);

        fileName.remove(aFileInfo.absoluteDir().absolutePath() + "/");

        QuaZip* aQuaZip = new QuaZip(fileName);
        aQuaZip->open(QuaZip::mdCreate);

        for (unsigned int i = 0; i < fileSizeVector.size(); i++)
        {
            QuaZipFile file(aQuaZip);
            file.open(QIODevice::WriteOnly, QuaZipNewInfo(fileSizeVector[i].filename.c_str()));

            file.write(fileSizeVector[i].filePointer, fileSizeVector[i].size);

            file.close();
        }
        aQuaZip->close();
    }
}

void MainWindow::on_openFolderPushButton_clicked()
{
    on_actionOpen_Folder_triggered();
}

void MainWindow::on_closeFilePushbutton_clicked()
{
    for (unsigned int i = 0; i < fileSizeVector.size(); i++)
        delete [] fileSizeVector[i].filePointer;
    fileSizeVector.clear();
}

void MainWindow::on_openFilePushButton_clicked()
{
    on_action_Open_triggered();
}
