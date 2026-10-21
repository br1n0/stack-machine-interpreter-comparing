#!/bin/bash
# transpile a stack language, is compilated two times for benchmark
clear


run(){
	name=$1
	time -f "%e $1" "./$name"
}

#rm transpiled*
#rm transpiler
#rm a.out

#FN="test4.f"
FN="test3_function_call.f"

#compile the transpiler
gcc transpiler.c -o transpiler 

#transpile program into c language
./transpiler $FN

#compile the program with O2
LEVEL="O2"
#gcc -I. -$LEVEL native_transpiled_run1.c    -o native_transpiled_run1_$LEVEL
gcc -I. -$LEVEL native_transpiled_run400k.c -o native_transpiled_run400k_$LEVEL


#compile the program with Ofast
LEVEL="Ofast"
#gcc -I. -$LEVEL native_transpiled_run1.c    -o native_transpiled_run1_$LEVEL
gcc -I. -$LEVEL native_transpiled_run400k.c -o native_transpiled_run400k_$LEVEL



#I changed main into run, to include and run
#gcc -I. -$LEVEL transpiled_main.c -o transpiled_main -lm -ldl 2>transpiled_main_stderr.txt

