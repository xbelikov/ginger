#ifndef GINGER_GAME
#define GINGER_GAME


#include <SFML/Graphics.hpp>
#include "../logger/logger.h"
#include "../scene/scene.h"
#include "../map/map.h"
 
namespace ginger {

	class Game
	{
	public:
		/*
		 * Game init 
		 * loading some configuration and resources
		 */
		int start();

		/*
		 * Free all, close app
		 */
		void stop();

		/*
		 * Main cycle:
		 * Poll events, do some logic, change states, compute statistics, clear frame buffer, draw.
		 */
		void cycle();

		/*
		 * Draw default menu
		 */
		void drawMenu();

		/*
		 * Create default menu
		 */
		void prepareMenu();

	private:
		const wchar_t*							_gameTitle = L"Ginger";

		sf::RenderWindow*						_window = 0;
		sf::View*								_view = 0;

		int										_gWidth = 1024;
		int										_gHeight = 700;

		ginger::Logger							_log;
		const char*								_defaultFontPath = "../assets/fonts/PTS55F.ttf";
		sf::Font								_defaultFont;
		sf::Text								_defaultText;
	};

}

#endif