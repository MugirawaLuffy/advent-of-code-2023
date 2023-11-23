@echo off
set SRC_DIR= .
set INCLUDE_DIRS=-I%SRC_DIR% -I ..

set OUTPUT_DIR=bin
set OUTPUT_FILE=application

mkdir %OUTPUT_DIR% 2>nul

cl %INCLUDE_DIRS% -o %OUTPUT_DIR%\%OUTPUT_FILE% ../file_impl.c main.c

if %errorlevel% neq 0 (
    echo Compilation failed
) else (
    echo Cleaning up after clang
    rem del /Q %SRC_DIR%\*.obj
    cd %OUTPUT_DIR%
    rem cls
    %OUTPUT_FILE%
    cd ..
)
