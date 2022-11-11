
; disk drive is port 2
addi x3, x0, 2

; identify first
ecall x1, x3, 1

; set position to 00
add x4, x0, x0
ecall x4, x3, 3

; Read bytes until the byte is 0xFF
    add x10, x0, x0
    addi x11, x0, 550
LOOP_CMP:
    beq x10, x11, DONE
LOOP:
    ecall x5, x3, 1
    sb x5, 496(x10)

    addi x10, x10, 1
    beq x0, x0, LOOP_CMP
DONE:

; here, jump to that position in memory
addi bp, x0, 496
jal ra, 496

addi x25, x0, 50

hlt

addi x26, x0, 50

STR1: "Hi!"


