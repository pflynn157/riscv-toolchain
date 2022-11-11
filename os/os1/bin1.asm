
test1:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    ; println location
    add x14, x0, x1
    
    ; string location of new base pointer
    addi x15, bp, STR1
    addi x15, x15, 8
    
    sw bp, 4(sp)
    add bp, x0, x2
    add x1, x0, x15
    jalr ra, x14, 0
    lw bp, 4(sp)
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
nop
STR1: "Hello from inner!"
nop

