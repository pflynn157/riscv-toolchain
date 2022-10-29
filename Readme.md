
To create SATA:
dd if=/dev/zero of=sata0.bin bs=512 count=2048

Merge program:
dd if=program1.bin of=sata0.bin status=none conv=notrunc

