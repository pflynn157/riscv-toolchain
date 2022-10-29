addi x1, x0, 10
addi x2, x0, 20
addi x3, x0, 30

add x4, x1, x2
add x5, x2, x3

addi x6, x0, 2
srli x7, x6, 1

sw x1, 500(x0)
sw x2, 510(x0)
sw x3, 520(x0)

lw x20, 500(x0)
lw x21, 510(x0)
lw x22, 520(x0)

beq x0, x0, DONE
    addi x30, x0, 10
    addi x20, x0, 10
    addi x21, x0, 10
    addi x22, x0, 10
DONE:
    addi x30, x0, 20

