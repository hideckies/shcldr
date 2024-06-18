CCX64 = x86_64-w64-mingw32-g++
CCX86 = i686-w64-mingw32-g++

CFLAGS = -Wall -Os -s
CFLAGS += -fPIC -fno-exceptions -ffunction-sections -fdata-sections
CFLAGS += -falign-jumps=1 -falign-labels=1 -fno-asynchronous-unwind-tables
CFLAGS += -static-libgcc

INCLUDE = -I include

SOURCE = src/ldr.cpp src/main.cpp

OUTX64 = build/ldr.x64.exe
OUTX86 = build/ldr.x86.exe

all: x64 x86

x64:
	mkdir -p build
	$(CCX64) -o $(OUTX64) $(CFLAGS) $(INCLUDE) $(SOURCE)

x86:
	mkdir -p build
	$(CCX64) -o $(OUTX86) $(CFLAGS) $(INCLUDE) $(SOURCE)
