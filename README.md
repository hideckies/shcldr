# Shellcode & Loader of Windows

Simple implementation of Windows shellcode &loader written in C++.   

## Install Dependencies

```sh
sudo apt install git build-essential nasm g++-mingw-w64 python3-pefile
```

## Compile

We need to compile both shellcode and loader on Linux using MinGW.

```sh
# 1. Compile shellcode
cd shellcode && make
file build/shellcode.bin

# 2. Compile loader
cd ldr && make
file build/ldr.exe
```

## Run

Transfer the generated shellcode and loader to Windows machine and execute as below:

```powershell
.\ldr.exe <PID> <SHELLCODE_PATH>
# e.g.
.\ldr.exe 12345 .\shellcode.bin
```
