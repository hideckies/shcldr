#ifndef LDR_HPP
#define LDR_HPP

#include <stdio.h>
#include <windows.h>

namespace Ldr
{
    LPVOID ReadShellcode(PCHAR filePath, DWORD& dwDataSize);
    BOOL InjectShellcode(DWORD dwPID, LPVOID lpBuffer, DWORD dwBufferSize);
}

#endif // LDR_HPP