;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Reverse
;;=============================================================
;;Name: Jared Raiola
;;=============================================================

.orig x3000
		AND R0, R0, 0 ;; X
    AND R1, R1, 0 ;; TEMP
    LD R2, LENGTH
    ADD R2, R2, -1 ;; Y
    LD R3, ARRAY
    AND R4, R4, 0 ;; THIS IS GOING TO BE X-Y

WHILE 
		AND R4, R4, 0 ;; RESETS R4
		LDR R4, R3, 0 ;; LOADS ARRAY AT CURRENT INDEX
		ADD R1, R4, 0 ;; ADDS ARRAY AT X TO TEMP

		AND R3, R3, 0 ;; RESETS R3
		LD R3, ARRAY ;; RESETS ARRAY
		ADD R3, R3, R2 ;; SHIFTS ARRAY TO INDEX Y
		AND R4, R4, 0 ;; RESETS R4
		LDR R4, R3, 0 ;; LOADS ARRAY AT CURRENT INDEX Y
		AND R3, R3, 0 ;; RESETS R3
		LD R3, ARRAY ;; RESETS ARRAY
		ADD R3, R3, R0 ;; MOVES ARRAY TO INDEX X
		STR R4, R3, 0 ;; STORES Y IN REGISTER ARRAY[X]

		AND R3, R3, 0 ;; RESETS R3
		LD R3, ARRAY ;; RESETS ARRAY
		ADD R3, R3, R2 ;; SHIFTS ARRAY TO INDEX Y
		STR R1, R3, 0 ;; STORES TEMP AT INDEX Y

		ADD R2, R2, -1 ;; Y--
		ADD R0, R0, 1 ; X++
		AND R3, R3, 0 ;; RESETS R3
		LD R3, ARRAY ;; RELOADS ARRAY
		ADD R3, R3, R0 ;; MOVES ARRAY TO INDEX X

		AND R4, R4, 0 ;; RESETS R4
		NOT R4, R2 ;; FLIP Y
		ADD R4, R4, 1 ;; 2'S COMP
		ADD R4, R0, R4 ;; X-Y
		BRn WHILE ;; IF X<Y IT'LL BE NEGATIVE BC X-Y
		HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
		.fill 2
		.fill 9
		.fill 7
		.fill 0
		.fill 5
		.fill 3
		.fill 10
.end
