@echo off
clang full_adder.c -o Release/full_adder.exe -Weverything -Wno-reserved-macro-identifier
Release\full_adder.exe
