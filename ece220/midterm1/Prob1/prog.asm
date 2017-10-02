; Implement a program to find the nearest smaller (or equal) perfect square of a given positive number
; The input will be stored in R2 and output (the nearest perfect square) should be stored in R3
; TODO: Write a subroutine called "PSquare" which returns the nearest perfect square of a given input and 
;       you must invoke this subroutine in the main part.
; Note : R2, R4, R5 and R6 must be left unchanged in PSquare.
;
; 
; PSquare :  input is stored in R2
;            output is stored in R3

.ORIG	x3000		; starting address is x3000

;;YOUR CODE STARTS HERE

	JSR PSquare
	HALT


;IN:R2 OUT:R3 UNCHANGED:R456
PSquare
	ST R7,SAVER7
	;ST R1,SAVER1
	;ST R0,SAVER0
	AND R1,R1,#0
	AND R3,R3,#0
RPLUS	ADD R1,R1,#1
	ADD R0,R1,#0
SQR	ADD R3,R3,R1
	ADD R0,R0,#-1
	BRp SQR	
	NOT R0,R3
	ADD R0,R0,#1
	ADD R0,R0,R2
	BRp RPLUS

	ADD R0,R1,#0
	AND R3,R3,#0
FINAL	ADD R3,R3,R1
	ADD R0,R0,#-1
	BRp FINAL
	BRnz DONE


DONE	LD R7,SAVER7
	;LD R1,SAVER1
	;LD R0,SAVER0
	RET


SAVER7	.BLKW 1
SAVER1	.BLKW 1
SAVER0	.BLKW 1

.END



