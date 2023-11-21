#计算C语言表达式: if (x>y) z=x+5; else z=y-5。其中z存放在寄存器a1中，x、y存放的寄存器不限。#
.data
numx:	.word 33
numy:	.word 66
numz:	.word 22
.text
main:
	lw t1,numx
	lw t2,numy
	lw a1,numz
	
	li s0,5
	ble t2,t1,lable1
lable0:
	sub a1,t2,s0
	b endif
lable1:
	add a1,t1,s0
endif:
