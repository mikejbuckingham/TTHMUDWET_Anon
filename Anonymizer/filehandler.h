#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler
{
public:
    FileHandler();

    char* getFileAsBinary(std::string iFilename, size_t& length);
    char* SeekDicomTag(char* memoryBlock, unsigned int tag, size_t length, size_t& oLength);
};

#endif // FILEHANDLER_H
