#include <windows.h> 
#include <stdio.h> 
#include <iostream>

typedef bool(__cdecl* MYPROC)(const char*, const char*);

#define DLL_PATH "../../Lab3/Debug/Dll.dll"

const char hello[] = "Hello, world";
const char love[] = "I love you";

int main(void)
{
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT(DLL_PATH));
 
    size_t size = strlen(love) + 1;
    char* dest = (char*)malloc(size * sizeof(char));

    strcpy_s(dest, size, love);

    std::cout << dest << std::endl;

    
    if (NULL != hinstLib)
    {
        ProcAdd = (MYPROC)GetProcAddress(hinstLib, "ReplaceMemory");

        if (NULL != ProcAdd)
        {
            fRunTimeLinkSuccess = TRUE;
            (ProcAdd)(love, hello);
        }
       
        fFreeResult = FreeLibrary(hinstLib);
    }

    if (!fRunTimeLinkSuccess)
        printf("Message printed from executable\n");
    std::cout << dest;    

    return 0;

}