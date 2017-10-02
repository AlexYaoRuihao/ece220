 Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor

 .ORIG x3000

    AND R4,R4,#0
    ADD R4,R4,#3
REC    AND R2,R2,#0  ; 
    ADD R2,R2,#4
    AND R1,R1,#0
    AND R0,R0,#0
    AND R5,R5,#0

CHK    ADD R3,R3,#0
    BRzp ZERO
    ADD R1,R1,#1
ZERO    ADD R3,R3,R3    
    ADD R2,R2,#-1
    BRz HEX
    ADD R1,R1,R1
    ADD R2,R2,#0
    BRp CHK

HEX    ADD R5,R1,#-10
    BRn NB
CHAR    LD R0,ASCIIA
    ADD R0,R5,R0
    OUT
    ADD R4,R4,#-1
    BRzp REC
    BRn END
NB    LD R0,ASCII0
    ADD R0,R1,R0    
    OUT
    ADD R4,R4,#-1
    BRzp REC
    BRn END

 ; stop the computer
END     HALT

 ; program data section starts here
ASCII0    .FILL x30

ASCIIA    .FILL X41

 .END
