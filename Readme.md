
To create SATA:
dd if=/dev/zero of=sata0.bin bs=512 count=2048

Merge program:
dd if=program1.bin of=sata0.bin status=none conv=notrunc


## Layout
0x0     | < Boot loader >
0x01F4  | < Initial program >
0x0400  | < Stack >

## Function Calls
x29 is the base pointer
x30 is always the return to the previous function
x31 is the stack pointer
