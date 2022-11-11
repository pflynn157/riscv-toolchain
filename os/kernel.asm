
boot:
    lui sp, 1
    slli sp, sp, 1
    sw ra, 0(sp)
    
    jalr ra, bp, kmain

    lw ra, 0(sp)
    jalr x28, ra, 0
    
kmain:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    addi x20, x0, 60
    
    ;addi x1, x0, MSG1
    addi x1, bp, MSG1
    jalr ra, bp, println
    
    ;addi x1, x0, STR1
    addi x1, bp, STR1
    jalr ra, bp, println
    
    addi x1, bp, println
    sw bp, 4(sp)
    add x2, x0, bp
    addi bp, bp, BOOT_END
    jalr ra, x2, BOOT_END
    lw bp, 4(sp)
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
println:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    ; Setup the base pointer and get string length
    ;add x3, bp, x1
    add x3, x0, x1
    sw x3, 4(sp)
    jalr ra, bp, strlen
    add x2, x0, x1
    lw x3, 4(sp)
    
    ; Clear
    ecall x0, x0, 2
    
    ; Run the loop
    add x1, x0, x0
    LOOP_CMP:
        beq x1, x2, DONE
    LOOP:
        add x4, x1, x3
        lb x5, 0(x4)
        ecall x5, x0, 3
        
        addi x1, x1, 1
        beq x0, x0, LOOP_CMP
    DONE:
    
    ; Newline
    addi x5, x0, 10
    ecall x5, x0, 3
    
    ; Print
    ecall x0, x0, 1
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
strlen:
    addi sp, sp, 8
    sw ra, 0(sp)
    
    ;add x1, x1, bp
    addi x2, x0, 0
    lb x3, 0(x1)
    LOOP_CMP1:
        beq x3, x0, DONE1
    LOOP1:
        addi x2, x2, 1
        add x4, x2, x1
        lb x3, 0(x4)
        beq x0, x0, LOOP_CMP1
    DONE1:
    
    add x1, x0, x2
    ;add x23, x0, x1
    ;add x23, x0, x1
    
    lw ra, 0(sp)
    addi sp, sp, -8
    jalr x0, ra, 0
    
STR1: "Hello!"
nop
MSG1: "Welcome to RISC-V OS!"
nop

nop
BOOT_END:
    nop
    nop
