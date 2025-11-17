
@KBD

D=M

@R0

M=D

(STLOOP)
@KBD
D=M

@R0

D=D-M

@STLOOP
D;JEQ
@START
0;JMP

@flag
M=1

(START)

@KBD

D=M

@R0

M=D

@SCREEN
D=A
@curr
M=D

@i
M=0

@flag
M=!M

(LOOP)
@8191
D=A
@i
D=D-M
@STLOOP
D;JEQ


@flag
D=M

@WHITE

D;JEQ

@BLACK

0;JMP

(BLACK)
    @curr
    D=M

    @i

    A=D+M

    M=-1
    @CONTINUE

    0;JMP

(WHITE)
    @curr
    D=M

    @i

    A=D+M

    M=0

(CONTINUE)

@i

M=M+1

@LOOP
0;JMP