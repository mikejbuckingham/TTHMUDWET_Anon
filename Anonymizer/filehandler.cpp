#include "filehandler.h"

#include <iostream>
#include <fstream>
#include <ostream>

#include <QDebug>

#include <vector>

#include <QFileDialog>

#include <QDir>
#include <QDirIterator>

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

#include <medStyleSheetParser.h>

const std::string OSSeperator = "/";

FileHandler::FileHandler()
{
}

FileHandler::~FileHandler()
{

}

std::vector<FileSizeTuple>* FileHandler::getFileSizeVector(QWidget* caller, QString& folderName, QStringList* listOfDirsPtr)
{
    QStringList& listOfDirs = *listOfDirsPtr;
    if (folderName.isNull())
    {
        emit finished(false);
        return NULL;
    }

    std::vector<FileSizeTuple>* aFileSizeVector = new std::vector<FileSizeTuple>;



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

    FileHandler aFileHandler;

    double numbersOfFiles = listOfFiles.size();
    double tick = 100.0f / numbersOfFiles;
    double currentPercentage = 0;

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
            {

                if (aFileSizeTuple.size > 0x84)
                {

                    char* DICOMAdd = aFileSizeTuple.filePointer + 0x80;
                    if (DICOMAdd[0] == 'D' && DICOMAdd[1] == 'I'
                            && DICOMAdd[2] == 'C' && DICOMAdd[3] == 'M')
                    {
                        aFileSizeVector->push_back(aFileSizeTuple);
                    }
                    else
                    {
                        delete [] aFileSizeTuple.filePointer;
                    }
                }
                else
                    delete [] aFileSizeTuple.filePointer;
            }
        }

        currentPercentage += tick;
        emit percentageProcessed(currentPercentage);
    }
    if (aFileSizeVector->size() > 0)
        return aFileSizeVector;
    else
    {
        delete aFileSizeVector;
        return NULL;
    }
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

    // number of words
    unsigned int nWords = nRead / sizeof(unsigned short);
    for (unsigned int i = 0; i < nWords-2; i++)
    {
        // endianness
        if ((bufferHandler[i] == pTag[1]) && bufferHandler[i+1] == pTag[0])
        {
            // We have found a tag, such that 4 bytes equals our int tag

            // get the start of the data element
            // tag is 4 bytes long, but we're working in 2-byte tuples

            dataElementPtr = &memoryBlock[i*2];

            // skip the first 4 bytes - we don't care about the tag

            dataElementPtr += 4;

            // now the fun bit - do we have a VR? Just length?

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

bool FileHandler::createZip(QString fullFileName, const std::vector<FileSizeTuple>* fileSizeVector)
{
    QuaZip* aQuaZip = new QuaZip(fullFileName);
    //aQuaZip->setZip64Enabled(true);
    aQuaZip->open(QuaZip::mdCreate);

    double numbersOfFiles = fileSizeVector->size();
    double tick = 100.0f / numbersOfFiles;
    double currentPercentage = 0;

    for (unsigned int i = 0; i < fileSizeVector->size(); i++)
    {

        QuaZipFile file(aQuaZip);

        std::string finalName = (*fileSizeVector)[i].filename.c_str();

        // Strip the first character, if it starts with /
        if (finalName.c_str()[0] == '/')
        {
            finalName = &finalName.c_str()[1];
        }

        QuaZipNewInfo newFileInfo(finalName.c_str());
        newFileInfo.setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ReadOther | QFile::ReadGroup);

        if (!file.open(QIODevice::WriteOnly, newFileInfo))
        {
            emit finished(false);
            file.close();
            aQuaZip->close();
            delete aQuaZip;
            return false;
        }

        file.write((*fileSizeVector)[i].filePointer, (*fileSizeVector)[i].size);

        file.close();

        currentPercentage += tick;
        emit percentageProcessed(currentPercentage);

    }
    aQuaZip->close();
    delete aQuaZip;
    emit finished(true);
    return true;
}

bool FileHandler::createFolder(QString folderName, std::vector<FileSizeTuple>* fileSizeVector)
{

    double numbersOfFiles = fileSizeVector->size();
    double tick = 100.0f / numbersOfFiles;
    double currentPercentage = 0;

    for (unsigned int i = 0; i < fileSizeVector->size(); i++)
    {
        std::string newFilename = folderName.toStdString() + OSSeperator + (*fileSizeVector)[i].filename;
        size_t size = (*fileSizeVector)[i].size;
        char* filePointer = (*fileSizeVector)[i].filePointer;

        writeFileFromBinary(newFilename, size, filePointer);

        currentPercentage += tick;
        emit percentageProcessed(currentPercentage);
    }

    emit finished(true);
    return true;

}

char* FileHandler::writeFileFromBinary(std::string iFilename, size_t length, char* binaryFile)
{
    char* result = NULL;
    std::ofstream file;



    file.open(iFilename.c_str(), std::ios::out|std::ios::binary);
    file.write(binaryFile, length);
    file.close();

    return result;
}
