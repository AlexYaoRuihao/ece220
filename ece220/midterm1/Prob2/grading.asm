; x3000

LD R2, STRSTART

LOOP
LDR R0, R2, #0
BRz FINISH		; We are done when we hit NULL
LD R1, BITMASK
JSR BITSWAP		; Do the bitswap
STR R0, R2, #0		; Writes back to the original location
ADD R2, R2, #1
BRnzp LOOP 
FINISH 
HALT

STRSTART .FILL x4000
BITMASK .FILL x0003	; set n = 3

;Do not touch or change and code above this line
;---------------------------------------------
;You must not change the separation line above
;Please write ALL your code for BITSWAP in between the separations lines,
;including all the labels, code, and .FILL commands

 
;Subroutine to swap bits
;Input: 
;R0: the ascii that to be swapped 
;R1: the number of bits to be swapped
; You can assume R1 is always 0, 1, 2, or 3
;Output: R0, the swapped ascii
BITSWAP
;;YOUR CODE STARTS HERE
	ST R7,SSAVER7
	ST R2,SSAVER2

	AND R3,R3,#0
	ADD R3,R3,#8
	ADD R2,R1,#0
	BRz ZERO
	ADD R2,R1,#-1
	BRz ONE
	ADD R2,R1,#-2
	BRz TWO
	ADD R2,R1,#-3
	BRz THREE
FOUR
	ADD R3,R3,#-4
	AND R2,R2,#0
	ADD R2,R2,#15
	AND R2,R2,R0
	NOT R6,R2
	ADD R6,R6,#1
	ADD R5,R0,R6
SHIFTF	ADD R2,R2,R2	;MOST SIG PART
	ADD R3,R3,#-1	
	BRp SHIFTF
	AND R4,R4,#0
	ADD R4,R4,#8
	ADD R4,R4,R4 ;16
	ADD R4,R4,R4 ;32
	ADD R4,R4,R4 ;64
	ADD R4,R4,R4 ;128   
	ADD R4,R4,R4 ;256
	ADD R4,R4,#-15
	ADD R4,R4,#-1
	AND R1,R4,R0 ; FIRST FOUR BIT
	
	NOT R1,R1
	ADD R1,R1,#1
	ADD R5,R5,R1 ; R5 MID PART
	JSR EXTRACT
	ADD R0,R0,R5
	ADD R0,R0,R2
	BRnzp SWAPDONE


THREE
	ADD R3,R3,#-3
	AND R2,R2,#0
	ADD R2,R2,#7
	AND R2,R2,R0
	NOT R6,R2
	ADD R6,R6,#1
	ADD R5,R0,R6
SHIFTH	ADD R2,R2,R2	;MOST SIG PART
	ADD R3,R3,#-1	
	BRp SHIFTH
	AND R4,R4,#0
	ADD R4,R4,#8
	ADD R4,R4,R4 ;16
	ADD R4,R4,R4 ;32
	ADD R4,R4,R4 ;64
	ADD R4,R4,R4 ;128   
	ADD R4,R4,R4 ;256
	ADD R4,R4,#-15
	ADD R4,R4,#-15
	ADD R4,R4,#-2
	AND R1,R4,R0 ; FIRST THREE BIT
	
	NOT R1,R1
	ADD R1,R1,#1
	ADD R5,R5,R1 ; R5 MID PART
	JSR EXTRACT
	ADD R0,R0,R5
	ADD R0,R0,R2
	BRnzp SWAPDONE



ZERO
	ADD R0,R0,#0
	BRnzp SWAPDONE	
ONE
	ADD R3,R3,#-1
	AND R2,R2,#0
	ADD R2,R2,#1
	AND R2,R2,R0
	NOT R6,R2
	ADD R6,R6,#1
	ADD R5,R0,R6
SHIFO	ADD R2,R2,R2	;MOST SIG PART
	ADD R3,R3,#-1
	BRp SHIFO

	AND R4,R4,#0
	ADD R4,R4,#8
	ADD R4,R4,R4 ;16
	ADD R4,R4,R4 ;32
	ADD R4,R4,R4 ;64
	ADD R4,R4,R4 ;128   
	AND R1,R4,R0 ; FIRST BIT
	
	NOT R1,R1
	ADD R1,R1,#1
	ADD R5,R5,R1 ; R5 MID PART
	JSR EXTRACT
	ADD R0,R0,R5
	ADD R0,R0,R2
	BRnzp SWAPDONE


TWO
	ADD R3,R3,#-2
	AND R2,R2,#0
	ADD R2,R2,#3
	AND R2,R2,R0
	NOT R6,R2
	ADD R6,R6,#1
	ADD R5,R0,R6
SHIFT	ADD R2,R2,R2	;MOST SIG PART
	ADD R3,R3,#-1	
	BRp SHIFT
	AND R4,R4,#0
	ADD R4,R4,#8
	ADD R4,R4,R4 ;16
	ADD R4,R4,R4 ;32
	AND R6,R6,#0
	ADD R6,R4,R4 ;64
	ADD R4,R6,R6 ;128   
	ADD R4,R4,R6 ;192
	
	AND R1,R4,R0 ; FIRST TWO BIT
	
	NOT R1,R1
	ADD R1,R1,#1
	ADD R5,R5,R1 ; R5 MID PART
	JSR EXTRACT
	ADD R0,R0,R5
	ADD R0,R0,R2
	BRnzp SWAPDONE

SWAPDONE
	LD R7,SSAVER7
	LD R2,SSAVER2
	RET
SSAVER7	.BLKW 1
SSAVER2	.BLKW 1
;You must not change the separation line below.
;Write all your code for BITSWAP above this line
;=============================================


;DO NOT CHANGE THE GIVEN CODE BELOW
;=============================================
;;EXTRACT Subroutine (Given Code) 
;;Input: R0 - ASCII value
;;       R1 - n (between 0 and 4) bits to be extracted
;;Output:R0 - value of the n most significant bits of input

EXTRACT
ST R1, SAVER1
ST R2, SAVER2
ST R3, SAVER3
NOT R1, R1 
ADD R1, R1, #9
ETOP
ADD R1, R1, #0 
BRz EBOT
ADD R1, R1, #-1
LD R3, MASK
AND R0, R0, R3
AND R2, R2, #0

EINNER 
ADD R3, R2, R2
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, R0
BRz EINNERBOT
ADD R2, R2, #1
BRnzp EINNER

EINNERBOT
ADD R0, R2, #0
BRnzp ETOP

EBOT
LD R1, SAVER1
LD R2, SAVER2
LD R3, SAVER3
RET
MASK .FILL x00FE
SAVER1 .FILL #0
SAVER2 .FILL #0
SAVER3 .FILL #0

.END	ADD R3,R3,#-1
	AND R2,R2,#0
	ADD R2,R2,R0
SHIFO	ADD R2,R2,R2	;MOST SIG PART
	ADD R3,R3,#-1
