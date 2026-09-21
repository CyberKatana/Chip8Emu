#include "chip8.h"
#include <iostream>
#include <ios>
#include <fstream>

bool Chip8::LoadROM(const std::string& Path)
{
	std::ifstream File(Path, std::ios::binary | std::ios::ate);
	if (!File.is_open())
	{
		std::cerr << "Failed to open ROM: " << Path << "\n";
		return false;
	}

	std::streamsize Size = File.tellg();
	constexpr std::streamsize MaxROMSize = sizeof(Memory) - 0x200;
	if (Size <= 0 || Size > MaxROMSize)
	{
		std::cerr << "ROM size invalid: " << Size << "bytes\n";
		return false;
	}

	File.seekg(0, std::ios::beg);
	if (!File.read(reinterpret_cast<char*>(&Memory[0x200]),Size))
	{
		std::cerr << "Faild to read ROM: " << Path << "\n";
		return false;
	}

	return true;
};
