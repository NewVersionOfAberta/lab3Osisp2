
#include "pch.h"
#include "Dll.h"
#include <windows.h>

const int MAX_LEN = 100;

using ADDR_INFO = struct _adrInfo {
    PVOID baseAddress;
    SIZE_T size;
};

bool FindAndReplace(ADDR_INFO addrInfo, HANDLE hProc, const char* src, const char* dest) {
    
    int srcLen = strnlen(src, MAX_LEN);
    int destLen = strnlen(dest, MAX_LEN);
    bool isModified = false;

   
    PBYTE tmpBuffer = (PBYTE)(addrInfo.baseAddress);
    for (unsigned int i = 0; i + srcLen < addrInfo.size; i++) {
        if (memcmp(tmpBuffer, src, srcLen) == 0) {
            memcpy(tmpBuffer, dest, destLen + 1);
            isModified = true;
        }
        tmpBuffer++;
    }
   
    return isModified;
}


bool ReplaceMemory(const char* src, const char* dest)
{
    SYSTEM_INFO sysInfo;
    MEMORY_BASIC_INFORMATION memBaseInfo;
    GetSystemInfo(&sysInfo);
    PVOID currentAddress = sysInfo.lpMinimumApplicationAddress;
    HANDLE hProcess = GetCurrentProcess();
    ADDR_INFO addr_info;

    bool isModifyed = false;

    while (sysInfo.lpMaximumApplicationAddress >= currentAddress) {
        VirtualQueryEx(hProcess, currentAddress, &memBaseInfo, sizeof(MEMORY_BASIC_INFORMATION));
        if (memBaseInfo.State | MEM_COMMIT 
            && (memBaseInfo.Protect & PAGE_READWRITE) 
            && !(memBaseInfo.Protect & PAGE_GUARD)) {
            addr_info.baseAddress = memBaseInfo.BaseAddress;
            addr_info.size = memBaseInfo.RegionSize;
            isModifyed = FindAndReplace(addr_info, hProcess, src, dest);
        }
        currentAddress = (PVOID)((DWORD)currentAddress + (DWORD)memBaseInfo.RegionSize);
    }
    return isModifyed;
}
