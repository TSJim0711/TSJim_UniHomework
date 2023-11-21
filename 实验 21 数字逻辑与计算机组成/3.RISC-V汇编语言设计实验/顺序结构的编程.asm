.data
numa:	.word 20
numb:	.word 40
numc:	.word 70
.text
main:
	#载入暂存器
	lw a1,numa
	lw a3,numb
	lw a5,numc	
	#计算，8a+a+a
	slli a2,a1,8
	add a2,a2,a1
	add a2,a2,a1
	slli a3,a3,2
	add a4,a4,a3
	add a4,a4,a3
	#储存答案于a0
	add a0,a2,a4
	sub a0,a0,a5
	#结束
	addi a7,x0,10
ecall 
