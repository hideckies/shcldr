#include "core/modules.hpp"

namespace Modules
{
    ULONG StringToHashModule(WCHAR* wStr, SIZE_T dwStrLen)
    {
        ULONG  dwHash   = HASH_IV;
        WCHAR* pwStr    = wStr;
        SIZE_T dwCnt    = 0;

        do
        {
            WCHAR c = *pwStr;

            if (!c)
            {
                break;
            }

            // If a character is uppercase, convert it to lowercase.
            if (c >= L'A' && c <= L'Z')
            {
                c += L'a' - L'A';
            }

            dwHash = dwHash * RANDOM_ADDR + c;
            ++pwStr;
            dwCnt++;

            if (dwStrLen > 0 && dwCnt >= dwStrLen)
            {
                break;
            }
        } while (TRUE);

        return dwHash & 0xFFFFFFFF;
    }

    PVOID GetModuleByHash(DWORD dwHash)
    {
        PPEB pPeb = (PPEB)PPEB_PTR;
        PPEB_LDR_DATA pLdr = (PPEB_LDR_DATA)pPeb->Ldr;

        // Get the first entry
        PLDR_DATA_TABLE_ENTRY pDte = (PLDR_DATA_TABLE_ENTRY)pLdr->InLoadOrderModuleList.Flink;

        while (pDte)
        {
            if (StringToHashModule(pDte->BaseDllName.Buffer, pDte->BaseDllName.Length) == dwHash)
            {
                return pDte->DllBase;
            }

            // Get the next entry
            pDte = *(PLDR_DATA_TABLE_ENTRY*)(pDte);
        }

        return nullptr;
    }

    // Load a module with LdrLoadDll.
    PVOID LoadModule(Procs::LPPROC_LDRLOADDLL lpLdrLoadDll, LPWSTR lpDllName)
    {
        PVOID pModule = nullptr;
        LPCWSTR lpcDllName = static_cast<LPCWSTR>(lpDllName);

        // Get string length
        LPCWSTR wStr2;
        for (wStr2 = lpcDllName; *wStr2; ++wStr2);
		USHORT uDllNameLen = (wStr2 - lpcDllName) * sizeof(WCHAR);

		UNICODE_STRING usDllName = {0};
		usDllName.Buffer = lpDllName;
		usDllName.Length = uDllNameLen;
        usDllName.MaximumLength = uDllNameLen + sizeof(WCHAR);

        NTSTATUS status = lpLdrLoadDll(
            nullptr,
            nullptr,
            &usDllName,
            &pModule
        );
		if (status != STATUS_SUCCESS || !pModule)
		{
			return nullptr;
		}

        return pModule;
    }
}