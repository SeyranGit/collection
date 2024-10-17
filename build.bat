@echo off
clang main.c List/list.c -o Release/list.exe -Weverything
Release\list.exe
