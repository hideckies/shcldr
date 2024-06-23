CCX64 = x86_64-w64-mingw32-g++
CCX86 = i686-w64-mingw32-g++

CFLAGS = -Wall -Os -s
CFLAGS += -fPIC -fno-exceptions -ffunction-sections -fdata-sections
CFLAGS += -falign-jumps=1 -falign-labels=1 -fno-asynchronous-unwind-tables
CFLAGS += -static-libgcc

INCLUDE = -I include

SOURCE = src/ldr.cpp src/main.cpp

OUTFILE = build/ldr.exe

x64:
	mkdir -p build && rm -rf build/*
	$(CCX64) -o $(OUTFILE) $(CFLAGS) $(INCLUDE) $(SOURCE)

x86:
	mkdir -p build && rm -rf build/*
	$(CCX86) -o $(OUTFILE) $(CFLAGS) $(INCLUDE) $(SOURCE)
