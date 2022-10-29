#!/bin/bash

as/src/rvas ../program.asm program.bin
rm sata0.bin

dd if=/dev/zero of=sata0.bin bs=512 count=2048
dd if=program.bin of=sata0.bin status=none conv=notrunc

