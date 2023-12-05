#利用数据结构课所学的任意一种排序方式，将
数据区的10个数字按从小到大排序#
.data
 array:	 .word  -15,1024,12,60,19,26,-18,19,100,86
.text

la a0,array #永远指向array头
la a1,array
la a2,array
li s2,1
li s3,4
li t1,9 #数组大小
loopStart:
	mul t2,t0,s3 #loop后指针移位
	add a1,a0,t2
	add a2,a1,s3
	lw a4,(a1) #交换
	lw a5,(a2)
	blt a4,a5,switchEnd
	sw a5,(a1)
	sw a4,(a2)
switchEnd:
	addi t0,t0,1 #t0 is counter
	bne t0,t1,loopStart
oneLoopEnd:
	sub t1,t1,s2 #t1-1 因为最后一个是最大，可以无视
	sub t0,t0,t0 #set t0=0
	bne t1,s2,loopStart #if t1!=1
