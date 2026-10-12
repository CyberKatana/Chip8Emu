#pragma once

#include <array>
#include <cstdint>
#include <string>

class Chip8 {
public:
  Chip8();
  bool LoadROM(const std::string &Path);

  // CLS
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#00E0
  void OP_00E0();

  // JP addr
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#1nnn
  void OP_1NNN();

  // LD Vx, byte
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#6xkk
  void OP_6XKK();

private:
  std::array<int8_t, 4096> Memory{};
  std::array<uint8_t, 64 * 32> Display{};
  std::array<uint8_t, 16> Register{};
  uint8_t RegI = 0;
  uint8_t Dt = 0, St = 0;
  uint16_t PC = 0;
  uint8_t SP = 0;
  std::array<uint16_t, 16> Stack{};
  std::array<uint8_t, 16> Keypad{};
  uint16_t OppCode = 0;
};
