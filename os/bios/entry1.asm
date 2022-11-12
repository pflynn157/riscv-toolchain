test1:
    addi sp, sp, 4
    sw ra, 0(sp)
    
    addi x10, x0, 20
    
    lw ra, 0(sp)
    addi sp, sp, -4
    jalr x0, ra, 0
