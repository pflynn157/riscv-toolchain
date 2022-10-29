
addi x3, x0, 2

; identify first
ecall x1, x3, 1

; set position to 00
add x4, x0, x0
ecall x4, x3, 3

; Read bytes until the byte is 0xFF
    add x10, x0, x0
    addi x11, x0, 100
    add x12, x0, x0
    add x15, x0, x0
LOOP_CMP:
    beq x10, x11, DONE
LOOP:
    add x4, x10, x12
    ecall x4, x3, 3

    add x5, x0, x10
    ecall x5, x3, 1
    sw x5, 500(x15)
    addi x15, x15, 1

    addi x10, x10, 1
    beq x0, x0, LOOP_CMP
DONE:

; here, jump to that position in memory
addi bp, x0, 500
jal ra, 500

addi x25, x0, 50

hlt

