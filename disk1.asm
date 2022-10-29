
addi x3, x0, 2

; identify first
ecall x1, x3, 1

; set position to 100
addi x4, x0, 100
ecall x4, x3, 3

; Now write bytes to the disk
    add x10, x0, x0
    addi x11, x0, 5
    addi x12, x0, 100
LOOP_CMP:
    beq x10, x11, DONE
LOOP:
    add x4, x10, x12
    ecall x4, x3, 3

    add x5, x0, x10
    ecall x5, x3, 2

    addi x10, x10, 1
    beq x0, x0, LOOP_CMP
DONE:

; Now read the bytes back and add them together
    add x4, x0, x12
    ecall x4, x3, 3

    add x13, x0, x0
    add x10, x0, x0
LOOP_CMP2:
    beq x10, x11, DONE2
LOOP2:
    add x4, x10, x12
    ecall x4, x3, 3

    ecall x5, x3, 1
    add x13, x13, x5

    addi x10, x10, 1
    beq x0, x0, LOOP_CMP2
DONE2:

hlt

