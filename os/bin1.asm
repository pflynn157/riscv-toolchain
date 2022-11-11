
test1:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    addi x18, x0, 7
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
nop
STR1: "Hello from inner!"
    
