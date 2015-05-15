#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <QWidget>

struct FileSizeTuple
{
    FileSizeTuple() { filePointer = 0; size = 0; }
    std::string filename;
    char* filePointer;
    size_t size;
};

class FileHandler
{
public:
    FileHandler();

    char* getFileAsBinary(std::string iFilename, size_t& length);
    char* SeekDicomTag(char* memoryBlock, unsigned int tag, size_t length, size_t& oLength);
    char* writeFileFromBinary(std::string iFilename, size_t length, char* binaryFile);
    std::vector<FileSizeTuple> getFileSizeVector(QWidget* caller);
};





#endif // FILEHANDLER_H
