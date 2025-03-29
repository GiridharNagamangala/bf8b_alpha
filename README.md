# bf8b

**B**aby's **F**irst **8**-**B**it computer. Now 16 bit.

My first Verilog project. I have no idea what I'm doing.

## Details

- 4-stage pipeline with fetch, decode, execute, and writeback
- 8-bit data bus
- 8-bit address bus
- Two general-purpose registers
- Four single-byte instructions

## Instruction set

| Mnemonic | Opcode | Description |
|----------|--------|-------------|
|     | ` x x x x x x x x ` |
| JMP | `0000  x  x  [7:0 ADDRESS]` | Jump to `0b[ADDRESS]` |
| LOD | `0001  DEST  [7:0 ADDRESS]` | Load from memory address `0b[ADDRESS]` into register `DEST` |
| STR | `0010  SRC1  [7:0 ADDRESS]` | Store from register `SRC1` to memory at `0b111[ADDRESS]` |
| ADD | `0011  DEST  SRC1  SRC2   ` | Add `SRC1` and `SRC2` and store in `DEST` |
| ADI | `0100  DEST  SRC1  x  x   ` | Add `SRC1` and content of memory address `0b[ADDRESS]` and store in `DEST` |
| LDI | `0101  DEST  x  x  x  x   ` |
| NDR | `0110  DEST  SRC1  SRC2   ` | Bitwise NAND of `SRC1` and `SRC2` to be stored in `DEST` |
| JEZ | `0111  SRC1  [7:0  ADDESS]` | Conditional jump to `0b[ADDRESS]`, provided `SRC1 == 0` |

For `DEST`/`SRC1`/`SRC2` (Merely rudimentary):
- `a` = 0000
- `b` = 0001
- `c` = 0010 (loop register?)
- `d` = 0011
- `e` = 0100
- `f` = 0101 (flag register?)
- `g` = 0111

## Programming

Edit [the testbench](/8bit_tb.v). That's right.

Execution begins at address `0x00`.
Jumps can only be performed in the first 64 bytes of memory, and only the last 32 bytes of memory are addressable with `LOD` and `STR`.
Also ensure that you specify an adequate number of clock pulses in the simulation for your program.
Dump bytes of `mem` relevant to you to the VCD file with `$dumpvars(0, mem[ADDR])`.

Build with the Makefile. This is written to use Icarus Verilog and GTKWave.

```sh
make clean
make          # Compile with `iverilog`
make 8bit.vcd # Make value change dump (simulation)
make sim      # View waveforms in GTKWave
```
