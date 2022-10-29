
boot:
    addi sp, x0, 1024
    sw ra, 0(sp)
    
    jalr x0, bp, kmain

    lw ra, 0(sp)
    jalr x0, ra, 0
    hlt
    
kmain:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    addi x20, x0, 60
    addi x21, x0, -8
    addi x22, x20, -8
    
    jalr x0, bp, call2
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
call2:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    addi x23, x0, 1
    addi x24, x0, 2
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
