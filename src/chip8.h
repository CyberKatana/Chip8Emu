#pragma once

#include <array>
#include <cstdint>
#include <string>

class Chip8 {
public:
  Chip8();
  bool LoadROM(const std::string &Path);

  // Utils
  std::size_t GetRegisterIndex(const std::uint16_t Opcode) const;

  std::uint8_t &GetRegisterRef(const std::uint16_t Opcode);
  // CLS
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#00E0
  void OP_00E0();

  // JP addr
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#1nnn
  void OP_1NNN();

  // LD Vx, byte
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#6xkk
  void OP_6XKK();

  // ADD Vx, byte
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#7xkk
  void OP_7XKK();

  // LD I, addr
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Annn
  void OP_ANNN();

  // DRW Vx, Vy, nibble
  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Dxyn
  void OP_DXYN();

private:
  std::array<std::uint8_t, 4096> Memory{};
  std::array<std::uint8_t, 64 * 32> Display{};
  std::array<std::uint8_t, 16> Register{};
  std::uint8_t RegI = 0;
  std::uint8_t Dt = 0, St = 0;
  std::uint16_t PC = 0;
  std::uint8_t SP = 0;
  std::array<std::uint16_t, 16> Stack{};
  std::array<std::uint8_t, 16> Keypad{};
  std::uint16_t OppCode = 0;
};
