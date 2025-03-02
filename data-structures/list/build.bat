@echo off
clang main.c list/list.c -o Release/list.exe -Weverything -Wno-pre-c23-compat -std=c23
Release\list.exe
