#!/bin/bash

as/src/rvas ../os/os1/kernel.asm kernel.bin
as/src/rvas ../os/os1/bin1.asm bin1.bin
rm sata0.bin

cat kernel.bin bin1.bin > complete.bin

dd if=/dev/zero of=sata0.bin bs=512 count=2048
dd if=complete.bin of=sata0.bin status=none conv=notrunc

as/src/rvas ../os/os1/boot.asm boot.bin
sim/sim

