#include "headers.hpp"

#ifdef _WIN32
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int main()
#endif
{
	//load sound
	if (!gSoundBuffer.loadFromFile((std::string)RES_FOLDER + (std::string)SOUND_FILE))
	{
		std::cout << "Unable to load sound file from RES folder" << std::endl;
		return EXIT_FAILURE;
	};
	gSound.setBuffer(gSoundBuffer);
	
	//load all the file names in the roms folder
	try
	{
		for (const auto & entry : std::filesystem::directory_iterator(ROMS_FOLDER))
		{
			std::string s = entry.path().string();
			gRoms.push_back(s);
		}
	}
	catch (...) 
	{
		std::cout << "ROMS folder not found or empty" << std::endl;
		return EXIT_FAILURE;
	};

	//prepare the window	
	gWindow.setKeyRepeatEnabled(false);
	gWindow.clear(sf::Color(150, 150, 150));
	gWindow.display();

	//prepare the clock
	gClockTick.restart();
	gTick = sf::Time::Zero;

	gClockTimer.restart();
	gTimer = sf::Time::Zero;

	//load the game
	gChip8.load(gRoms[gRomsIndex]);

	//main loop
	while (gWindow.isOpen())
	{
		//call emulator if elepsed enought time
		gTick += gClockTick.restart();
		if (gTick.asMicroseconds() > CPU_FREQ)
		{
			gTick = sf::Time::Zero;

			Instr ins = gChip8.emulate();
			//std::cout << ins << std::endl;//

			//update the display if needed
			if (ins.type.compare(DISPLAY) == 0)
			{
				//update the pixels
				gDisplay.update(gChip8.getDisplayBuffer());

				//update the display window
				gWindow.clear(sf::Color(150, 150, 150));
				gWindow.draw(gDisplay);
				gWindow.display();

			};
		}
		
		//handle events
		while (gWindow.pollEvent(gEvent))
		{
			//handle keyboard
			if (gEvent.type == sf::Event::KeyPressed || gEvent.type == sf::Event::KeyReleased)
			{
				gKeyboard.handle(gEvent);
			};

			//ESC close
			if (gEvent.type == sf::Event::KeyPressed && gEvent.key.code == sf::Keyboard::Escape)
			{
				gWindow.close();
			};

			//F1 reset
			if (gEvent.type == sf::Event::KeyPressed && gEvent.key.code == sf::Keyboard::F1)
			{
				Reset();
				gChip8.load(gRoms[gRomsIndex]);
			}

			//F2 next rom
			if (gEvent.type == sf::Event::KeyPressed && gEvent.key.code == sf::Keyboard::F2)
			{				
		
				gRomsIndex++;
				if (gRomsIndex >= gRoms.size()) { gRomsIndex = 0; };

				Reset();
				gChip8.load(gRoms[gRomsIndex]);
			}
		}

		//adjust the timers
		gTimer += gClockTimer.restart();
		if (gTimer.asMicroseconds() > TIME_FREQ)
		{
			gTimer = sf::Time::Zero;

			if (gChip8.getDT() > 0) { gChip8.decDT(); };

			if (gChip8.getST() > 0)
			{
				gChip8.decST();
				if (gSound.getStatus() == sf::SoundSource::Stopped) { gSound.play(); };		
			};

		}

	}

	return EXIT_SUCCESS;
}