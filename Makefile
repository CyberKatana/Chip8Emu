CXX			= g++
CXXFLAGS	= -std=c++23 -Wall -Wextra -g

chip8 : src/chip8.h src/chip8.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ src/chip8.cpp src/main.cpp
