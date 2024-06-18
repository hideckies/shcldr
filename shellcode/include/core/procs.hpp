#ifndef PROCS_HPP
#define PROCS_HPP

#include "core/macros.hpp"
#include "core/nt.hpp"

#include <windows.h>

// Function hashes calculated with script/calc_hash_func.py
#define HASH_FUNC_LDRLOADDLL              0x19cb5e59
#define HASH_FUNC_MESSAGEBOXA             0xcc4a1d08

namespace Procs
{
    // NTAPI
    typedef NTSTATUS (NTAPI* LPPROC_LDRLOADDLL)(PWSTR DllPath, PULONG DllCharacteristics, Nt::PUNICODE_STRING DllName, PVOID *DllHandle);
    
    // WINAPI
    typedef int (WINAPI* LPPROC_MESSAGEBOXA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

    DWORD StringToHashFunc(CHAR* str);
    PVOID GetProcAddressByHash(HMODULE hModule, DWORD dwHash);
}

#endif // PROCS_HPP