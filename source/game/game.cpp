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
		
		ginger::Player	player(&_log);

		/* --- доавим тестовую землю --- */
		std::vector<ginger::SceneObject> objects;
		ginger::SceneObject ground;
		ground.boundingBox = sf::FloatRect(5.0f, 300.0f, 100.0f, 10.0f);
		ground.collision = true;

		objects.push_back(ground);

		/* --- */
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

			player.update(time, objects);

			_window->clear();
			
			_window->draw(player);

			for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
				_window->draw(*it);
			}

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