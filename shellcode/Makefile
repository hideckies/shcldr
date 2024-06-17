CCX64 = x86_64-w64-mingw32-g++
CCX86 = i686-w64-mingw32-g++

CFLAGS = -Os -masm=intel -nostdlib
CFLAGS += -s -ffunction-sections -fno-ident -fno-asynchronous-unwind-tables -w
CFLAGS += -fpack-struct=8 -falign-labels=1 -falign-jumps=1 -fPIC
CFLAGS += -Wl,-Tscript/linker.ld
CFLAGS += -Wl,-s,--no-seh,--enable-stdcall-fixup

INCLUDE = -I include

SOURCE = src/core/*.cpp src/entry.cpp

OUTTEMPX64 = build/tmp.x64.exe
OUTTEMPX86 = build/tmp.x86.exe

OUTFILEX64 = build/shellcode.x64.bin
OUTFILEX86 = build/shellcode.x86.bin

all: x64 x86

x64:
	mkdir -p build
	nasm -f win64 -o build/alignstack.x64.o src/asm/alignstack.x64.asm
	$(CCX64) -o $(OUTTEMPX64) $(CFLAGS) -Iinclude $(SOURCE) build/alignstack.x64.o
	python3 script/extract.py -f $(OUTTEMPX64) -o $(OUTFILEX64)

x86:
	mkdir -p build
	nasm -f win32 -o build/alignstack.x86.o src/asm/alignstack.x86.asm
	$(CCX86) -o $(OUTTEMPX86) $(CFLAGS) -Iinclude $(SOURCE) build/alignstack.x86.o
	python3 script/extract.py -f $(OUTTEMPX86) -o $(OUTFILEX86)
