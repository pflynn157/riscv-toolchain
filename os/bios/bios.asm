
main:
    ; setup the stack and base pointer
    addi sp, x0, STACK
    addi bp, x0, main

    ; clear display
    ecall x0, x0, 2
    
    addi x15, x0, START

    hlt

STACK: [256]
nop
START:
nop
