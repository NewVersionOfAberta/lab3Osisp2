#pragma once
#ifdef MEM_READ_EXPORTS
#define MEMREADERLIBRARY_API __declspec(dllexport)
#else
#define MEMREADERLIBRARY_API __declspec(dllimport)
#endif



extern "C" MEMREADERLIBRARY_API bool ReplaceMemory(const char* src, const char* dest);

