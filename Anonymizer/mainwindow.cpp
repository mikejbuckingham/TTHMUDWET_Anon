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

#include <DirMaker.h>

const std::string OSSeperator = "/";

struct FileSizeTuple
{
    FileSizeTuple() { filePointer = 0; size = 0; }
    std::string filename;
    char* filePointer;
    size_t size;
};

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

    QStringList listOfFiles;
    QStringList listOfDirs;

    QDirIterator it(folderName, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        listOfFiles << it.next().remove(folderName);
    }

    QDirIterator itdir(folderName, QDir::Dirs |QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (itdir.hasNext())
    {
        listOfDirs << itdir.next().remove(folderName);
    }

    for (int i = 0; i < listOfDirs.size(); i++)
    {
        std::cout << listOfDirs[i].toStdString() << std::endl;
    }



    std::vector<FileSizeTuple> aFileSizeVector;


    FileHandler aFileHandler;

    std::vector<std::string> aStringVector;


    // let's do a hack for now (need to strip the .. and .)
    for (int i = 0; i < listOfFiles.length(); i++)
    {
        size_t size = 0;
        if (!listOfFiles[i].endsWith("."))
        {
            std::string filename = folderName.toStdString() + listOfFiles[i].toStdString();
            FileSizeTuple aFileSizeTuple;
            aFileSizeTuple.filename = listOfFiles[i].toStdString();
            aFileSizeTuple.filePointer = aFileHandler.getFileAsBinary(filename, size);
            aFileSizeTuple.size = size;

            if (aFileSizeTuple.filePointer)
                aFileSizeVector.push_back(aFileSizeTuple);
            else
            {
                std::cout << "ABORT ABORT ABORT" << std::endl;
                std::cout << aFileSizeTuple.filename;
                std::abort();

            }
        }
    }

    // search dicom tag, hardcoded patient name
    size_t dataLength = 0;
    char* filePointer = aFileSizeVector[0].filePointer;
    size_t size = aFileSizeVector[0].size;
    char* name = aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);

    QString result = QInputDialog::getText(0, "Change name", "Value:");

    std::string stdResult = result.toStdString();

    // TODO - Can files have different name lengths? That would be pretty shitty

    if (stdResult.length() > dataLength)
    {
        std::cout << "Error : Cannot fit";
    }



    // Create directory structure and write content
    for (int i = 0; i < aFileSizeVector.size(); i++)
    {

        std::string newDirName = folderName.toStdString() + OSSeperator + "Anon";

        if(!isDirExist(newDirName))
        {
            makePath(newDirName);
        }

        for (int p = 0; p < listOfDirs.size(); p++)
        {
            std::string newSubDir = newDirName + listOfDirs[p].toStdString();

            if (!isDirExist(newSubDir))
            {
                makePath(newSubDir);
            }
        }

        std::string newFileName = folderName.toStdString() + OSSeperator + "Anon" + aFileSizeVector[i].filename;

        char* filePointer = aFileSizeVector[i].filePointer;
        size_t size = aFileSizeVector[i].size;
        char* name = aFileHandler.SeekDicomTag(filePointer, 0x00100010, size, dataLength);

        for (int i = 0; i < dataLength; i++)
        {
            // zero the content
            name[i] = 0;
        }

        for (int i = 0; i < stdResult.length(); i++)
        {
            name[i] = stdResult[i];
        }



        aFileHandler.writeFileFromBinary(newFileName, size, filePointer);
    }


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

    // search for dicom tag (hardcoded to patient name)
    size_t dataLength = 0;
    char* name = aFileHandler.SeekDicomTag(memoryBlock, 0x00100010, size, dataLength);

    QString result = QInputDialog::getText(0, "Change name", "Value:");

    std::string stdResult = result.toStdString();

    // write out name

    if (stdResult.length() > dataLength)
    {
        std::cout << "Error : Cannot fit";
    }

    for (int i = 0; i < dataLength; i++)
    {
        // zero the content
        name[i] = 0;
    }

    for (int i = 0; i < stdResult.length(); i++)
    {
        name[i] = stdResult[i];
    }

    std::string newFileName = filename.toStdString() + "_Anon";
    aFileHandler.writeFileFromBinary(newFileName, size, memoryBlock);

    delete memoryBlock;
}
