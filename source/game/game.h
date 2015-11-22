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
		 * Инициализируем игру, 
		 * загружаем всё, что необходимо
		 */
		int start();

		/*
		 * Выгружаем всё, закрываем приложение
		 */
		void stop();

		/*
		 * Основной цикл:
		 * Очищаем буфферы, рассчитываем логику, меняем состояния, суммируем статистику, рисуем
		 */
		void cycle();

		void drawMenu();
		void prepareMenu();
	private:
		const wchar_t*							_gameTitle = L"Тест";

		sf::RenderWindow*						_window = 0;
		sf::View*								_view = 0;

		int										_gWidth = 1024;
		int										_gHeight = 700;

		ginger::Logger							_log;
		const char*								_defaultFontPath = "../assets/fonts/PTS55F.ttf";
		sf::Font								_defaultFont;
		sf::Text								_defaultText;
		//std::map<std::wstring, ginger::Scene>	_scenes;
		//ginger::Scene*						_currentScene = 0;
		//void									_drawScene(ginger::Scene& scene);
	};

}

#endif