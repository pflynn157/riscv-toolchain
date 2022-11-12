test1:
    addi sp, sp, 4
    sw ra, 0(sp)
    
    add x10, x0, bp
    addi x11, x0, STR1
    addi x12, bp, STR1
    
    addi x2, x0, 1
    addi x1, bp, STR1
    addi x4, x0, 2
    ecall x4, x2, 0
    
    lw ra, 0(sp)
    addi sp, sp, -4
    jalr x0, ra, 0
    
STR1: "Welcome to inner!"
nop
