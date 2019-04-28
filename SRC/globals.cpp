#include "headers.hpp"

//global variables

std::mt19937_64 gRng;

std::uniform_int_distribution<int> gUnif(0, 0xFF);

std::vector<std::string> gRoms;

unsigned gRomsIndex = 0;

Chip8 gChip8;

Display gDisplay;

Keyboard gKeyboard;

sf::RenderWindow gWindow( sf::VideoMode((unsigned)WINDOW_W, (unsigned)WINDOW_H, WINDOW_BITS), WINDOW_TITLE, sf::Style::Titlebar);

sf::Event gEvent;

sf::SoundBuffer gSoundBuffer;

sf::Sound gSound;

sf::Clock gClockTick;

sf::Time gTick;

sf::Clock gClockTimer;

sf::Time gTimer;

//global functions

std::vector<int> ByteToBits(BYTE b)
{
	std::vector<int> v(BYTE_SIZE);

	for (int i = 0; i < BYTE_SIZE; i++)
	{
		v[ (BYTE_SIZE-1) - i ] = (b >> i) % 2;
	};

	return v;
}

BYTE BitsToByte(std::vector<int> v)
{
	BYTE b = 0x00;

	for (int i = 0; i < BYTE_SIZE; i++)
	{
		b += (BYTE)pow(2, (BYTE_SIZE-1) - i) * v[i];
	};

	return b;
}

void Reset()
{
	gChip8.reset();
	gDisplay.reset();
	gKeyboard.reset();
	gWindow.clear(sf::Color(150, 150, 150));
	gWindow.display();
}