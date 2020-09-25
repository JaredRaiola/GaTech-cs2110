;;===============================
;; Name: Jared Raiola
;;===============================

.orig x3000

    AND R0, R0, 0
    AND R1, R1, 0
    LD R2, LENGTH
    LD R3, ARRAY
    AND R4, R4, 0
FOR 
    ADD R5, R3, R4
    LDR R5, R5, 0
    ADD R0, R0, 0
    BRz EVEN
    NOT R5, R5
    ADD R5, R5, 1
    ADD R1, R1, R5
    AND R0, R0, 0
    ADD R4, R4, 1
    AND R6, R6, 0
    ADD R6, R4, 0
    NOT R6, R6
    ADD R6, R6, 1
    ADD R6, R6, R2
    BRp FOR 
EVEN
    ADD R1, R1, R5
    ADD R0, R0, 1
    ADD R4, R4, 1
    AND R6, R6, 0
    ADD R6, R4, 0
    NOT R6, R6
    ADD R6, R6, 1
    ADD R6, R6, R2
    BRp FOR
END
    ST R1, RESULT
    HALT


ARRAY .fill x6000
LENGTH .fill 7
RESULT .fill 0
.end

.orig x6000
.fill 3 ; +
.fill 5 ; -
.fill 1 ; +
.fill 4 ; -
.fill 6 ; +
.fill 8 ; -
.fill 12; +
.end
