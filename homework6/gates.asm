;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Gates
;;=============================================================
;;Name: Jared Raiola
;;=============================================================

.orig x3000

		AND R0, R0, 0
    AND R1, R1, 0
    AND R2, R2, 0
    AND R4, R4, 0
		LD R0, A
    LD R1, B
    LD R2, X
    NOT R2, R2 ;; NEGATE X
    ADD R2, R2, 1 ;; 2'S COMPLEMENT
    ADD R0, R0, R2 ;; WILL GIVE A VALUE EITHER ABOVE 0, 0, OR - FOR A-X
    BRn EL2 ;; IF A IS NEGATIVE GO TO CONDITION 2
    BRz EL4 ;; IF A = 0 GO TO CONDITION 4
    ADD R1, R1, R2 ;; B-X
    BRp EL1 ;; IF B IS POSITIVE GO TO CONDITION 1
    BRz EL4 ;; IF B = 0 GO TO CONDITION 4

    AND R0, R0, 0
    AND R1, R1, 0
    LD R0, A
    LD R1, B
    AND R4, R0, R1
    NOT R4, R4
    ST R4, ANSWER
    BRnzp END

EL1
		;; how do you write an nor?
		AND R0, R0, 0
    AND R1, R1, 0
		LD R0, A
    LD R1, B
		NOT R0, R0 ;; FLIP A
		NOT R1, R1 ;; FLIP B
		AND R4, R0, R1
		BRnzp END

EL2 
		;; how do you write an or?
		ADD R1, R1, R2 ;; B-X
		BRp EL3 ;; IF B IS POSITIVE GO TO CONDITION 3
		BRz EL4 ;; IF B IS 0 GO TO CONDITION 4
		AND R0, R0, 0
    AND R1, R1, 0
		LD R0, A
    LD R1, B
    NOT R0, R0 ;; FLIP A
		NOT R1, R1 ;; FLIP B
		AND R4, R0, R1
		NOT R4, R4
		BRnzp END

EL3
		AND R0, R0, 0
    AND R1, R1, 0
		LD R0, A
    LD R1, B
		AND R4, R0, R1
		BRnzp END

EL4
		AND R0, R0, 0
		LD R0, A
		NOT R4, R0
		BRnzp END

END 
		ST R4, ANSWER
		HALT

    ;;YOUR CODE GOES HERE

A   .fill x3030
B   .fill x4040
X   .fill x4040

ANSWER .blkw 1

.end
