<?php

$n= 2000;
$i= 0;
echo "vm.pc = 0;\n";

echo "vm.stack[0]= +2;\n";

for($i=1;$i<=$n;$i++)
	echo "vm.stack[{$i}]= +1;\n";

echo "vm.stack[{$i}]= 0;\n";
$limit= $i+1;
echo "vm.sp = {$limit};\n";

//echo "vm.code[4]= OP_RETURN;

echo "vm.code[{$i}]= OP_RETURN;\n";
$i--;
echo "vm.code[{$i}]= OP_MUL;\n";
$i--;

for(;$i>=0;$i--){
	echo "vm.code[{$i}]= OP_SUB;\n";
}

echo "vm.code_size={$limit};\n";
/*
vm.pc = 0;

vm.stack[0]= +4;
vm.stack[1]= +1;
vm.stack[2]= +1;
vm.stack[3]= +1;
vm.stack[4]= 0;
vm.sp = 5;

vm.code[4]= OP_RETURN;
vm.code[3]= OP_MUL;
vm.code[2]= OP_SUB;
vm.code[1]= OP_SUB;
vm.code[0]= OP_SUB;
vm.code_size=5;
*/ 


?>