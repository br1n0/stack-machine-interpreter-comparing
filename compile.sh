#!/bin/sh

#compile
gcc stack_function_table.c -lm -O0 -o stack_function_table 
gcc stack_goto.c -lm -O0 -o stack_goto 
gcc stack_subroutine.c -lm -O0 -o stack_subroutine 
gcc stack_switch.c -lm -O0 -o stack_switch 

#gcc native.c -lm -o native 


time ./stack_function_table
clear

echo "stack_function_table"
echo .
time ./stack_function_table
echo ""
echo ""
echo "stack_switch"
echo .
time ./stack_switch
echo ""
echo ""
echo "stack_goto"
echo .
time ./stack_goto
echo ""
echo ""
echo "stack_subroutine"
echo .
time ./stack_subroutine


#echo ""
#echo ""
#echo "native"
#echo .
#time ./native

