#include "game.h"

namespace ginger {
	int Game::start()
	{
		_window = new sf::RenderWindow(sf::VideoMode(640, 480), _gameTitle);
		prepareMenu();

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
		bool pause = true;
		float lastStateChangeAt = 0.0f;

		_log.add(L"запускаем цикл");
		
		ginger::Player player(&_log);

		/* --- доавим тестовую землю --- */
		std::vector<ginger::SceneObject> objects;
		ginger::SceneObject ground;
		ground.boundingBox = sf::FloatRect(5.0f, 300.0f, 100.0f, 10.0f);
		ground.collision = true;
		objects.push_back(ground);

		ground.boundingBox = sf::FloatRect(5.0f, 400.0f, 600.0f, 10.0f);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				if (!lastStateChangeAt || (lastStateChangeAt > time * 0.2f)) {
					pause = !pause;
					lastStateChangeAt = 1.0f;
				}
				else {
					lastStateChangeAt++;
				}
			}

			_window->clear();

			if (!pause) {
				for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
					_window->draw(*it);
				}

				player.update(time, objects);
				_window->draw(player);
			}
			else {
				drawMenu();
			}

			_window->display();

			time = clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}

		_log.add(L"выходим из цикла");
	}

	void Game::drawMenu()
	{
		//TODO: подключить freetype
		/*
		sf::Text text(sf::String("asd"), sf::Font());
		text.setPosition(10.0f, 50.0f);
		w->draw(text);
		*/

		_window->draw(_defaultText);
	}

	void Game::prepareMenu()
	{
		if (_defaultFont.loadFromFile(_defaultFontPath)) {
			_log.add(L"{\nЗагрузили шрифты: ");
			_log.add(_defaultFontPath);
			_log.add(L"}");
		}
		_defaultText.setFont(_defaultFont);
		_defaultText.setColor(sf::Color::White);
		_defaultText.setString("Pause");
		_defaultText.setPosition(sf::Vector2f(640 / 2, 480 / 2));
	}

	/*
	void Game::_drawScene(ginger::Scene& scene)
	{

	}
	*/
}