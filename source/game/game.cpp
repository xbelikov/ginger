#include "game.h"

namespace ginger {
	int Game::start()
	{
		_window = new sf::RenderWindow(sf::VideoMode(200, 200), _gameTitle);

		return true;
	};

	void Game::stop()
	{
		delete _window;
	};

	void Game::cycle()
	{

		while (_window->isOpen())
		{
			sf::Event event;

			while (_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					_window->close();
				}
			}

			_window->clear();
			_window->display();
		}
	};
}