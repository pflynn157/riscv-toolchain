
main:
    ; setup the stack and base pointer
    addi sp, x0, STACK
    addi bp, x0, main

    ; clear display
    ecall x0, x0, 2
    
    addi bp, x0, START
    
    jalr ra, bp, 0

    hlt

STACK: [256]
nop
START:
nop

test1:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    addi x10, x0, 20
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
