#ifndef MACROS_HPP
#define MACROS_HPP

#ifdef _WIN64
#define PPEB_PTR __readgsqword(0x60)
#else
#define PPEB_PTR __readfsdword(0x30)
#endif

#define DEREF(name)     *(UINT_PTR*)(name)
#define DEREF_64(name)  *(DWORD64*)(name)
#define DEREF_32(name)  *(DWORD*)(name)
#define DEREF_16(name)  *(WORD*)(name)
#define DEREF_8(name)   *(BYTE*)(name)

#define SEC(s, x) __attribute__((section("." #s "$" #x "")))

// They're used for resolving modules and functions
#define HASH_IV     0x35
#define RANDOM_ADDR 0xab10f29f

#endif // MACORS_HPP