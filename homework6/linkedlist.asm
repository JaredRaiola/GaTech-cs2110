;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Linked List
;;=============================================================
;;Name: Jared Raiola
;;=============================================================

.orig x3000
		AND R0, R0, 0
		AND R1, R1, 0
		AND R2, R2, 0
		AND R3, R3, 0
		AND R4, R4, 0
		LD R0, LL
		ADD R0, R0, 0
		BRz END

		LDI R1, LL ;; LINKED LIST HEAD SET TO R1
		LDR R4, R0, 1 ;; DATA FOR FIRST NODE

		LD R3, DATA
		NOT R3, R3
		ADD R3, R3, 1
		ST R3, DFLIP

WHILE
		LDR R2, R1, 1
		LD R3, DFLIP
		ADD R3, R3, R2
		BRz IF1
		ADD R1, R1, 0
		BRz END
		LDR R1, R1, 0
		ADD R1, R1, 0
		BRp WHILE
		BRnzp END

IF1
		STR R4, R1, 1
		ADD R4, R4, 0
		BRnzp WHILE
		
END
		HALT	





DATA .fill 10
LL .fill x6000
DFLIP .blkw 1
.end

.orig x4000
.fill x4008
.fill 5
.fill x400A
.fill 2
.fill x4002
.fill 9
.fill x0000 
.fill 3
.fill x4004
.fill 10
.fill x4006
.fill 7
.end

.orig x6000
.fill x4000
.fill 6
.end
