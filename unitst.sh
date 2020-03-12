#!/bin/sh
cd /Users/ada/Desktop/V1
make re
cd /Users/ada/Desktop/dyali
rm examples/*.cor
rm diff*
cd /Users/ada/Desktop/dyalhom
rm examples/*.cor
rm diff*
cd /Users/ada/Desktop
mv V1/asm /Users/ada/Desktop/dyali
sh asm_script.sh
cd /Users/ada/Desktop/dyali
rm asm
