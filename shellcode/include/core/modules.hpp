#ifndef MODULES_HPP
#define MODULES_HPP

#include "core/macros.hpp"
#include "core/procs.hpp"

#include <windows.h>

// Module hashes calculated with script/calc_hash_module
#define HASH_MODULE_KERNEL32 0xf4796887
#define HASH_MODULE_NTDLL    0x3cd7873f
#define HASH_MODULE_USER32   0xecf87bd5

namespace Modules
{
    ULONG StringToHashModule(WCHAR* wStr, SIZE_T dwStrLen);
    PVOID GetModuleByHash(DWORD dwHash);
    // PVOID LoadModule(Procs::PPROCS pProcs, LPWSTR lpDllName);
}

#endif // MODULES_HPP