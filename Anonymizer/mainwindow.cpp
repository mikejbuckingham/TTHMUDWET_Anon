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

#include <qtconcurrentrun.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MUSIC Dicom Anonymisation Tool");
    this->firstInput = true;
    this->isAnon = false;
    this->ui->radioZip->setChecked(true);
    this->dateString = "";
    this->nameString = "";
    this->nameLength = 0;
    this->dateLength = 0;
    this->doNotClose = false;
    this->ui->progressBar->setVisible(false);
    this->ui->SaveOpenText->setVisible(false);
    this->fileSizeVector = 0;

    // old stuff - keeping just in case we want to revert
    this->ui->savePushButton->setVisible(false);
    this->ui->setStringsButton->setVisible(false);

    // normal stuff

    this->ui->radioZip->setVisible(false);
    this->ui->radioFolder->setVisible(false);
    this->ui->anonPushButton->setVisible(false);

    this->ui->newDobBox->setVisible(false);
    this->ui->newNameBox->setVisible(false);
    this->ui->NewDobLabel->setVisible(false);
    this->ui->newNameLabel->setVisible(false);
    this->ui->folderNameLabel->setAlignment(Qt::AlignRight);
    this->ui->folderNameLabel->setText("");
    this->ui->folderNameLabel->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    // Get all files and read them into memory
    // prompt to close if we already have a file
    if (fileSizeVector && !fileSizeVector->empty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File already open!", "Close current file?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            on_closeFilePushbutton_clicked();
        }
        else
            return;
    }

    this->doNotClose = true;

    QString folderName = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                           "",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);

    if (!folderName.size())
    {
        return;
    }

    this->ui->folderNameLabel->setText(folderName);
    this->ui->folderNameLabel->setVisible(true);
    this->ui->SaveOpenText->setText("Opening...");
    this->ui->SaveOpenText->setVisible(true);
    this->ui->progressBar->setVisible(true);


    FileHandler* aFileHandler = new FileHandler;
    connect(aFileHandler, SIGNAL(percentageProcessed(double)), this, SLOT(updateProgress(double)), Qt::QueuedConnection);

    QFuture<std::vector<FileSizeTuple>* > future = QtConcurrent::run(aFileHandler, &FileHandler::getFileSizeVector, this, folderName, listOfDirs);

    this->watcher.setFuture(future);
    connect(&this->watcher,SIGNAL(finished()),this, SLOT(dataLoaded()));
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

    this->ui->newDobBox->setVisible(false);
    this->ui->newNameBox->setVisible(false);
    this->ui->NewDobLabel->setVisible(false);
    this->ui->newNameLabel->setVisible(false);

    this->dateString = this->ui->newDobBox->text().toStdString();
    this->nameString = this->ui->newNameBox->text().toStdString();

    if (!firstInput && (this->nameString != "" || this->dateString != ""))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "New Session?", "Keep anonymisation key?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            this->ui->newDobBox->setVisible(true);
            this->ui->newNameBox->setVisible(true);
            this->ui->NewDobLabel->setVisible(true);
            this->ui->newNameLabel->setVisible(true);
        }
        else
        {
            this->nameString = "";
            this->dateString = "";
            this->ui->newDobBox->clear();
            this->ui->newNameBox->clear();


        }
    }

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
}

void MainWindow::on_anonPushButton_clicked()
{
    FileHandler aFileHandler;


    this->dateString = this->ui->newDobBox->text().toStdString();
    this->nameString = this->ui->newNameBox->text().toStdString();

    if (this->dateString != "" && this->nameString != "")
    {
        if (!fileSizeVector || fileSizeVector->empty())
        {
            QMessageBox aMessageBox;
            aMessageBox.setText("No files opened!");
            aMessageBox.exec();
        }
        if (this->dateString.length() > this->dateLength)
        {
            QMessageBox aMessageBox;
            aMessageBox.setText("New DoB is too long! Aborting!");
            aMessageBox.exec();
            return;
        }

        if (this->nameString.length() > this->nameLength)
        {
            QMessageBox aMessageBox;
            aMessageBox.setText("New name is too long! Aborting!");
            aMessageBox.exec();
            return;
        }

        for (unsigned int i = 0; i < fileSizeVector->size(); i++)
        {
            char* filePointer = (*fileSizeVector)[i].filePointer;
            size_t size = (*fileSizeVector)[i].size;
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

        this->ui->SaveOpenText->setText("Saving...");
        this->ui->SaveOpenText->setVisible(true);
        this->ui->progressBar->setVisible(true);
        if (this->ui->radioFolder->isChecked())
        {
            saveFolder();
        }
        else if (this->ui->radioZip->isChecked())
        {
            saveZip();
        }

    }
    else
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("No anonymisation strings set!");
        aMessageBox.exec();
    }

    this->firstInput = false;
}

void MainWindow::on_savePushButton_clicked()
{

    if (!fileSizeVector || fileSizeVector->empty())
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
}

void MainWindow::saveZip()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("Zip (*.zip)"));

    std::cout << fileName.toStdString() << std::endl;

    QFileInfo aFileInfo(fileName);

    QString fullFileName = fileName;

    fileName.remove(aFileInfo.absoluteDir().absolutePath() + "/");

    FileHandler* aFileHandler = new FileHandler;
    connect(aFileHandler, SIGNAL(percentageProcessed(double)), this, SLOT(updateProgress(double)), Qt::QueuedConnection);
    connect(aFileHandler, SIGNAL(finished(bool)), this, SLOT(onComplete(bool)), Qt::QueuedConnection);

    this->doNotClose = true;
    QtConcurrent::run(aFileHandler, &FileHandler::createZip, fullFileName, fileSizeVector);
}

void MainWindow::saveFolder()
{
    QString folderName = QFileDialog::getExistingDirectory(this, "Save Directory",
                                                       "",
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

    FileHandler* aFileHandler = new FileHandler;
    connect(aFileHandler, SIGNAL(percentageProcessed(double)), this, SLOT(updateProgress(double)), Qt::QueuedConnection);
    connect(aFileHandler, SIGNAL(finished(bool)), this, SLOT(onComplete(bool)), Qt::QueuedConnection);

    this->doNotClose = true;
    QtConcurrent::run(aFileHandler, &FileHandler::createFolder, folderName, fileSizeVector);

}

void MainWindow::on_openFolderPushButton_clicked()
{
    on_actionOpen_Folder_triggered();
}

void MainWindow::on_closeFilePushbutton_clicked()
{
    if (this->doNotClose)
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("Please wait until process has finished!");
        aMessageBox.exec();
        return;
    }

    if (fileSizeVector)
    {
        for (unsigned int i = 0; i < fileSizeVector->size(); i++)
            delete [] (*fileSizeVector)[i].filePointer;
        fileSizeVector->clear();

        delete fileSizeVector;
        fileSizeVector = 0;
    }

    if (this->ui->newDobBox->text() == "" && this->ui->newNameBox->text() == "")
    {
        this->ui->newDobBox->setVisible(false);
        this->ui->newNameBox->setVisible(false);
        this->ui->NewDobLabel->setVisible(false);
        this->ui->newNameLabel->setVisible(false);
    }

    this->ui->folderNameLabel->setText("");
    this->ui->folderNameLabel->setVisible(false);

    this->ui->radioZip->setVisible(false);
    this->ui->radioFolder->setVisible(false);
    this->ui->anonPushButton->setVisible(false);
}

void MainWindow::updateProgress(double tick)
{
    this->ui->progressBar->setValue(tick);
}

void MainWindow::onComplete(bool success)
{
    if (!success)
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("A problem occured. Please retry.");
        aMessageBox.exec();
    }
    this->doNotClose = false;
    this->ui->SaveOpenText->setVisible(false);
    this->ui->progressBar->setVisible(false);
}

void MainWindow::dataLoaded()
{
    fileSizeVector = this->watcher.result();
    if (!fileSizeVector || fileSizeVector->empty())
    {
        QMessageBox aMessageBox;
        aMessageBox.setText("Load failed!");
        aMessageBox.exec();

        this->ui->SaveOpenText->setVisible(false);
        this->ui->progressBar->setVisible(false);
        this->ui->folderNameLabel->setText("");
        this->ui->folderNameLabel->setVisible(false);
        return;
    }

    this->firstInput = false;

    // read first file and check max lengths of key tags (name and date of birth)
    size_t dataLength = 0;
    char* filePointer = (*fileSizeVector)[0].filePointer;
    size_t size = (*fileSizeVector)[0].size;

    FileHandler aFileHandler;
    aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);
    this->nameLength = dataLength;

    aFileHandler.SeekDicomTag(filePointer, 0x00100030, size, dataLength);
    this->dateLength = dataLength;


    this->ui->SaveOpenText->setVisible(false);
    this->ui->progressBar->setVisible(false);

    this->doNotClose = false;

    this->ui->radioZip->setVisible(true);
    this->ui->radioFolder->setVisible(true);
    this->ui->anonPushButton->setVisible(true);

    this->ui->newDobBox->setVisible(true);
    this->ui->newNameBox->setVisible(true);
    this->ui->NewDobLabel->setVisible(true);
    this->ui->newNameLabel->setVisible(true);
}
