@echo off
clang main.c stack/stack.c "../list/list/list.c" -o Release/stack.exe -Weverything
Release\stack.exe
