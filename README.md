# UBI-Boot for Ingenic JZ47xx SoC

Simple and small bootloader to start a Linux kernel on a UBI partition.

## Compatibility

| Board | Ingenic SoC | Variants                    |
| ----- | ----------- | --------------------------- |
| a320  | 4740        | ili9325, ili9331, ili9338   |
| gcw0  | 4770        | v11 (256/512MB), v20, RG350 |
| rs90  | 4750        | v21, v30                    |

## Building from Source

Use a MIPS32r2 toolchain compatible with your device.

```bash
CONFIG=<board> make -j4
```

Output:

```bash
 CONFIG=gcw0 make -j4
  CC      output/gcw0/fat.o
  CC      output/gcw0/main_v11_ddr2_256mb.o
  CC      output/gcw0/main_v11_ddr2_512mb.o
  CC      output/gcw0/main_v20_mddr_512mb.o
  CC      output/gcw0/main_rg350.o
  LD      output/gcw0/ubiboot-rg350.elf
  LD      output/gcw0/ubiboot-v20_mddr_512mb.elf
  LD      output/gcw0/ubiboot-v11_ddr2_256mb.elf
  LD      output/gcw0/ubiboot-v11_ddr2_512mb.elf
  BIN     output/gcw0/ubiboot-v20_mddr_512mb.bin
  BIN     output/gcw0/ubiboot-rg350.bin
  BIN     output/gcw0/ubiboot-v11_ddr2_256mb.bin
  BIN     output/gcw0/ubiboot-v11_ddr2_512mb.bin
```

## Credits

- Developed By [Paul Cercueil](mailto:paul@crapouillou.net)