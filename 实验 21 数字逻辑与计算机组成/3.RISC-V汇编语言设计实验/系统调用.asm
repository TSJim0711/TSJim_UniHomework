#输出提示信息“请输入姓名：”，从键盘输入本人姓名的字符串；输出提示信息“请输入学号：”，输入本人学号后3位（整数形式）。程序结束后调用exit功能退出。#
.data 
 stringName: .ascii   "请输入姓名："
 blank: .align 6
 stringID: .ascii "请输入学号后3位："
 blank2: .align 6
 stringPrint: .ascii "已输入信息：\n"
 .text
 la a0, stringName
 li a7,4
 ecall #^要求输入姓名#
 la s0, stringName
 addi s0, s0 ,34
 mv a0, s0
 li a1, 16
 li a7 ,8
 ecall  #^输入姓名#
 la a0,stringID
 li a7,4
 ecall #^要求输入学号后3位#
 li a7,5
 ecall 
 mv s1,a0 #^输入学号后3位#
 la a0, stringPrint
 li a7,4
 ecall #^输出已输入信息：#
 mv a0,s0
 li a7,4
 ecall #^输出姓名#
 mv a0,s1
 li a7,1
 ecall #^输出学号后3位#
 li a7,10
 ecall
