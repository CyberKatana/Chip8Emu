#include "chip8.h"

int main(int argc, char *argv[]) {
	Chip8 Chip;
	Chip.LoadROM(argv[1]);
	return 0;
}
