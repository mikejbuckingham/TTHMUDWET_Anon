#include "filehandler.h"

#include <iostream>
#include <fstream>
#include <ostream>

#include <QDebug>

#include <vector>

#include <QFileDialog>

#include <QDir>
#include <QDirIterator>


FileHandler::FileHandler()
{
}

std::vector<FileSizeTuple> FileHandler::getFileSizeVector(QWidget* caller, QString& folderName, QStringList& listOfDirs)
{
    folderName = QFileDialog::getExistingDirectory(caller, "Open Directory",
                                                           "/home",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);

    std::vector<FileSizeTuple> aFileSizeVector;

    if (folderName.isNull())
        return aFileSizeVector;

    QStringList listOfFiles;
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




    FileHandler aFileHandler;

    // let's do a hack for now (need to strip the .. and .)
    for (int i = 0; i < listOfFiles.size(); i++)
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

    return aFileSizeVector;
}

char* FileHandler::SeekDicomTag(char* memoryBlock, unsigned int tag, size_t length, size_t& oDataLength)
{
    unsigned short* bufferHandler = (unsigned short*)memoryBlock;
    unsigned short* pTag = (unsigned short*)&tag;
    unsigned int nRead = length;
    char* dataElementPtr = 0;

    // words are unsigned shorts
    // read the data sequentially in words
    // check if the tag matches (each tag is two words)
    // return a pointer? Should we also evaluate endianness here? Probably..
    // Do we need to know the length of the tag content? Should we zero it? What's the correct 'null' value for dicom? Spam spaces?

    // number of words
    unsigned int nWords = nRead / sizeof(unsigned short);
    for (unsigned int i = 0; i < nWords-2; i++)
    {
        // endianness fuckabout, I assume
        if ((bufferHandler[i] == pTag[1]) && bufferHandler[i+1] == pTag[0])
        {
            // We have found a tag, such that 4 bytes equals our int tag

            // get the start of the data element
            // tag is 4 bytes long, but we're working in 2-byte tuples

            dataElementPtr = &memoryBlock[i*2];

            // skip the first 4 bytes - we don't care about the tag

            dataElementPtr += 4;

            // now the fun bit - do we have a VR? Just length? BECAUSE FUCK YOU DICOM STANDARD

            // TODO we currently assume 2bytes VR, 2bytes length

            oDataLength = (unsigned short)(dataElementPtr[2]);

            // skip the VR and length, just return a pointer to the content
            dataElementPtr += 4;

            break;
        }
    }
    return dataElementPtr;
}


char* FileHandler::getFileAsBinary(std::string iFilename, size_t& length)
{
    // return a char* to a binary segment holding the file contents
    std::streampos size;
    char* memoryBlock = 0;

    std::ifstream file (iFilename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memoryBlock = new char [size];
        file.seekg(0, std::ios::beg);
        file.read(memoryBlock, size);
        file.close();
    }
    else
        qDebug() << "Open file failed";

    length = size;
    return memoryBlock;
}

char* FileHandler::writeFileFromBinary(std::string iFilename, size_t length, char* binaryFile)
{
    char* result = NULL;
    std::streampos size;
    std::ofstream file;



    file.open(iFilename.c_str(), std::ios::out|std::ios::binary);
    file.write(binaryFile, length);
    file.close();

    return result;
}
