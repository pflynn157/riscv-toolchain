
test1:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    ;addi x18, x0, 7
    
    add x14, x0, x1
    add x15, x0, x2
    add x16, x14, x15

    addi x19, x0, 823
    add x1, x0, x19
    jalr ra, x16, 0
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
nop
STR1: "Hello from inner!"
nop

