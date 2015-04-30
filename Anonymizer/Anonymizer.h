// Anonymizer.h: interface for the CAnonymizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANONYMIZER_H__43D8742D_8D3B_4F62_8C0E_A138D4460A55__INCLUDED_)
#define AFX_ANONYMIZER_H__43D8742D_8D3B_4F62_8C0E_A138D4460A55__INCLUDED_

#include <vector>
#include <string>

class CAnonymizer  
{
public:
	CAnonymizer();
	virtual ~CAnonymizer();

    void SetPrimaryTag(unsigned int tag) { m_iPrimaryTag = tag; }

	// Scan for a list of DICOM files:
    int ScanFolder(std::string sFolder, int& nProgress);

	struct FileProperty
	{
        std::string m_sFileName;  // File name to be appended to m_sFolder.
        std::string m_sPatientName;
	};
	typedef std::vector<FileProperty> FileList;
	const FileList& GetFileList() { return m_FileList; }

	// Dictionary to anonymize them:
	struct NamePair
	{
        std::string m_sName;
        std::string m_sAnonymized;
	};
	typedef std::vector<NamePair> Dictionary;
	const Dictionary& GetDictionary() { return m_Dictionary; }
	void SetDictionary(const NamePair& entry);
	void SortDictionary(bool bByName);  // bByName: false to sort by Anonymized.

    void AssignNewNames(const std::string& sPrefix, int nStart, bool bUseNumber);

	bool Anonymize(int index, bool bEraseInstitution);

    std::string GetLastErrMsg() { return m_sErrMsg; }

private:

    unsigned int m_iPrimaryTag;
    std::string m_sFolder;  // with a "\" in the end.
    std::string m_sErrMsg;

	FileList m_FileList;
	Dictionary m_Dictionary;

    void ScanFolderForFiles(std::string sFolder, std::string sFileName, int& nProgress);
        bool GetDicomFileProperties(const std::string& sFullPath, FileProperty& F);
		void CreateDictionary();
    bool LookupDictionary(const std::string& sName, std::string& sAnonymized);

    static bool IsLikeDicomFile(const std::string& sFullPath);  // Returns false if file is too short.
    static bool OpenDicomFile(const std::string& sFullPath, FILE& file, bool bWrite=false);  // Returns false if is not DICOM.
    static bool ReadDicomTag(FILE& file, unsigned int tag, std::string& oValue);
    static bool SeekDicomTag(FILE& file, unsigned int tag, unsigned int& oLength);  // Points to the value.
    static bool ReplaceStringInFile(const std::string& sFullPath, const std::string& sOld, const std::string& sNew);

    bool AnonymizeDicomFile(const std::string& sFullPath, const std::string& sNewPatientName, bool bEraseInstitution);
    static void EraseInstitution(FILE& file);

	static int CompareByName(const void* pair1, const void* pair2);
	static int CompareByAnonymized(const void* pair1, const void* pair2);
};

#endif // !defined(AFX_ANONYMIZER_H__43D8742D_8D3B_4F62_8C0E_A138D4460A55__INCLUDED_)
