@echo off
clang malloc.c -o Release/malloc.exe -Weverything
Release\malloc.exe
