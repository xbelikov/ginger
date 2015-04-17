#include "game.h"

namespace ginger {
	int Game::start()
	{
		_window = new sf::RenderWindow(sf::VideoMode(640, 480), _gameTitle);

		_log.add(L"настроились");
		return true;
	}

	void Game::stop()
	{
		delete _window;

		_log.add(L"выгрузились");
	}

	void Game::cycle()
	{
		sf::Clock clock;
		float time = 0.0f;

		_log.add(L"запускаем цикл");
		
		ginger::Player player(&_log);

		_window->setVerticalSyncEnabled(true);

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

			player.update(time);

			_window->clear();
			_window->draw(player);
			_window->display();

			time = clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}

		_log.add(L"выходим из цикла");
	}

	/*
	void Game::_drawScene(ginger::Scene& scene)
	{

	}
	*/
}