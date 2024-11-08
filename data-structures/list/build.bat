@echo off
clang main.c list/list.c -o Release/list.exe -Weverything
Release\list.exe
