//type defines
using BYTE = unsigned char;
using PBYTE = unsigned char *;

using RAW_BYTE = char;
using RAW_PBYTE = char *;

using ADDRESS = unsigned short;
using PADDRESS = unsigned short *;

//standard include
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <random>
#include <filesystem>

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

//program related
#include "const.hpp"
#include "charset.hpp"
#include "instr.hpp"
#include "chip8.hpp"
#include "pixel.hpp"
#include "display.hpp"
#include "keyboard.hpp"
#include "globals.hpp"
