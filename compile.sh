#!/bin/sh

#compile
gcc stack_switch.c -lm -O0 -o stack_switch 



echo "stack_switch"
echo .
time ./stack_switch
echo ""
