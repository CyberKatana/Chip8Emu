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

private:
  std::array<int8_t, 4096> Memory{};
  std::array<uint8_t, 64 * 32> Display;
  std::array<uint8_t, 16> Register;
  uint8_t RegI;
  uint8_t Dt, St;
  uint16_t PC;
  uint8_t SP;
  std::array<uint16_t, 16> Stack;
  std::array<uint8_t, 16> Keypad;
};
