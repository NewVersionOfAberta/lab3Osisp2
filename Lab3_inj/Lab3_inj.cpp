// Lab3_inj.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

#define FILE_NAME "Dll_inj.dll"

HANDLE inject_DLL(int PID)
{
    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);         
    

    LPVOID DLLPath_addr = VirtualAllocEx(h_process, NULL, _MAX_PATH,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);   
    if (!DLLPath_addr) {
        return (HANDLE)-1;
    }
    SIZE_T written = 0;
    if (!WriteProcessMemory(h_process, DLLPath_addr, FILE_NAME,
        strlen(FILE_NAME), &written))
    {
        return (HANDLE)-1;
    }

    LPVOID LoadLib_addr = GetProcAddress(GetModuleHandle(L"Kernel32"),                 
        "LoadLibraryA");                             

    HANDLE h_rThread = CreateRemoteThread(h_process, NULL, 0,                       
        (LPTHREAD_START_ROUTINE)LoadLib_addr, DLLPath_addr, 0, NULL); 

    WaitForSingleObject(h_rThread, INFINITE);                         

    DWORD exit_code;
    GetExitCodeThread(h_rThread, &exit_code);                                         
                                                                                      

    CloseHandle(h_rThread);                                                           
    VirtualFreeEx(h_process, DLLPath_addr, 0, MEM_RELEASE);                          
    CloseHandle(h_process);                                                          

    return (HANDLE)exit_code;
}

int main()
{
    int pid;
    std::cout << "Enter pid:";
    std::cin >> pid;
    inject_DLL(pid);
}
