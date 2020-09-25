;;=======================================
;; CS 2110 - Spring 2019
;; Timed Lab 4
;;=======================================
;; Name:
;;=======================================

;; A little reminder from your friendly neighborhood 2110 TA staff:
;; Do not try to run this directly by pressing 'RUN' in Complx.
;; Instead, load it and use 'Debug' -> 'Simulate Subroutine Call'
;; and choose the 'countMult7' label.

.orig x3000

halt ; Do not remove this line – see note above

; mod(a, b)
;
; This looks funky, but it is a subroutine you can call
; like normal. Just be sure to use the LC3 calling convention!
;
; return 1 if a % b == 0 and 0 otherwise
mod
    .fill x1dbf
    .fill x1dbf
    .fill x7f80
    .fill x1dbf
    .fill x7b80
    .fill x1dbf
    .fill x1ba0
    .fill x1dbe
    .fill x7381
    .fill x7580
    .fill x6344
    .fill x6545
    .fill x94bf
    .fill x14a1
    .fill x1242
    .fill x0402
    .fill x0805
    .fill x03fc
    .fill x5260
    .fill x1261
    .fill x7343
    .fill x0e02
    .fill x5260
    .fill x7343
    .fill x6580
    .fill x6381
    .fill x1d63
    .fill x6f42
    .fill x6b41
    .fill xc1c0

; return count of arguments that are multiples of 7
countMult7 ; countMult7(a, ...)
    ; TODO Stack SETUP code here
    ADD R6, R6, -4 ;; MAKE SPACE OR RV, RA, OFP, LV

		STR R7, R6, 2 ;; SAVE OLD RETURN ADDRESS
		STR R5, R6, 1 ;; SAVE OLD FRAME POINTER

		ADD R5, R6, 0 ;; SET CURRENT FRAME POINTER
		ADD R6, R6, -5 ;; PLACE STACK POINTER TO MAKE ROOM FOR ALL REGISTERS

		STR R0, R5, -1 ;; SAVE R0
		STR R1, R5, -2 ;; SAVE R1
		STR R2, R5, -3 ;; SAVE R2
		STR R3, R5, -4 ;; SAVE R3
		STR R4, R5, -5 ;; SAVE R4

    ; TODO your function body code here
    LDR R0, R5, 4
    BRz END 
    ST R0, CHECKPOINT1
    ADD R1, R5, 5
    ST R1, CHECKPOINT2

    AND R2, R2, 0 ;; PUT COUNT INTO R2


WHILE
		LDR R4, R1, 0 ;;GETS VARIABLE 

		ADD R6, R6, -2 ;; INITIALIZE SPACE ON STACK
		STR R4, R6, 0 ;; PUSH DECIMAL TO STACK
		AND R3, R3, 0
		ADD R3, R3, 7
		STR R3, R6, 1
		JSR mod ;; CALL mod
		LDR R3, R6, 0 ;; LOAD RETURN TO R3
		ADD R6, R6, 2 ;; POP RETURN VAL AND PARAM OFF STACK

		ADD R3, R3, -1
		BRz IF1

CONT
		ADD R1, R1, 1
		ADD R0, R0, -1
		BRp WHILE
		BR END2

IF1
		ADD R2, R2, 1
		BR CONT

END
		ST R0, CHECKPOINT1
		STR R0, R5, 3
		BR STACK_BREAKDOWN

END2
		STR R2, R5, 3
    
    ; TODO your TEARDOWN code here
STACK_BREAKDOWN
		LDR R4, R5, -5 ;; RESTORE R4
		LDR R3, R5, -4 ;; RESTORE R3
		LDR R2, R5, -3 ;; RESTORE R2
		LDR R1, R5, -2 ;; RESTORE R1
		LDR R0, R5, -1 ;; RESTORE R0
		
		ADD R6, R5, 0 ;; BRING R6 DOWN TO R5, POP OFF ALL LOCAL VARIABLES OFF THE STACK

		LDR R5, R6, 1 ;; RESTORE OLD FRAME POINTER
		LDR R7, R6, 2 ;; RESTORE OLD RETURN ADDRESS

		ADD R6, R6, 3 ;; R6 NOW POINTS TO RETURN VALUE
		RET

; Do not remove or modify anything below this line
; Needed for subroutine calls and grading
STACK .fill xF000
CHECKPOINT1 .blkw 1 ; Should store n
CHECKPOINT2 .blkw 1 ; Should store address of first variable argument

.end
