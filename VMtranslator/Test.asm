// function Sys.init 0
@fun_end_Sys.init
0;JMP
(fun_Sys.init)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
M=D+M
// push constant 10
@10
D=A
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
// push constant 20
@20
D=A
@SP
M=M+1
A=M-1
M=D
// pop argument 0
@ARG
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
// push constant 3000
@3000
D=A
@SP
M=M+1
A=M-1
M=D
// pop pointer 0
@SP
M=M-1
A=M
D=M

@THIS
M=D
// push constant 4000
@4000
D=A
@SP
M=M+1
A=M-1
M=D
// pop pointer 1
@SP
M=M-1
A=M
D=M

@THAT
M=D
// push constant 50
@50
D=A
@SP
M=M+1
A=M-1
M=D
// pop this 0
@THIS
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
// push constant 60
@60
D=A
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
// push constant 70
@70
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
// push constant 80
@80
D=A
@SP
M=M+1
A=M-1
M=D
// pop static 0
@Test_0
D=A
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
// push this 0
@THIS
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
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
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
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// push static 0
@Test_0
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
// pop temp 1
@R5
D=A
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
// push constant 10
@10
D=A
@SP
M=M+1
A=M-1
M=D
// push constant 10
@10
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
@eq_0
D;JEQ
@SP
A=M
A=A-1
M=0
(eq_0)
// not
@SP
A=M
A=A-1
M=!M
// if-goto ERROR
@SP
M=M-1
A=M
D=M
@.ERROR
D;JNE
// push constant 20
@20
D=A
@SP
M=M+1
A=M-1
M=D
// push constant 10
@10
D=A
@SP
M=M+1
A=M-1
M=D
// gt
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@gt_0
D;JGT
@SP

A=M
A=A-1
M=0
(gt_0)
// not
@SP
A=M
A=A-1
M=!M
// if-goto ERROR
@SP
M=M-1
A=M
D=M
@.ERROR
D;JNE
// push constant 10
@10
D=A
@SP
M=M+1
A=M-1
M=D
// push constant 20
@20
D=A
@SP
M=M+1
A=M-1
M=D
// lt
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@lt_0
D;JLT
@SP
A=M
A=A-1
M=0
(lt_0)
// not
@SP
A=M
A=A-1
M=!M
// if-goto ERROR
@SP
M=M-1
A=M
D=M
@.ERROR
D;JNE
// push constant 100
@100
D=A
@SP
M=M+1
A=M-1
M=D
// push constant 200
@200
D=A
@SP
M=M+1
A=M-1
M=D
// call Sys.addTwo 2
@fun_returnAddress_Sys.addTwo_47
D=A
@SP
A=M
M=D
@LCL
D=M
@SP
M=M+1
A=M
M=D
@ARG
D=M
@SP
M=M+1
A=M
M=D
@THIS
D=M
@SP
M=M+1
A=M
M=D
@THAT
D=M
@SP
M=M+1
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@2
D=D-A
@ARG
M=D
@fun_Sys.addTwo
0;JMP
(fun_returnAddress_Sys.addTwo_47)
// pop temp 2
@R5
D=A
@2
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// goto END
@.END
0;JMP
// label ERROR
(.ERROR)
// push constant 9999
@9999
D=A
@SP
M=M+1
A=M-1
M=D
// pop temp 7
@R5
D=A
@7
D=D+A
@SP
M=M-1
A=M
M=D+M
D=M-D
M=M-D
A=M
M=D
// label END
(.END)
// goto END
@.END
0;JMP
// function Sys.addTwo 0
@fun_end_Sys.addTwo
0;JMP
(fun_Sys.addTwo)
@SP
D=M
@LCL
M=D
@0
D=A
@SP
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
// add
@SP
M=M-1
A=M
D=M
A=A-1
M=D+M
// return
(fun_return_Sys.addTwo)
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
(fun_end_Sys.addTwo)
