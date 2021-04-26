#!/usr/bin/env python
#检测当前终端支持色彩
import sys
import os
 
def echo(msg):
    os.system('echo -n "' + str(msg) + '"')
 
def out(n):
    os.system("tput setab " + str(n) + "; echo -n " + ("\"% 4d\"" % n))
    os.system("tput setab 0")
 
# normal colors 1 - 16
os.system("tput setaf 16")
for n in range(8):
    out(n)
echo("\n")
for n in range(8, 16):
    out(n)
 
echo("\n")
echo("\n")
 
y=16
while y < 231:
    for z in range(0,6):
        out(y)
        y += 1
 
    echo("\n")
 
echo("\n")
 
for n in range(232, 256):
    out(n)
    if n == 237 or n == 243 or n == 249:
        echo("\n")
 
echo("\n")
