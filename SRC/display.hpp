class Display : public sf::Drawable
{
public:
	Display();
	void reset();
	void update(BYTE *buffer);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Pixel> pixels;
};