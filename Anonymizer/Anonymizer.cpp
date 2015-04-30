// Anonymizer.cpp: implementation of the CAnonymizer class.
//
//////////////////////////////////////////////////////////////////////

#include "Anonymizer.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnonymizer::CAnonymizer()
{
	m_iPrimaryTag = 0x00100010;  // Patient's Name
}

CAnonymizer::~CAnonymizer()
{

}

//------------------------------------------------------------------------------
int CAnonymizer::ScanFolder(std::string sFolder, int& nProgress)
{
    // TODO - What does this do?
//	m_sFolder = sFolder;
//	m_sFolder.TrimRight(_T("/"));
//	if (m_sFolder.Right(1) != _T("\\"))
//		m_sFolder += _T("\\");

	m_FileList.clear();
    //ScanFolderForFiles(m_sFolder, _T("*.*"), nProgress);
	CreateDictionary();

	return m_FileList.size();
}

//------------------------------------------------------------------------------
void CAnonymizer::SetDictionary(const NamePair& entry)
{
	Dictionary::iterator it;
	for (it = m_Dictionary.begin(); it != m_Dictionary.end(); it++)
	{
		if (entry.m_sName == it->m_sName)
		{
			if (entry.m_sAnonymized != it->m_sAnonymized)
			{
				*it = entry;
			}
			return;
		}
	}
	m_Dictionary.push_back(entry);
}

//------------------------------------------------------------------------------
void CAnonymizer::SortDictionary(bool bByName)  // bByName: false to sort by Anonymized.
{
    //TODO - What does this do?
    int (*Compare )(const void *elem1, const void *elem2 ) = bByName ? CompareByName : CompareByAnonymized;

	for (int iMain = 0; iMain < m_Dictionary.size(); iMain++)
	{
		// Select the smallest one from the rest:
		int iSelect = iMain;
		for (int iSub = iMain+1; iSub < m_Dictionary.size(); iSub++)
		{
			if (Compare(&m_Dictionary[iSub], &m_Dictionary[iSelect]) < 0)
			{
				iSelect = iSub;
			}
		}
		// Swap it to main:
		if (iSelect != iMain)
		{
			NamePair swap = m_Dictionary[iSelect];
			m_Dictionary[iSelect] = m_Dictionary[iMain];
			m_Dictionary[iMain] = swap;
		}
	}
}

//------------------------------------------------------------------------------
int CAnonymizer::CompareByName(const void* pair1, const void* pair2)
{
	if (((const NamePair*)pair1)->m_sName < ((const NamePair*)pair2)->m_sName)
	{
		return -1;
	}
	return (((const NamePair*)pair1)->m_sName > ((const NamePair*)pair2)->m_sName);
}

//------------------------------------------------------------------------------
int CAnonymizer::CompareByAnonymized(const void* pair1, const void* pair2)
{
	if (((const NamePair*)pair1)->m_sAnonymized < ((const NamePair*)pair2)->m_sAnonymized)
	{
		return -1;
	}
	return (((const NamePair*)pair1)->m_sAnonymized > ((const NamePair*)pair2)->m_sAnonymized);
}


//------------------------------------------------------------------------------
void CAnonymizer::AssignNewNames(const std::string& sPrefix, int nStart, bool bUseNumber)
{
	int n = nStart;

	std::vector<NamePair>::iterator it;
	for (it = m_Dictionary.begin(); it != m_Dictionary.end(); it++)
	{
		NamePair& pair = *it;
        int nLength = pair.m_sName.length();

		// Generate new name of the same length:

        // TODO - All the 'format' shit
        std::string sAnonym;
		if (bUseNumber)
		{
            //sAnonym.Format(sPrefix + "%03d", n);
		}
		else
		{
			sAnonym = sPrefix;
		}
        int nAnonym = sAnonym.length();
		if (nAnonym < nLength)
		{
			for (int i=0; i < (nLength-nAnonym); i++)
			{
				sAnonym += " ";
			}
		}
		else
		{
            //sAnonym = sAnonym.Right(nLength);
		}

		pair.m_sAnonymized = sAnonym;
		n++;
	}
}

//------------------------------------------------------------------------------
bool CAnonymizer::Anonymize(int index, bool bEraseInstitution)
{
	int nFiles = GetFileList().size();
	if ((index < 0) || (index >= nFiles))
	{
        //m_sErrMsg.Format("Index %d is out of range %d.", index, nFiles);
		return false;
	}

	const FileProperty& prop = GetFileList().at(index);
    std::string sFilePath = m_sFolder + prop.m_sFileName;
    std::string sAnonymized;
	if (!LookupDictionary(prop.m_sPatientName, sAnonymized))
	{
        //m_sErrMsg.Format("Can not find patient name '%d' in dictionary.", prop.m_sPatientName);
		return false;
	}

	bool bOK = AnonymizeDicomFile(sFilePath, sAnonymized, bEraseInstitution);
	if (!bOK)
	{
		m_sErrMsg = "Can not anonymize file\n";
		m_sErrMsg += sFilePath;
		m_sErrMsg += "\n\nPossible reasons:\n";
		m_sErrMsg += "1. It is not a DICOM file, or\n";
		m_sErrMsg += "2. It is read-only.\n";
		return false;
	}
	return true;
}

//=========================================================================
void CAnonymizer::ScanFolderForFiles(std::string sFolder, std::string sFileName, int& nProgress)
{
    // todo - unfuck all of this
//    std::string sCast = sFolder;
//	ASSERT(sCast.Right(1) == _T("\\"));
//	sCast += sFileName;

//	enum FolderType
//	{
//		kUncertain,
//		kDicomFolder,
//		kNonDicomFolder
//	};
//	FolderType eFolderType = kUncertain;

//	FILEFind FF;
//	BOOL bFoundSomething = FF.FindFile(sCast);
	
//	FileProperty F;

//	while (bFoundSomething)
//	{
//		bFoundSomething = FF.FindNextFile();
//		if (FF.IsDots())
//		{
//			continue;
//		}
//		else if (FF.IsDirectory())
//		{
//            std::string sNewFolder = std::string(sFolder) + FF.GetFileName() + _T("\\");
//			ScanFolderForFiles(sNewFolder, sFileName, nProgress);
//			continue;
//		}

//		// Found a file. Is it a DICOM file?
//		if (eFolderType == kUncertain)
//		{
//			if (GetDicomFileProperties(FF.GetFilePath(), F))
//			{
//				eFolderType = kDicomFolder;
//			}
//			else
//			{
//				eFolderType = kNonDicomFolder;
//				continue;
//			}
//		}

//		// Add the DICOM file into list:
//		if (eFolderType == kDicomFolder)
//		{
//            F.m_sFileName = FF.GetFilePath().Mid(m_sFolder.length());
//			m_FileList.push_back(F);
//			nProgress++;
//		}
//	}

//	nProgress = m_FileList.size();
}


//=========================================================================
bool CAnonymizer::GetDicomFileProperties(const std::string& sFullPath, FileProperty& F)
{
    // TODO - More CSTRING bullshit
 //   F.m_sFileName = sFullPath.Mid(m_sFolder.length());

	if (!IsLikeDicomFile(sFullPath))
	{
		return false;
	}

    // TODO - this is not intended, the new is just to make it compile
    FILE& file = *(new FILE);
	if (!OpenDicomFile(sFullPath, file))
	{
		return false;
	}
	if (!ReadDicomTag(file, m_iPrimaryTag, F.m_sPatientName))
	{
		return false;
	}
//     TODO - Close the filestream
    //file.Close();

	return true;
}


//=========================================================================
void CAnonymizer::CreateDictionary()
{
	m_Dictionary.resize(0);

	FileList::const_iterator it;
	for (it = m_FileList.begin(); it != m_FileList.end(); it++)
	{
		NamePair entry;
		entry.m_sName = it->m_sPatientName;
		SetDictionary(entry);
	}

}

//=========================================================================
bool CAnonymizer::LookupDictionary(const std::string& sName, std::string& sAnonymized)
{
	Dictionary::const_iterator it;
	for (it = m_Dictionary.begin(); it != m_Dictionary.end(); it++)
	{
		if (sName == it->m_sName)
		{
			sAnonymized = it->m_sAnonymized;
			return true;
		}
	}
	return false;
}

//=========================================================================
bool CAnonymizer::IsLikeDicomFile(const std::string& sFullPath)
{
    // TODO - Unfuck this entire thing
//	// Check file length:
//	FILEFind FF;
//	if (!FF.FindFile(sFullPath))
//	{
//		return false;
//	}
//	FF.FindNextFile();

//    unsigned int iLength = FF.length();
//	if (iLength < 512)  // File is too small.
//	{
//		return false;
//	}

	return true;
}

//=========================================================================
bool CAnonymizer::OpenDicomFile(const std::string& sFullPath, FILE& file, bool bWrite)
{
    // TODO - Unfuck all of this
//    if (!file.Open(sFullPath, bWrite ? FILE::modeReadWrite : FILE::modeRead))
//	{
//		return false;
//	}
//	const unsigned int kBufferSize = 0x84;
//	const unsigned int nunsigned ints = kBufferSize / 4;
//	unsigned int buffer[nunsigned ints];
//	unsigned int nRead = file.Read(buffer, kBufferSize);
//	if (nRead == kBufferSize)
//	{
//#if 0
//		// Check leading zeros:
//		for (int i=0; i< nunsigned ints-1; i++)
//		{
//			if (buffer[i] != 0)
//			{
//				file.Close();
//				return false;
//			}
//		}
//#endif
//		// "DICM":
//		if (buffer[nunsigned ints-1] == 0x4D434944)
//		{
//			return true;
//		}
//	}

//	file.Close();
	return false;
}

//=========================================================================
bool CAnonymizer::ReadDicomTag(FILE& file, unsigned int tag, std::string& oValue)
{
    const unsigned int kBufferSize = 512;
    unsigned int nLength;
	if (SeekDicomTag(file, tag, nLength) && (nLength < kBufferSize))
	{
		// Read the string:
		char buffer[kBufferSize];
        // TODO - Unfuck the file handling
        //file.Read(buffer, nLength);
        oValue = std::string((char*)buffer, nLength);
		return true;
	}
	return false;
}

//=========================================================================
bool CAnonymizer::SeekDicomTag(FILE& file, unsigned int tag, unsigned int& oLength)
{
    const unsigned int kBlockSize = 1024;
    unsigned short buffer[kBlockSize / sizeof(unsigned short)];
    unsigned short* pTag = (unsigned short*)&tag;

    // TODO - Unfuck the file handling
//	// Find the tag:
//	bool bFound = false;
//    unsigned int nRead = kBlockSize;
//	while (!bFound && (nRead == kBlockSize))
//	{
//		nRead = file.Read(buffer, kBlockSize);
//        unsigned int nWords = nRead / sizeof(unsigned short);
//        for (int i=0; i < nWords-2; i++)
//		{
//			if ((buffer[i] == pTag[0]) && (buffer[i+1] == pTag[1]))
//			{
//                file.Seek(i * sizeof(unsigned short) + 4 - nRead, FILE::current);
//				bFound = true;
//				break;
//			}

//			// Removed because this can happen before patient name in some dose report file.
//			//if ((buffer[i] == 0x7FE0) && (buffer[i+1] == 0x0010))
//			//{
//			//	break;  // Reached pixel data. Terminate.
//			//}
//		}
//		if (bFound)
//		{
//			break;
//		}
//        file.Seek(-4, FILE::current);
//	}
//	if (!bFound)
//	{
//		return false;
//	}

//	// Read the length:
//	file.Read(&oLength, sizeof(oLength));
//    const unsigned int kMaxLength = 127;
//	if (oLength > kMaxLength)
//	{
//		oLength = oLength >> 16;
//		if (oLength > kMaxLength)
//		{
//			ASSERT(0);  // bad length
//			return false;
//		}
//	}

	return true;
}

//=========================================================================
bool CAnonymizer::ReplaceStringInFile(const std::string& sFullPath, const std::string& sOld, const std::string& sNew)
{
    // TODO - Unfuck the file handling
//    const unsigned int nWordSize = sOld.length();
//    if (nWordSize == 0)
//	{
//		return true;
//	}
//	char firstChar = sOld[0];

//    FILE file;
//    if (!file.Open(sFullPath, FILE::modeReadWrite))
//	{
//		return false;
//	}

//    const unsigned int kBlockSize = 1024;
//	char buffer[kBlockSize];

//	while (1)
//	{
//        unsigned int nRead = file.Read(buffer, kBlockSize);
//        int nScan = nRead - nWordSize;
//		for (int i=0; i<nScan; i++)
//		{
//			if (buffer[i] == firstChar)
//			{
//                std::string sFound(buffer+i, nWordSize);
//				if (sFound == sOld)
//				{
//                    file.Seek(i-kBlockSize, FILE::current);
//                    file.Write((std::string)sNew, nWordSize);
//					return true;
//				}
//			}
//		}
//		if (nRead < kBlockSize)
//		{
//			break;
//		}
//        file.Seek(-nWordSize, FILE::current);
//	}

//	ASSERT(0);
	return false;
}

//=========================================================================
bool CAnonymizer::AnonymizeDicomFile(const std::string& sFullPath, const std::string& sNewPatientName, bool bEraseInstitution)
{
    FILE file;
	if (!OpenDicomFile(sFullPath, file, true))
	{
		return false;
	}

	if (bEraseInstitution)
	{
		EraseInstitution(file);
	}

	// Replace patient name:
    unsigned int nLength;
	if (SeekDicomTag(file, m_iPrimaryTag, nLength))
	{
        // TODO - Unfuck..
        //ASSERT(sNewPatientName.length() == nLength);
        //file.Write((std::string)sNewPatientName, nLength);
	}

    // TODO - close the file
    //file.Close();
	return true;
}

//=========================================================================
void CAnonymizer::EraseInstitution(FILE& file)
{
    // TODO - Unfuck this bullshit
//    unsigned int tags[] =
//	{
//		0x00800008,  // Institution Name
//		0x00900008,  // Referring Physician's Name
//		0x10100008,  // Station Name
//		0x10700008  // Operators' Name
//	};
//    const unsigned int nTags = sizeof(tags) / sizeof(tags[0]);

//    int pos = file.Seek(0, FILE::current);
//	for (int iTag=0; iTag < nTags; iTag++)
//	{
//        unsigned int nLength;
//		if (SeekDicomTag(file, tags[iTag], nLength))
//		{
//			if ((0 < nLength) && (nLength < 256))
//			{
//                std::string str(' ', nLength);
//                file.Write((std::string)str, nLength);
//			}
//		}
//		else
//		{
//            file.Seek(pos, FILE::begin);
//		}
//	}
}
