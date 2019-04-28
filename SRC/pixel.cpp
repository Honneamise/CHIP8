#include "headers.hpp"

Pixel::Pixel()
{
	shape.setSize(sf::Vector2f(PIXEL_W, PIXEL_H));

	status = OFF; //just to keep the compiler happy
	setStatus(OFF);

	//remove this in future
	//shape.setOutlineThickness(1.0f);
	//shape.setOutlineColor(sf::Color::Black);
}

void Pixel::setPosition(sf::Vector2<float> v)
{
	shape.setPosition(v);
}

void  Pixel::setStatus(int s)
{
	status = s;

	if(status==ON)
	{ 
		setColor(sf::Color(25, 25, 25));
	}
	else 
	{ 
		setColor(sf::Color(50, 100, 150));
	};
}

int  Pixel::getStatus()
{
	return status;
}

void Pixel::setColor(sf::Color c)
{
	shape.setFillColor(c);
}

void Pixel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}