#include "headers.hpp"

Keyboard::Keyboard()
{
	KEYS.resize(NUM_KEYS);
	KEY_PRESSED = -1;
}

void Keyboard::reset()
{
	KEYS.resize(0);
	KEYS.resize(NUM_KEYS);
	KEY_PRESSED = -1;
}

void Keyboard::handle(sf::Event event)
{
	KEY_PRESSED = -1;
	bool flag = false;
	if (event.type == sf::Event::KeyPressed) { flag = true; };
	
	/*
	1	2	3	4		=>		1	2	3	C
	Q	W	E	R				4	5	6	D
	A	S	D	F				7	8	9	E
	Z	X	C	V				A	0	B	F

	*/

	switch (event.key.code)
	{
	case sf::Keyboard::Num1:
		KEYS[0x01] = flag;
		if (flag) { KEY_PRESSED = 0x01; }
		break;

	case sf::Keyboard::Num2:
		KEYS[0x02] = flag;
		if (flag) { KEY_PRESSED = 0x02; }
		break;

	case sf::Keyboard::Num3:
		KEYS[0x03] = flag;
		if (flag) { KEY_PRESSED = 0x03; }
		break;

	case sf::Keyboard::Num4:
		KEYS[0x0C] = flag;
		if (flag) { KEY_PRESSED = 0x0C; }
		break;

	case sf::Keyboard::Q:
		KEYS[0x04] = flag;
		if (flag) { KEY_PRESSED = 0x04; }
		break;

	case sf::Keyboard::W:
		KEYS[0x05] = flag;
		if (flag) { KEY_PRESSED = 0x05; }
		break;

	case sf::Keyboard::E:
		KEYS[0x06] = flag;
		if (flag) { KEY_PRESSED = 0x06; }
		break;

	case sf::Keyboard::R:
		KEYS[0x0D] = flag;
		if (flag) { KEY_PRESSED = 0x0D; }
		break;

	case sf::Keyboard::A:
		KEYS[0x07] = flag;
		if (flag) { KEY_PRESSED = 0x07; }
		break;

	case sf::Keyboard::S:
		KEYS[0x08] = flag;
		if (flag) { KEY_PRESSED = 0x08; }
		break;

	case sf::Keyboard::D:
		KEYS[0x09] = flag;
		if (flag) { KEY_PRESSED = 0x09; }
		break;

	case sf::Keyboard::F:
		KEYS[0x0E] = flag;
		if (flag) { KEY_PRESSED = 0x0E; }
		break;

	case sf::Keyboard::Z:
		KEYS[0x0A] = flag;
		if (flag) { KEY_PRESSED = 0x0A; }
		break;

	case sf::Keyboard::X:
		KEYS[0x00] = flag;
		if (flag) { KEY_PRESSED = 0x00; }
		break;

	case sf::Keyboard::C:
		KEYS[0x0B] = flag;
		if (flag) { KEY_PRESSED = 0x0B; }
		break;

	case sf::Keyboard::V:
		KEYS[0x0F] = flag;
		if (flag) { KEY_PRESSED = 0x0F; }
		break;

	default:
		break;
	}

}
bool Keyboard::getKey(BYTE k)
{
	return KEYS[k];
}

int Keyboard::getKeyPressed()
{
	return KEY_PRESSED;
}

void Keyboard::unsetKeyPressed()
{
	KEY_PRESSED = -1;
}