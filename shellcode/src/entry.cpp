#include "entry.hpp"

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

    Procs::LPPROC_LDRLOADDLL lpLdrLoadDll = reinterpret_cast<Procs::LPPROC_LDRLOADDLL>(Procs::GetProcAddressByHash(hNtdll, HASH_FUNC_LDRLOADDLL));

    // ------------------------------------------------------------------
    // Get runtime modules and functions
    // ------------------------------------------------------------------

    WCHAR wUser32[] = L"user32.dll";
    HMODULE hUser32 = (HMODULE)Modules::LoadModule(lpLdrLoadDll, wUser32);
    if (!hUser32)
    {
        return;
    }
    
    Procs::LPPROC_MESSAGEBOXA lpMessageBoxA = reinterpret_cast<Procs::LPPROC_MESSAGEBOXA>(Procs::GetProcAddressByHash(hUser32, HASH_FUNC_MESSAGEBOXA));
    
    // ------------------------------------------------------------------
    // Execute arbitrary function
    // ------------------------------------------------------------------

    lpMessageBoxA(NULL, "Injected shellcode successfully;)", "shcldr", MB_OK);
}