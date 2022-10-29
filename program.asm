addi x5, x0, 592

addi x10, x0, 72
addi x11, x0, 105
addi x12, x0, 10

sb x11, 1(x5)
sb x12, 2(x5)
sb x10, 0(x5)

sw x0, 0(x5)

addi x20, x0, STR1

addi x21, x0, 10
sb x21, 8(x5)

addi x22, x0, 6
addi x23, x0, 1

LOOP:
add x15, x20, x22
add x16, x5, x22

lb x21, 0(x15)
sb x21, 0(x16)

sub x22, x22, x23
bne x22, x0, LOOP

lb x21, 0(x20)
sb x21, 0(x5)

sw x0, 0(x5)
sw x0, 4(x5)
addi x21, x0, 10
sb x21, 0(x5)

hlt

STR1: "Hello!"

