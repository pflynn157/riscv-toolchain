#!/bin/bash

as/src/rvas program1.asm program1.bin
rm sata0.bin

dd if=/dev/zero of=sata0.bin bs=512 count=2048
dd if=program1.bin of=sata0.bin status=none conv=notrunc

