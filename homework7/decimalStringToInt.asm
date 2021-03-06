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

MULT
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

;; Put the code for the MULT subroutine here
		LDR R0, R5, 4 ;; VALUE OF A LOADED INTO R0
		LDR R1, R5, 5 ;; VALUE OF B LOADED INTO R1

		AND R2, R2, 0 ;; RESULT = 0

WHILE
		ADD R2, R2, R0 ;; RESULT += A
		ADD R1, R1, -1
		BRp WHILE

		STR R2, R5, 3 ;; RESULT IN NOW RESTURN VALUE

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



LENGTH
;; Put the code for the LENGTH subroutine here

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

		LDR R0, R5, 4 ;; LOAD ADDRESS OF STRING INTO R0
		AND R1, R1, 0 ;; LENGTH TO 0

LENGTH_BODY_LOOP
		ADD R2, R0, R1 ;; ADDRESS OF CURR
		LDR R2, R2, 0 ;; VAL OF CURR
		BRz END ;; IF VALUE IS 0, END

		ADD R1, R1, 1 ;; increment length
		BR LENGTH_BODY_LOOP

END
		STR R1, R5, 3 ;; RETURN VALUE IS NOW LENGTH

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



decimalStringToInt
;; Put the code for the DECIMALSTRINGTOINT subroutine here
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

		LDR R0, R5, 4 ;; LOAD DECIMAL PARAM
		AND R1, R1, 0 ;; RET = 0

		ADD R6, R6, -1 ;; INITIALIZE SPACE ON STACK
		STR R0, R6, 0 ;; PUSH DECIMAL TO STACK
		JSR LENGTH ;; CALL LENGTH
		LDR R3, R6, 0 ;; LOAD RETURN TO R3
		ADD R6, R6, 1 ;; POP RETURN VAL AND PARAM OFF STACK

		NOT R2, R3 ;; REVERSE LEN
		ADD R2, R2, 1 ;; REVERSE OF LEN
		AND R4, R4, 0 ;; INITIALIZE I TO 0

FOR
		AND R0, R0, 0
		LDR R0, R5, 4
		ADD R0, R0, R4

		ADD R6, R6, -2 ;; SPACE ON STACK FOR MULT PARAMS
		STR R1, R6, 0
		AND R3, R3, 0
		ADD R3, R3, 10
		STR R3, R6, 1
		JSR MULT
		LDR R1, R6, 0
		ADD R6, R6, 2 ;; POP STACK
		;; RET = MULT RELT, 10

		AND R3, R3, 0
		LDR R3, R0, 0 ;; CURR CHAR
		AND R0, R0, 0
		LD R0, NUM
		ADD R3, R3, R0
		ADD R1, R1, R3


		;; RET = RET + DECIMAL.CHARAT(I) - 48
		ADD R4, R4, 1 ;; INCREMENT I
		ADD R3, R4, R2 ;; CHECK TO SEE IF I IS STILL LESS THAN LEN
		BRn FOR ;; IF I < LEN KEEP LOOPING
		STR R1, R5, 3 ;; RET IS NOW RETURN VALUE


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

NUM .fill -48
; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

.orig x6000
.stringz "10098"
.end
