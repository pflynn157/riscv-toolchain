
main:
    ; setup the stack and base pointer
    addi sp, x0, STACK
    addi bp, x0, main

    ; clear display
    ecall x0, x0, 2
    
    ; test syscall
    ; set the system call
    addi x1, x0, 1
    addi x4, bp, INT1
    ecall x4, x1, 1
    
    addi x1, x0, 1
    addi x4, bp, println
    ecall x4, x1, 2
    
    ; call the system call
    addi x4, x0, 1
    addi x1, x0, 1
    ecall x4, x1, 0
    
    addi x2, x0, 1
    addi x1, bp, STR1
    addi x4, x0, 2
    ecall x4, x2, 0
    add x15, x0, x1
    
    ; Jump out of the initial bios
    sw bp, 0(sp)
    addi bp, bp, START
    jalr ra, bp, 0
    lw bp, 0(sp)
    
    addi x11, x0, 5

    hlt

STACK: [256]
nop

INTERRUPTS:
nop
INT1:
    addi x24, x0, 20
    jalr x0, ra, 0
    
println:
    ; Clear
    ecall x0, x0, 2
    
    ; Run the loop
    add x2, x0, x0
    lb x3, 0(x1)
    add x5, x0, x3
    ecall x5, x0, 3
    LOOP_CMP:
        beq x3, x0, DONE
    LOOP:
        addi x2, x2, 1
        add x4, x2, x1
        lb x3, 0(x4)
        add x5, x0, x3
        ecall x5, x0, 3
        beq x0, x0, LOOP_CMP
    DONE:
    
    ; Newline
    addi x5, x0, 10
    ecall x5, x0, 3
    
    ; Print
    ecall x0, x0, 1
    
    jalr x0, ra, 0
    nop
    
nop

STR1: "Welcome to RISC-V"
nop

START:

