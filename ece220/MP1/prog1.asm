;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here
    AND R6,R6,#0    ; R6 AS COUNTER

NXT_H
    AND R0,R0,#0
    LD R4,ASCIIH
    ADD R0,R4,R6    ; ADD UP R4 AND R6, POINT TO NEXT CHAR
    OUT        ; PRINT THE CHAR
    LD R0,SPACE    
    OUT        ; PRINT SPACE

    LD R4,HIST_ADDR ; LOAD FREQUENCY NEED PRINT OUT INTO R3
    ADD R4,R4,R6    ; POINT TO CURRENT CHAR
    LDR R3,R4,#0    


;TURN BINARY TO HEX

    AND R4,R4,#0    ; USE R4 AS 3 COUNTER
    ADD R4,R4,#3
REC
    AND R2,R2,#0    ; R2 AS 4 COUNTER 
    ADD R2,R2,#4
    AND R1,R1,#0
    AND R0,R0,#0
    AND R5,R5,#0

CHK
    ADD R3,R3,#0
    BRzp ZERO
    ADD R1,R1,#1    ; ADD A BINARY ONE
ZERO
    ADD R3,R3,R3    ; SHIFT R3, NEXT BIT
    ADD R2,R2,#-1
    BRz HEX
    ADD R1,R1,R1    ; SHIFT R1, NEXT BIT
    ADD R2,R2,#0
    BRp CHK

HEX
    ADD R5,R1,#-10  ; CHECK NUM OR CHAR
    BRn NB
CHAR
    LD R0,ASCIIA    ; PRINT CHAR
    ADD R0,R1,R0
    OUT
    ADD R4,R4,#-1
    BRzp REC
    BRn PRIN
NB
    LD R0,ASCII0    ; PRINT NUMBER
    ADD R0,R1,R0    
    OUT
    ADD R4,R4,#-1
    BRzp REC
    
PRIN
    LD R0,NEWLINE
    OUT         ; SHIFT LINE
    ADD R6,R6,#1    ; ADD 1 EACH LOOP
    LD R4,NUM_BINS
    NOT R4,R4
    ADD R4,R4,1	    ; SAVE -27 IN R4
    ADD R4,R4,R6    ; ONCE R6=27, DONE
    BRz DONE
    BRnp NXT_H   


DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
SPACE		.FILL x20
NEWLINE		.FILL x0A
ASCIIH		.FILL x40	; ASCII FOR @
ASCIIA		.FILL x37
ASCII0		.FILL x30
; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
