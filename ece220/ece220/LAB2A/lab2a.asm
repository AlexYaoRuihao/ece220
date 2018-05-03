.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.
START
GETC
OUT
LD R1, SPACE
NOT R1, R1
ADD R1, R1, #1
ADD R1, R0, R1
BRz START

LD R1, CHAR_RETURN
NOT R1, R1
ADD R1, R1, #1
ADD R1, R0, R1
BRnp Y
LD R3, STACK_TOP
LD R4, STACK_START
NOT R4, R4
ADD R4, R4, #1
ADD R4, R3, R4
BRz Zero_Case
Non_Zero_Case
AND R5, R5, #0
ADD R5, R5, #-1
BRnzp DONE
Zero_Case
AND R5, R5, #0
ADD R5, R5, #1
BRnzp DONE



Y
JSR IS_BALANCED
BRnzp START

DONE HALT

SPACE   .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
Left_Parenthesis .FILL x0028
Right_Parenthesis .FILL x0029
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack, if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
ST R1, IS_BALANCED_SaveR1
ST R3, IS_BALANCED_SaveR3

LD R1, Left_Parenthesis
AND R5, R5, #0
NOT R1, R1
ADD R1, R1, #1
ADD R1, R0, R1
BRz PUSH_LOOP
POP_LOOP
ST R7, IS_BALANCED_SaveR7
JSR POP
LD R7, IS_BALANCED_SaveR7
LD R2, STACK_TOP



;LDR R3, R2, #0;    R3 contains the value of POP character
LD R1, Left_Parenthesis
NOT R1, R1
ADD R1, R1, #1
ADD R1, R0, R1
BRnp Unbalanced
ADD R5, R5, #1
BRnzp X
Unbalanced
ADD R5, R5, #-2
BRnzp DONE


PUSH_LOOP
ST R7, IS_BALANCED_SaveR7
JSR PUSH
LD R7, IS_BALANCED_SaveR7
X
LD R1, IS_BALANCED_SaveR1
LD R3, IS_BALANCED_SaveR3
RET



NEG_OPEN .FILL xFFD8
IS_BALANCED_SaveR1 .BLKW #1
IS_BALANCED_SaveR3 .BLKW #1
IS_BALANCED_SaveR4 .BLKW #1
IS_BALANCED_SaveR7 .BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

.END
