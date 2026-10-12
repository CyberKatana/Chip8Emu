#include "chip8.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
std::uint8_t FontSet[FONTSET_SIZE]{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
  PC = START_ADDRESS;
  // Load fonts
  for (std::size_t i = 0; i < std::size(FontSet); i++) {
    Memory[FONTSET_START_ADDRESS + i] = FontSet[i];
  }
};

bool Chip8::LoadROM(const std::string &Path) {
  std::ifstream File(Path, std::ios::binary | std::ios::ate);
  if (!File.is_open()) {
    std::cerr << "Failed to open ROM: " << Path << "\n";
    return false;
  }

  std::streamsize Size = File.tellg();
  constexpr std::streamsize MaxROMSize = sizeof(Memory) - 0x200;
  if (Size <= 0 || Size > MaxROMSize) {
    std::cerr << "ROM size invalid: " << Size << "bytes\n";
    return false;
  }

  File.seekg(0, std::ios::beg);
  if (!File.read(reinterpret_cast<char *>(&Memory[0x200]), Size)) {
    std::cerr << "Faild to read ROM: " << Path << "\n";
    return false;
  }

  return true;
};

std::size_t Chip8::GetRegisterIndex(const std::uint16_t Opcode) const {
  return (Opcode & 0x0F00u) >> 8u;
};

std::uint8_t &Chip8::GetRegisterRef(const std::uint16_t Opcode) {
  return Register[GetRegisterIndex(Opcode)];
};

void Chip8::OP_00E0() { Display.fill(0); };

void Chip8::OP_1NNN() { PC = OppCode & 0x0FFFu; };

void Chip8::OP_6XKK() {
  auto RegesterIdx = (OppCode & 0x0F00u) >> 8u;
  auto Val = OppCode & 0x00FFu;
  Register[RegesterIdx] = Val;
};

void Chip8::OP_7XKK() { GetRegisterRef(OppCode) = OppCode & 0x00FFu; }

void Chip8::OP_ANNN() { RegI = OppCode & 0x0FFFu; };

void Chip8::OP_DXYN() {
  Register[0xF] = 0;

  std::uint8_t Xpos = ((OppCode & 0x0F00u) >> 8u) % 64;
  std::uint8_t Ypos = ((OppCode & 0x00F0u) >> 4u) % 32;
  std::uint8_t SpriteHeight = OppCode & 0x000Fu;

  for (std::uint8_t Row = 0; Row < SpriteHeight; Row++) {
    std::uint8_t SpriteLine = Memory[RegI + Row];
    for (std::uint8_t Column = 0; Column < 8; Column++) {
      std::uint8_t SpritePixel = SpriteLine & (0b10000000 >> Column);
      std::uint8_t &DisplayPixel = Display[(Ypos + Row) * 64 + (Xpos + Column)];

      if (SpritePixel) {
        if (DisplayPixel == 0xFF) {
          // Collision detected
          Register[0xF] = 1;
        }

        DisplayPixel ^= 0xFF;
      }
    }
  }
};
