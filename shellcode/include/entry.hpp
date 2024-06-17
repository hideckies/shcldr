#ifndef SHELLCODE_HPP
#define SHELLCODE_HPP

#include "core/macros.hpp"
#include "core/nt.hpp"
#include "core/modules.hpp"
#include "core/procs.hpp"

extern "C" VOID AlignStack();
extern "C" VOID Entry();

#endif // SHELLCODE_HPP