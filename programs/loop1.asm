addi x2, x0, 512

; I
sw x0, 4(x2)

; N = 10
addi x5, x0, 10

CMP:
    lw x10, 4(x2)
    bge x10, x5, END
LOOP:
    lw x10, 4(x2)
    srli x11, x10, 2
    
    sw x10, 900(x11)
    
    addi x10, x10, 1
    sw x10, 4(x2)
    beq x0, x0, CMP

END:
    addi x30, x0, 10
