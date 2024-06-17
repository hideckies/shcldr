# Shellcode Generator & Loader for Windows

Simple implementation of Windows shellcode generator & loader written in C++.   

## Install Dependencies

```sh
sudo apt install git build-essential nasm g++-mingw-w64 python3-pefile
```

## Compile

We need to compile both shellcode and loader on Linux using MinGW.

```sh
# 1. Compile shellcode
cd shellcode && make
file build/shellcode.x64.bin

# 2. Compile loader
cd ldr && make
file build/ldr.x64.exe
```

## Run

Transfer the generated shellcode and loader to Windows machine and execute as below:

```powershell
.\ldr.x64.exe <PID> <SHELLCODE_PATH>
# e.g.
.\ldr\build\ldr.x64.exe 12345 .\shellcode\build\shellcode.x64.bin
```
