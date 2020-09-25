;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 7 - Recursive Reverse Linked List
;;=============================================================
;;Name: Jared Raiola
;;=============================================================

.orig x3000
    ;; Below is a main function that will:
    ;;      - Print the linked list before reversing
    ;;      - Reverse the linked list
    ;;      - Print the reversed linked list
    ;; You shouldn't need to change this main function.

    LDI R1, LL          ; Load first node to R1
    JSR print_ll

    LD R6, STACK        ; Initialize stack pointer
    ADD R6, R6, -1      ; Make room on stack for argument
    STR R1, R6, 0       ; Place first node on stack as argument
    JSR reverse

    LDR R1, R6, 0       ; Load result of reverse
    JSR print_ll
    halt


reverse
;;=============================================================
;; YOUR CODE GOES HERE
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

        LDR R0, R5, 4 ;; HEAD NODE 

        ADD R0, R0, 0
        BRz END 
        LDR R1, R0, 0
        BRz END


        ADD R6, R6, -1 ;; INITIALIZE SPACE ON STACK
        STR R1, R6, 0 ;; PUSH DECIMAL TO STACK
        JSR reverse ;; CALL LENGTH
        LDR R3, R6, 0 ;; LOAD RETURN TO R3
        ADD R6, R6, 1 ;; POP RETURN VAL

        STR R0, R1, 0 ;; head.next.next = head

        AND R4, R4, 0

        STR R4, R0, 0

        STR R3, R5, 3

        BR STACK_BREAKDOWN

END
        STR R0, R5, 3


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

;;=============================================================


; A subroutine that will print a linked list
; given the first node is in R1
print_ll
    ST R0, Save0        ; Save R0
    ST R1, Save1        ; Save R1
    ST R7, Save7        ; Save R7
    LD R0, QUOTES       ; print('"')
    OUT
loop
    LDR R0, R1, 1       ; R0 = curr.val
    OUT                 ; print(curr.val)
    LDR R1, R1, 0       ; R1 = curr.next
    BRz print_done      ; curr.next == null -> done
    BRnzp loop          ;
print_done
    LD R0, QUOTES       ; print('"')
    OUT
    LD R0, NEWLINE      ; print('\n')
    OUT
    LD R0, Save0        ; Restore R0
    LD R1, Save1        ; Restore R1
    LD R7, Save7        ; Restore R7
    RET
Save0       .blkw 1
Save1       .blkw 1
Save7       .blkw 1
QUOTES      .fill '"'
NEWLINE     .fill '\n'

LL .fill x6000
STACK .fill xF000
.end

.orig x4000
.fill x4002         ; x4000
.fill 'a'           ; x4001
.fill x4004         ; x4002
.fill 'b'           ; x4003
.fill x4006         ; x4004
.fill 'c'           ; x4005
.fill x4008         ; x4006
.fill 'd'           ; x4007
.fill x400A         ; x4008
.fill 'e'           ; x4009
.fill x0000         ; x400A
.fill 'f'           ; x400B
.end


.orig x6000
.fill x4000
.fill 6
.end
