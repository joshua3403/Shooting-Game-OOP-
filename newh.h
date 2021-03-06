#pragma once

#include <iostream>
#include <cstdio>

#define MAX_FILENAME_LENGTH 512
#define MAX_TRACE_ALLOC_COUNT 1024*10

typedef struct _AllocEntry
{
	size_t size;
	void* ptr;
	char filename[MAX_FILENAME_LENGTH];
	int line;
} AllocEntry;

namespace lunas {
	class HeapManager
	{
	private:
		int total_alloc_size_;
		size_t alloc_count_;
		size_t alloc_failed_count_;
		size_t free_count_;
		size_t free_failed_count_;
		int curr_alloc_idx_;
		int curr_free_idx_;
		int curr_count_;

		AllocEntry alloc_list_[MAX_TRACE_ALLOC_COUNT];

	public:
		HeapManager()
		{
			total_alloc_size_ = 0;
			alloc_count_ = 0;
			alloc_failed_count_ = 0;
			free_count_ = 0;
			free_failed_count_ = 0;
			curr_count_ = 0;
			curr_alloc_idx_ = 0;
			curr_free_idx_ = 0;
		}

		~HeapManager()
		{

		}

	public:
		void* add(size_t size)
		{
			void *ptr = malloc(size);
			if (!ptr) {
				std::cout << "Heap Memory is shortage " << std::endl;
				++alloc_failed_count_;
				return NULL;
			}

			std::cout << ptr << "  I'm overriding add 111 " << std::endl;

			int i;
			for (i = 0; i < MAX_TRACE_ALLOC_COUNT; ++i) {
				int idx = (i + curr_alloc_idx_) % MAX_TRACE_ALLOC_COUNT;
				if (NULL == alloc_list_[idx].ptr) {
					alloc_list_[idx].size = size;
					alloc_list_[idx].ptr = ptr;
					strcpy_s(alloc_list_[idx].filename, sizeof(alloc_list_[idx].filename), "");
					alloc_list_[idx].line = 0;

					curr_alloc_idx_ = (i + curr_alloc_idx_) % MAX_TRACE_ALLOC_COUNT;
					total_alloc_size_ += size;
					++alloc_count_;
					++curr_count_;
					break;
				}
			}

			if (MAX_TRACE_ALLOC_COUNT == i) {
				std::cout << "TRACE COUNT is shortage " << std::endl;
			}

			return ptr;
		}

		void* add(size_t size, const char* file, int line)
		{
			void *ptr = malloc(size);
			if (!ptr) {
				std::cout << "Heap Memory is shortage " << std::endl;
				++alloc_failed_count_;
				return NULL;
			}

			std::cout << ptr << "  I'm overriding add 222 " << std::endl;

			int i;
			for (i = 0; i < MAX_TRACE_ALLOC_COUNT; ++i) {
				int idx = (i + curr_alloc_idx_) % MAX_TRACE_ALLOC_COUNT;
				if (NULL == alloc_list_[idx].ptr) {
					alloc_list_[idx].size = size;
					alloc_list_[idx].ptr = ptr;
					strcpy_s(alloc_list_[idx].filename, sizeof(alloc_list_[idx].filename), file);
					alloc_list_[idx].line = line;

					curr_alloc_idx_ = (i + curr_alloc_idx_) % MAX_TRACE_ALLOC_COUNT;
					total_alloc_size_ += size;
					++alloc_count_;
					++curr_count_;
					break;
				}
			}

			if (MAX_TRACE_ALLOC_COUNT == i) {
				std::cout << "TRACE COUNT is shortage " << std::endl;
			}

			return ptr;
		}


		void remove(void* ptr)
		{
			if (!ptr) {
				++free_failed_count_;
				std::cout << "delete NULL !!!! " << std::endl;
				return;
			}

			std::cout << ptr << "  I'm overriding delete " << std::endl;

			for (int i = 0; i < MAX_TRACE_ALLOC_COUNT; ++i) {
				int idx = (i + curr_free_idx_) % MAX_TRACE_ALLOC_COUNT;
				if (ptr == alloc_list_[idx].ptr) {
					curr_free_idx_ = (i + curr_free_idx_) % MAX_TRACE_ALLOC_COUNT;
					total_alloc_size_ -= alloc_list_[idx].size;
					++free_count_;
					--curr_count_;

					alloc_list_[idx].size = 0;
					alloc_list_[idx].ptr = NULL;
					goto FREEFREE;
				}
			}

			++free_failed_count_;
			std::cout << "I didnt trace this pointer (0x" << ptr << ") " << std::endl;

		FREEFREE:
			free(ptr);
		}

		void printInfo()
		{
			printf("Memory Info (%d)(a:%u/f:%u\taf:%u/ff:%u)\n", total_alloc_size_, alloc_count_, free_count_, \
				alloc_failed_count_, free_failed_count_);
		}

		void printInfoAll()
		{
			printf("Memory Info (%d)(a:%u/f:%u\taf:%u/ff:%u)\n", total_alloc_size_, alloc_count_, free_count_, \
				alloc_failed_count_, free_failed_count_);

			printf("--- Start Alloc Entry---\n");
			for (int i = 0; i < MAX_TRACE_ALLOC_COUNT; ++i) {
				if (alloc_list_[i].ptr) {
					printf("(0x%08X/%d/%d)\n", alloc_list_[i].ptr, alloc_list_[i].size, i);
				}
			}
			printf("---End Alloc Entry---\n");
		}

	};

	static HeapManager s_heap_manager;
}

void* operator new(size_t size)
{
	return ::lunas::s_heap_manager.add(size);
}

void* operator new[](size_t size)
{
	return operator new(size);
}

void* operator new(size_t size, const char* file, const int line)
{
	return ::lunas::s_heap_manager.add(size, file, line);
}

void* operator new[](size_t size, const char* file, const int line)
{
	return operator new(size, file, line);
}

void operator delete(void* ptr)
{
	return ::lunas::s_heap_manager.remove(ptr);
}

void operator delete[](void* ptr)
{
	return operator delete(ptr);
}

#define new new(__FILE__, __LINE__)
