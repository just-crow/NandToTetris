// function Memory.init 0
@fun_end_Memory.init
0;JMP
(fun_Memory.init)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
M=D+M
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// pop static 0
@Memory_0
D=A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push constant 2048
@2048
D=A
@SP
M=M+1
A=M-1
M=D
// pop static 1
@Memory_1
D=A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push constant 2048
@2048
D=A
@SP
M=M+1
A=M-1
M=D
// pop static 2
@Memory_2
D=A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push static 1
@Memory_1
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push static 1
@Memory_1
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push constant 14334
@14334
D=A
@SP
M=M+1
A=M-1
M=D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// return
(fun_return_Memory.init)
@LCL
A=M-1
D=M
@THAT
M=D
@LCL
D=M
@5
D=D-A
A=D
D=M
@LCL
A=M-1
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@SP
A=M
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@SP
A=M
A=M
0;JMP
(fun_end_Memory.init)
// function Memory.peek 0
@fun_end_Memory.peek
0;JMP
(fun_Memory.peek)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
M=D+M
// push static 0
@Memory_0
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// return
(fun_return_Memory.peek)
@LCL
A=M-1
D=M
@THAT
M=D
@LCL
D=M
@5
D=D-A
A=D
D=M
@LCL
A=M-1
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@SP
A=M
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@SP
A=M
A=M
0;JMP
(fun_end_Memory.peek)
// function Memory.poke 0
@fun_end_Memory.poke
0;JMP
(fun_Memory.poke)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
M=D+M
// push static 0
@Memory_0
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push argument 1
@ARG
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// return
(fun_return_Memory.poke)
@LCL
A=M-1
D=M
@THAT
M=D
@LCL
D=M
@5
D=D-A
A=D
D=M
@LCL
A=M-1
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@SP
A=M
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@SP
A=M
A=M
0;JMP
(fun_end_Memory.poke)
// function Memory.alloc 2
@fun_end_Memory.alloc
0;JMP
(fun_Memory.alloc)
@SP
D=M
@LCL
M=D
@2
D=A
@SP
M=D+M
// push static 1
@Memory_1
D=M
@SP
M=M+1
A=M-1
M=D
// pop local 0
@LCL
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// label while_start_0
(.while_start_0)
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// eq
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@eq_7
D;JEQ
@SP
A=M
A=A-1
M=0
(eq_7)
// not
@SP
A=M
A=A-1
M=!M
// not
@SP
A=M
A=A-1
M=!M
// if-goto while_end_0
@SP
M=M-1
A=M
D=M
@.while_end_0
D;JNE
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// gt
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@gt_5
D;JGT
@SP

A=M
A=A-1
M=0
(gt_5)
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// eq
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@eq_8
D;JEQ
@SP
A=M
A=A-1
M=0
(eq_8)
// or
@SP
M=M-1
A=M
D=M
A=A-1
M=D|M
// not
@SP
A=M
A=A-1
M=!M
// if-goto if_label_end_1
@SP
M=M-1
A=M
D=M
@.if_label_end_1
D;JNE
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
// pop local 1
@LCL
D=M
@1
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push local 1
@LCL
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push local 1
@LCL
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 1
@1
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push local 1
@LCL
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// return
@fun_return_Memory.alloc
0;JMP
// goto full_if_label_end_1
@.full_if_label_end_1
0;JMP
// label if_label_end_1
(.if_label_end_1)
// label full_if_label_end_1
(.full_if_label_end_1)
// push local 0
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push that 0
@THAT
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop local 0
@LCL
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// goto while_start_0
@.while_start_0
0;JMP
// label while_end_0
(.while_end_0)
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// return
(fun_return_Memory.alloc)
@LCL
A=M-1
D=M
@THAT
M=D
@LCL
D=M
@5
D=D-A
A=D
D=M
@LCL
A=M-1
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@SP
A=M
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@SP
A=M
A=M
0;JMP
(fun_end_Memory.alloc)
// function Memory.deAlloc 0
@fun_end_Memory.deAlloc
0;JMP
(fun_Memory.deAlloc)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
M=D+M
// push static 2
@Memory_2
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
// pop temp 0
@R5
D=A
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push temp 0
@R5
D=A
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// pop that 0
@THAT
D=M
@0
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push argument 0
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
// push constant 2
@2
D=A
@SP
M=M+1
A=M-1
M=D
// sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
// pop static 2
@Memory_2
D=A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// push constant 0
@0
D=A
@SP
M=M+1
A=M-1
M=D
// return
(fun_return_Memory.deAlloc)
@LCL
A=M-1
D=M
@THAT
M=D
@LCL
D=M
@5
D=D-A
A=D
D=M
@LCL
A=M-1
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@LCL
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@LCL
A=M-1
D=M
@SP
A=M
M=D
@LCL
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@SP
A=M
A=M
0;JMP
(fun_end_Memory.deAlloc)
