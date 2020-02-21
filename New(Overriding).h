#pragma once

#include "stdafx.h"

class CMemoryHistory
{
public:
	enum
	{
		FILE_NAME_LEN = 128,
		ALLOC_INFO_MAX = 1000
	};

	// �޸� �Ҵ� ���� �ϳ�
	struct stALLOC_INFO
	{
		void* pAlloc;					// �Ҵ���� ������
		int iSize;						// �Ҵ� ������
		char szFile[FILE_NAME_LEN];		// �Ҵ� ���� ��ġ
		int iLine;						// ���� ����
		bool bArray;					// �迭 ���� ����
		bool bFree;						// ���� ����
	};

private:
	// �޸� �Ҵ� ������ ���� �迭
	stALLOC_INFO _allocInfos[ALLOC_INFO_MAX];
	char _logFileName[64];

public:
	CMemoryHistory(const char* szLogFile = "AllocInfo")
	{
		char szTime[17] = "";
		time_t timer;
		struct tm TM;

		memset(_allocInfos, 0, sizeof(stALLOC_INFO) * ALLOC_INFO_MAX);
		memset(_logFileName, 0, 64);

		time(&timer);

		localtime_s(&TM, &timer);

		sprintf_s(szTime, 17, "%04d%02d%02d_%02d%02d%02d", TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);

		StringCchCatA(_logFileName, 64, szLogFile);
		StringCchCatA(_logFileName, 64, szTime);
		StringCchCatA(_logFileName, 64, ".txt");
	}	
	~CMemoryHistory()
	{
		SaveLogFile();
	}

public:
	bool SaveLogFile(void)
	{
		FILE* pLogFile;
		errno_t err = fopen_s(&pLogFile, _logFileName, "a");

		if (err != 0)
			return false;

		for (int iCnt = 0; iCnt < ALLOC_INFO_MAX; iCnt++)
		{
			if (_allocInfos[iCnt].pAlloc != nullptr)
			{
				if (_allocInfos[iCnt].bFree)
					fprintf(pLogFile, "       ");
				else
					fprintf(pLogFile, "LEAK   !! ");

				fprintf(pLogFile, "[0x%p] [%7d] %s : %d \n", _allocInfos[iCnt].pAlloc,
															  _allocInfos[iCnt].iSize,
															  _allocInfos[iCnt].szFile,
															  _allocInfos[iCnt].iLine);
			}
		}
		fclose(pLogFile);
		return true;
	}

	bool NewAlloc(void* pPtr, char* szFile, int iLine, int iSize, bool bArray = false)
	{
		for (int iCnt = 0; iCnt < ALLOC_INFO_MAX; iCnt++)
		{
			if (_allocInfos[iCnt].pAlloc == nullptr || _allocInfos[iCnt].pAlloc == pPtr)
			{
				_allocInfos[iCnt].bFree = false;
				_allocInfos[iCnt].bArray = bArray;
				_allocInfos[iCnt].pAlloc = pPtr;
				_allocInfos[iCnt].iLine = iLine;
				_allocInfos[iCnt].iSize = iSize;
				strcpy_s(_allocInfos[iCnt].szFile, FILE_NAME_LEN, szFile);
				return true;
			}
		}

		return false;
	}
	bool Delete(void* pPtr, bool bArray = false)
	{
		FILE* pLogFile;
		for (int iCnt = 0; iCnt < ALLOC_INFO_MAX; iCnt++)
		{
			if (_allocInfos[iCnt].pAlloc == pPtr)
			{
				if (_allocInfos[iCnt].bFree)
				{
					errno_t err = fopen_s(&pLogFile, _logFileName, "a");
					if (err == 0)
					{
						fprintf(pLogFile, "REFREE !! [0x%x] [%7d] \n", _allocInfos[iCnt].pAlloc, _allocInfos[iCnt].iSize);
						fclose(pLogFile);
					}
					return false;
				}
				else if (_allocInfos[iCnt].bArray != bArray)
				{
					errno_t err = fopen_s(&pLogFile, _logFileName, "a");
					if (err == 0)
					{
						fprintf(pLogFile, "ARRAY !! [0x%x] [%7d] \n", _allocInfos[iCnt].pAlloc, _allocInfos[iCnt].iSize);
						fclose(pLogFile);
					}
					return false;
				}
				else
				{
					_allocInfos[iCnt].bFree = true;
				}
				return true;
			}
		}

		errno_t err = fopen_s(&pLogFile, _logFileName, "a");
		if (err == 0)	return false;
		fprintf(pLogFile, "NOALLOC [0x%x] \n", pPtr);
		fclose(pLogFile);

		return false;
	}

	// new ������ �����ε� �Լ������� �� Ŭ������ ������ ���� �� �� �ִ�.
	friend void* operator new(size_t size, char* File, int Line);
	friend void* operator new[](size_t size, char* File, int Line);
	friend void operator delete(void* p);
	friend void operator delete[](void* p);

	static CMemoryHistory g_MemHistory;
};

CMemoryHistory CMemoryHistory::g_MemHistory;

void* operator new(size_t size)
{
	void* p = malloc(size);
	return p;
}

void* operator new(size_t size, char* File, int Line)
{
	void* p = malloc(size);
	CMemoryHistory::g_MemHistory.NewAlloc(p, File, Line, size);
	return p;
}

void* operator new[](size_t size, char* File, int Line)
{
	void* p = malloc(size);
	CMemoryHistory::g_MemHistory.NewAlloc(p, File, Line, size, true);
	return p;
}

void operator delete(void* p, char* File, int Line)
{

}

void operator delete[](void* p, char* File, int Line)
{

}

void operator delete(void* p)
{
	if (CMemoryHistory::g_MemHistory.Delete(p))
	{
		free(p);
	}
}

void operator delete[](void* p)
{
	if (CMemoryHistory::g_MemHistory.Delete(p, true))
	{
		free(p);
	}
}