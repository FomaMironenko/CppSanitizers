#!/usr/bin/python3

import os
from sys import platform

cwd = os.getcwd()
parent = os.path.dirname(cwd)
base = os.path.basename(cwd)

if 'make.py' not in os.listdir(parent):
    print('Run make.py from project directory')
    exit(1)
if 'main.cpp' not in os.listdir(cwd):
    print('No main.cpp found in project directory')
    exit(1)


if platform != 'linux':
    LEAK = ''
    THREAD = ''
    print(f'Leak sanitizer is unavailable at {platform} platform')
else:
    THREAD = '-pthread'
    LEAK = ',leak'



COMMON_COMMAND = f'g++ main.cpp -std=c++17 {THREAD} -g '
print(f'Building target: {base}')

MAIN_COMMAND = COMMON_COMMAND + '-o main'
print(f'Compiling:  {MAIN_COMMAND}')
res = os.system(MAIN_COMMAND)
if res != 0:
    exit(1)

ASAN_COMMAND = COMMON_COMMAND + f'-fsanitize=address{LEAK} -o asan'
print(f'Compiling:  {ASAN_COMMAND}')
os.system(ASAN_COMMAND)

USAN_COMMAND = COMMON_COMMAND + f'-fsanitize=undefined{LEAK} -o usan'
print(f'Compiling:  {USAN_COMMAND}')
os.system(USAN_COMMAND)

TSAN_COMMAND = COMMON_COMMAND + f'-fsanitize=thread -o tsan'
print(f'Compiling:  {TSAN_COMMAND}')
os.system(TSAN_COMMAND)
