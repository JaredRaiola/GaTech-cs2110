;;=======================================
;; CS 2110 - Spring 2019
;; Homework 7
;;=======================================
;; Name: Jared Raiola
;;=======================================

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'decimalStringToInt' label.

.orig x3000

halt

checkTreeEquality
;; Put the code for the CHECKTREEEQUALITY subroutine here
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

		LDR R0, R5, 4 ;; NODE B1
		LDR R1, R5, 5 ;; NODE B2

		ADD R0, R0, 0
		BRz IF1
		ADD R1, R1, 0
		BRz END2
		BR PASS_ON

IF1
		ADD R1, R1, 0
		BRz END 
		BR END2

PASS_ON
		LDR R3, R0, 2 ;; DATA AT B1
		LDR R4, R1, 2 ;; DATA AT B2
		NOT R4, R4
		ADD R4, R4, 1
		ADD R3, R3, R4
		BRnp END2

		;; FIX YOUR LEFT AND RIGHT CALLS

		ADD R6, R6, -2 ;; INITIALIZE SPACE ON STACK
		LDR R2, R0, 0
		STR R2, R6, 0 ;; 
		LDR R4, R1, 0
		STR R4, R6, 1
		JSR checkTreeEquality ;; CALL CHECKTREEEQUALITY
		LDR R3, R6, 0 ;; LOAD RETURN TO R3
		ADD R6, R6, 2 ;; POP RETURN VAL AND PARAM OFF STACK
		ADD R3, R3, 0
		BRz END2

		ADD R6, R6, -2 ;; INITIALIZE SPACE ON STACK
		LDR R0, R0, 1
		STR R0, R6, 0 ;; 
		LDR R1, R1, 1
		STR R1, R6, 1
		JSR checkTreeEquality ;; CALL CHECKTREEEQUALITY
		LDR R3, R6, 0 ;; LOAD RETURN TO R3
		ADD R6, R6, 2 ;; POP RETURN VAL AND PARAM OFF STACK
		ADD R3, R3, 0
		BRz END2
		BR END


END
		AND R2, R2, 0
		ADD R2, R2, 1
		STR R2, R5, 3
		BR STACK_BREAKDOWN

END2
		AND R2, R2, 0
		STR R2, R5, 3
		BR STACK_BREAKDOWN


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


; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
