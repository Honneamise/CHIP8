class Keyboard 
{
public:
	Keyboard();
	void reset();
	void handle(sf::Event event);
	bool getKey(BYTE k);
	int getKeyPressed();
	void unsetKeyPressed();

private:
	std::vector<bool> KEYS;
	int KEY_PRESSED;
	
};