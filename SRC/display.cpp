#include "headers.hpp"

Display::Display() : pixels(DISPLAY_W*DISPLAY_H)
{
	for (int k = 0; k < DISPLAY_W * DISPLAY_H; k++)
	{	
		int i = k % DISPLAY_W;
		int j = k / DISPLAY_W;

		float x = 0.0f;
		float y = 0.0f;

		x = i * PIXEL_W;
		y = j * PIXEL_H;

		sf::Vector2<float> v(x, y);

		pixels[k].setPosition(v);

	};
}

 void Display::reset()
{
	for (int k = 0; k < DISPLAY_W * DISPLAY_H; k++)
	{
		pixels[k].setStatus(OFF);
	}
}

void Display::update(BYTE *buffer)
{
	//for each byte
	for (auto i = 0; i < DISPLAY_W* DISPLAY_H / BYTE_SIZE ; i++)
	{
		for (auto j = 0; j < BYTE_SIZE; j++)
		{
			int src_bit = (buffer[i] >> j ) % 2;

			if (pixels[i*BYTE_SIZE + (BYTE_SIZE - 1)-j].getStatus() != src_bit)
			{
				pixels[i*BYTE_SIZE + (BYTE_SIZE - 1)-j].setStatus(src_bit);
			};
		}
				
	};
}

void Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned k = 0; k < DISPLAY_W * DISPLAY_H; k++)
	{
		target.draw(pixels[k], states);
	};

}
