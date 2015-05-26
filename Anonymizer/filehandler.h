#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <QWidget>



struct FileSizeTuple
{
    FileSizeTuple() { filePointer = 0; size = 0; }
    ~FileSizeTuple() { }
    std::string filename;
    char* filePointer;
    size_t size;
};

class FileHandler : public QObject
{
    Q_OBJECT
public:
    FileHandler();
    virtual ~FileHandler();

    char* getFileAsBinary(std::string iFilename, size_t& length);
    char* SeekDicomTag(char* memoryBlock, unsigned int tag, size_t length, size_t& oLength);
    char* writeFileFromBinary(std::string iFilename, size_t length, char* binaryFile);
    std::vector<FileSizeTuple>* getFileSizeVector(QWidget* caller, QString& folderName, QStringList& listOfDirs);
    bool createZip(QString fullFileName, const std::vector<FileSizeTuple>* fileSizeVector);
    bool createFolder(QString folderName, std::vector<FileSizeTuple>* fileSizeVector);

signals:
    void percentageProcessed(double percentage);
    void finished(bool);
};





#endif // FILEHANDLER_H
