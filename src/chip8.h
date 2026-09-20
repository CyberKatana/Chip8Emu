#pragma once

#include <stdint.h>
#include <string>

class Chip8 {
public:
  bool LoadROM(const std::string &Path);

private:
  uint8_t Memory[4096];
  uint8_t Display[64 * 32];
  uint8_t Register[16];
  uint8_t RegI;
  uint8_t Dt, St;
  uint16_t PC;
  uint8_t SP;
  uint16_t Stack[16];
  uint8_t Keypad[16];
};

