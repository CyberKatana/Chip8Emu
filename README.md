# CHIP-8

A CHIP-8 emulator/interpreter.

## Overview

CHIP-8 is an interpreted programming language from the 1970s, commonly implemented
as a virtual machine to run classic games (Pong, Tetris, Space Invaders, etc.).
This project aims to implement a CHIP-8 interpreter.

## Specs

- **Memory**: 4096 bytes (4KB). Programs load starting at `0x200`.
- **Registers**: 16 general-purpose 8-bit registers (`V0`-`VF`), one 16-bit
  index register (`I`), a 16-bit program counter (`PC`), and an 8-bit stack
  pointer (`SP`).
- **Stack**: 16 levels, used for subroutine call/return.
- **Timers**: Delay timer and sound timer, both 8-bit, counting down at 60Hz.
- **Display**: 64x32 pixels, monochrome, XOR-based sprite drawing.
- **Input**: 16-key hexadecimal keypad (`0`-`F`).
- **Opcodes**: 35 instructions, all 2 bytes, big-endian.

## Planned structure

```
chip-8/
├── src/
│   ├── chip8.*      # Core interpreter: memory, registers, opcode execution
│   ├── display.*     # Framebuffer / rendering backend
│   ├── input.*        # Keypad handling
│   └── main.*          # Entry point: load ROM, run emulation loop
├── roms/                # Test/demo ROMs
└── README.md
```

## Roadmap

- [ ] Memory, registers, and program counter setup
- [ ] ROM loading
- [ ] Fetch-decode-execute cycle
- [ ] Opcode implementation (35 instructions)
- [ ] Delay and sound timers (60Hz)
- [ ] Display output (64x32, sprite XOR drawing)
- [ ] Keypad input
- [ ] Sound (beep on sound timer)
