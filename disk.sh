#!/bin/bash

as/src/rvas ../os/kernel.asm kernel.bin
as/src/rvas ../os/bin1.asm bin1.bin
rm sata0.bin

cat kernel.bin bin1.bin > complete.bin

dd if=/dev/zero of=sata0.bin bs=512 count=2048
dd if=complete.bin of=sata0.bin status=none conv=notrunc

