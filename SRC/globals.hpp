//global variables

extern std::mt19937_64 gRng;

extern std::uniform_int_distribution<int> gUnif;

extern std::vector<std::string> gRoms;

extern unsigned gRomsIndex;

extern Chip8 gChip8;

extern Display gDisplay;

extern Keyboard gKeyboard;

extern sf::RenderWindow gWindow;

extern sf::Event gEvent;

extern sf::SoundBuffer gSoundBuffer;

extern sf::Sound gSound;

extern sf::Clock gClockTick;

extern sf::Time gTick;

extern sf::Clock gClockTimer;

extern sf::Time gTimer;

//global functions

std::vector<int> ByteToBits(BYTE b);

BYTE BitsToByte(std::vector<int> v);

void Reset();

