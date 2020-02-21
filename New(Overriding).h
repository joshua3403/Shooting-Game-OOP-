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

	// 메모리 할당 정보 하나
	struct stALLOC_INFO
	{
		void* pAlloc;					// 할당받은 포인터
		int iSize;						// 할당 사이즈
		char szFile[FILE_NAME_LEN];		// 할당 파일 위치
		int iLine;						// 파일 라인
		bool bArray;					// 배열 생성 여부
		bool bFree;						// 해제 여부
	};

private:
	// 메모리 할당 정보들 저장 배열
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

	// new 연산자 오버로딩 함수에서는 본 클래스를 마음껏 접근 할 수 있다.
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