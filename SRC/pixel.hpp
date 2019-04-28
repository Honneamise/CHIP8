class Pixel : public sf::Drawable
{
public:
	Pixel();
	void setPosition(sf::Vector2<float> v);
	void setStatus(int s);
	int getStatus();
	void setColor(sf::Color c);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	int status;
	sf::RectangleShape shape;
};