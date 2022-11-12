
main:
    ; setup the stack and base pointer
    addi sp, x0, STACK
    addi bp, x0, main

    ; clear display
    ecall x0, x0, 2
    
    sw bp, 0(sp)
    addi bp, bp, START
    jalr ra, bp, 0
    lw bp, 0(sp)
    
    addi x11, x0, 5

    hlt

STACK: [256]
nop
START:
nop

