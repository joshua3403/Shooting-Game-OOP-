#pragma once


#include "stdafx.h"

#define MAX_FILENAME_LENGTH 255
#define MAX_TRACE_ALLOC_COUNT 1024*10


namespace MemoryControl {
	class Node
	{
	private:
		void* pPtr;								// �Ҵ�� �޸��� ���� �ּҰ�
		int iSize;								// �Ҵ�� �޸��� ũ��
		bool bIsArray;							// �迭 ���·� �Ҵ� �Ǿ�����
		char szFile[MAX_FILENAME_LENGTH];		// ���� �̸� ����
		int iLine;								// main �Լ����� ȣ���� ��ġ
		friend class List;
		friend class MemoryAllocator;

	public:

		Node* Next;

		Node()
		{

		}

		~Node()
		{
			std::cout << "Node deleted" << std::endl;
		}

	};

	class List
	{
	private:
		int iNodeSize;
		Node* head;
		Node* tail;
		char date_string[128] = { '\0', };

		FILE* file;

		friend class MemoryAllocator;
	public:
		List()
		{

		}

		bool IsEmpty()
		{
			if (iNodeSize <= 0)
				return true;
			else
				return false;
		}

		bool Push_Back(void* ptr, int Size, bool isArray,const char* fileName, int Line)
		{
			std::cout << "Here" << std::endl;
			// ��带 �����ڸ� ���� �����ϰ� �����Ͷ��� �����Ѵ�.
			Node* newNode = (Node*)malloc(sizeof(Node));

			newNode->pPtr = ptr;
			newNode->iSize = Size;
			newNode->bIsArray = isArray;
			StringCchCopyA(newNode->szFile, sizeof(newNode->szFile), fileName);
			newNode->iLine = Line;

			if (newNode == nullptr)
				return false;

			if (IsEmpty())
			{
				head = newNode;
			}
			else
			{
				tail->Next = newNode;
			}
			tail = newNode;
			tail->Next = nullptr;
			iNodeSize++;

			return true;
		}

		Node* Find(void* ptr)
		{
			Node* NowNode = head;
			if (iNodeSize == 0)
				return nullptr;
			while (NowNode != nullptr)
			{
				if (NowNode->pPtr == ptr)
				{
					return NowNode;
				}
				else
				{
					NowNode = NowNode->Next;
				}
			}

			return nullptr;
		}

		bool Erase(void* ptr)
		{
			if (iNodeSize == 0)
			{
				return false;
			}

			Node* NowNode = head;
			Node* NextNode = head->Next;


			// ã���� �ϴ� ��尡 �����
			if (NowNode->pPtr == ((Node*)ptr)->pPtr)
			{
				head = head->Next;
				head = nullptr;
				delete head;
				iNodeSize--;
				return true;
			}

			while (NextNode != nullptr)
			{
				if (NextNode->pPtr == ((Node*)ptr)->pPtr)
				{
					NowNode->Next = NextNode->Next;
					NowNode = nullptr;
					iNodeSize--;
					return true;
				}
				else
				{
					NowNode = NowNode->Next;
					NextNode = NextNode->Next;
				}
			}

			return false;

		}

		int GetListSize()
		{
			return iNodeSize;
		}


		void PrintList()
		{
			file = fopen(date_string, "ab");
			Node* now = head;
			while (now != nullptr)
			{
				fprintf_s(file, "Leak [0x%08p][%08d] %s : %d \n", now->pPtr, now->iSize, now->szFile, now->iLine);
				now = now->Next;
			}

			fclose(file);
		}

		void PrintError(void* ptr, const char* string)
		{
			file = fopen(date_string, "ab");
			fprintf_s(file, string, ptr);
			fclose(file);
		}

		void PrintFreeArrayError(void* ptr, int size, const char* fileName, int line)
		{
			file = fopen(date_string, "ab");
			fprintf_s(file, "Array [0x%08p][%08d] %s : %d \n", ptr, size, fileName, line);
			fclose(file);
		}

	};

	class MemoryAllocator
	{
	private:
		int iTotal_Alloc_Size;
		size_t alloc_count;
		size_t alloc_failed_count;
		size_t free_count;
		size_t free_failed_count;
		int current_alloc_index;
		int current_free_index;
		int current_count;

		List* MemoryAllocList;
		
	public:


		MemoryAllocator() : iTotal_Alloc_Size(0), alloc_count(0), alloc_failed_count(0), free_count(0), free_failed_count(0),
			current_alloc_index(0), current_free_index(0), current_count(0)
		{
			MemoryAllocList = (List*)malloc(sizeof * (MemoryAllocList));
			MemoryAllocList->iNodeSize = 0;
			MemoryAllocList->head = MemoryAllocList->tail = nullptr;
			time_t now = time(NULL);
			struct tm date;
			setlocale(LC_ALL, "Korean");
			localtime_s(&date, &now);

			strftime(MemoryAllocList->date_string, sizeof(MemoryAllocList->date_string), "Alloc_%Y%m%d_%H%M%S.txt", &date);
			MemoryAllocList->file = fopen(MemoryAllocList->date_string, "ab");

			fclose(MemoryAllocList->file);
		}

		~MemoryAllocator()
		{
			PrintLeakMemory();
		}

	public:
		void PrintAllocFail(void* ptr)
		{
			MemoryAllocList->PrintError(ptr, "MallocFail [0x%08p]\n");
		}

		void PrintTraceCountShortage(void* ptr)
		{
			MemoryAllocList->PrintError(ptr, "TraceCountShortage [0x%08p]\n");
		}

		void PrintNullptrFree(void* ptr)
		{
			MemoryAllocList->PrintError(ptr, "NullPointerFree [0x%08p]\n");
		}

		void PrintNoAlloc(void* ptr)
		{
			MemoryAllocList->PrintError(ptr, "NoAlloc [0x%08p]\n");
		}

		void PrintFreeArrayError(void* ptr, int size, const char* fileName, int line)
		{
			MemoryAllocList->PrintFreeArrayError(ptr, size, fileName, line);
		}

		void PrintLeakMemory()
		{
			MemoryAllocList->PrintList();

		}

		void* Alloc(size_t size, const char* fileName, int line, bool isArray)
		{
			void* ptr = malloc(size);

			if (ptr == nullptr)
			{
				PrintAllocFail(ptr);
				++alloc_failed_count;
				return nullptr;
			}

			MemoryAllocList->Push_Back(ptr, size, isArray, fileName, line);

			current_alloc_index = (MemoryAllocList->iNodeSize + current_alloc_index) % MAX_TRACE_ALLOC_COUNT;
			iTotal_Alloc_Size += size;
			++alloc_count;
			++current_count;

			if (MAX_TRACE_ALLOC_COUNT == MemoryAllocList->GetListSize())
			{
				PrintTraceCountShortage(ptr);
			}

			return ptr;
		}

		void Free(void* ptr)
		{
			if (ptr == nullptr)
			{
				PrintNullptrFree(ptr);
				free_failed_count++;
				return;
			}

			int index;
			Node* findNode = MemoryAllocList->Find(ptr);
			Node* findArrayNode = MemoryAllocList->Find((void*)((int*)ptr - 2));

			if (findNode == nullptr && findArrayNode != nullptr)
			{

				PrintFreeArrayError(ptr, findArrayNode->iSize, findArrayNode->szFile, findArrayNode->iLine);
				current_alloc_index = (MemoryAllocList->iNodeSize + current_free_index) % MAX_TRACE_ALLOC_COUNT;
				++free_count;
				current_count--;

				iTotal_Alloc_Size -= findArrayNode->iSize;
				//findArrayNode->pPtr = nullptr;
				goto FREEARRAY;
			}

			if (findNode != nullptr && findNode == nullptr)
			{
				current_alloc_index = (MemoryAllocList->iNodeSize + current_free_index) % MAX_TRACE_ALLOC_COUNT;
				++free_count;
				current_count--;

				iTotal_Alloc_Size -= findNode->iSize;
				//findNode->pPtr = nullptr;
				goto FREE;

			}

			if (findNode == nullptr && findArrayNode == nullptr)
			{
				free_failed_count++;
				PrintNoAlloc(ptr);
			}

		FREE:
			free(ptr);
			MemoryAllocList->Erase(findNode);
			return;
		FREEARRAY:
			free((void*)((int*)ptr - 2));
			MemoryAllocList->Erase(findArrayNode);
			return;
		}
	};

	static MemoryAllocator c_Memory_Controler;
}

// ����ο��� new�� delete ���� �����
// cpp�� ���ǿ� ������ �־�� --> ������ �Ⱦ����ϱ�
// ��ũ�� ����Ʈ�� ���� ��� �����ڿ����� new �� �ƴ� malloc�� ����ؾ� �Ѵ�
// ������ ���� ���� �ݰ�.

void* operator new(size_t size, const char* fileName, int line)
{
	return MemoryControl::c_Memory_Controler.Alloc(size, fileName, line, false);
}

void* operator new[](size_t size, const char* fileName, int line)
{
	return MemoryControl::c_Memory_Controler.Alloc(size, fileName, line, true);
}

void operator delete(void* ptr)
{
	return MemoryControl::c_Memory_Controler.Free(ptr);
}

void operator delete[](void* ptr)
{
	return operator delete(ptr);
}

void operator delete (void* p, char* File, int Line)
{
}
void operator delete[](void* p, char* File, int Line)
{
}

#define new new(__FILE__, __LINE__)