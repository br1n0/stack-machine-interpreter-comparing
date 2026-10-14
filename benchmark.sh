#!/bin/sh
#
Optimization='-O0'
compile() {
	echo "--- compile Optimization: $Optimization ---"
	gcc i_TTC_dispatch_computed_goto.c   -lm $Optimization -o i_TTC_dispatch_computed_goto 
	gcc i_TTC_dispatch_switch.c          -lm $Optimization -o i_TTC_dispatch_switch 
	gcc i_TTC_dispatch_if.c              -lm $Optimization -o i_TTC_dispatch_if 
	gcc i_TTC_dispatch_function_table.c  -lm $Optimization -o i_TTC_dispatch_function_table 
	gcc i_DCT_dispatch_function_call.c   -lm $Optimization -o i_DCT_dispatch_function_call
	gcc i_DCT_dispatch_function_call.c   -lm $Optimization -o i_DCT_dispatch_function_call

	gcc -std=c99 $Optimization -fPIC -fvisibility=hidden  -shared vm_shared.c -o vm_shared.so -lm
	gcc i_TTC_dispatch_function_table_shared.c -lm $Optimization -o i_TTC_dispatch_function_table_shared

	gcc native_function_call.c           -lm $Optimization -o native_function_call
	gcc native_function_init.c           -lm $Optimization -o native_function_init
	gcc native_baseline.c                -lm $Optimization -o native_baseline
}

run(){
	name=$1
	time -f "%e $1" "./$name"
}

benchmark(){
	run i_TTC_dispatch_computed_goto
	run i_TTC_dispatch_switch
	run i_TTC_dispatch_if
	run i_TTC_dispatch_function_table
	run i_DCT_dispatch_function_call
	run i_TTC_dispatch_function_table_shared
	run native_function_init
	run native_function_call
	run native_baseline
}


clear
echo "naive benchmak to against different machines:"
echo "remember to set the cpu performance governor, and remove other cpu usage"
echo 'echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor'
#read -p "Press key to continue.. " -n1 -s


Optimization='-O0'
compile
benchmark

Optimization='-O1'
compile
benchmark

Optimization='-O2'
compile
benchmark

Optimization='-O2 -fshort-enums'
compile
benchmark

Optimization='-O2 -march=native'
compile
benchmark

Optimization='-O3 -march=native -fshort-enums'
compile
benchmark

Optimization='-Ofast -march=native -fshort-enums'
compile
benchmark

