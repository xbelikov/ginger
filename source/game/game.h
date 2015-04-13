#include <SFML/Graphics.hpp>

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

	private:
		sf::RenderWindow*	_window = 0;
		wchar_t*			_gameTitle = L"Ginger";
	};

}