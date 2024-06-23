CCX64 = x86_64-w64-mingw32-g++
CCX86 = i686-w64-mingw32-g++

CFLAGS = -Os -s -masm=intel -nostdlib
CFLAGS += -ffunction-sections -fno-ident -fno-asynchronous-unwind-tables -w
CFLAGS += -fpack-struct=8 -falign-labels=1 -falign-jumps=1 -fPIC
CFLAGS += -Wl,-Tscript/linker.ld
CFLAGS += -Wl,-s,--no-seh,--enable-stdcall-fixup

INCLUDE = -I include

ASM_OUT = build/alignstack.o

SOURCE = src/core/*.cpp src/entry.cpp

OUTTEMP = build/tmp.exe

OUTFILE = build/shellcode.bin

x64:
	mkdir -p build && rm -rf build/*
	nasm -f win64 -o $(ASM_OUT) src/asm/alignstack.x64.asm
	$(CCX64) -o $(OUTTEMP) $(CFLAGS) $(INCLUDE) $(SOURCE) $(ASM_OUT)
	python3 script/extract.py -f $(OUTTEMP) -o $(OUTFILE)

x86:
	mkdir -p build && rm -rf build/*
	nasm -f win32 -o $(ASM_OUT) src/asm/alignstack.x86.asm
	$(CCX86) -o $(OUTTEMP) $(CFLAGS) $(INCLUDE) $(SOURCE) $(ASM_OUT)
	python3 script/extract.py -f $(OUTTEMP) -o $(OUTFILE)
