#include "game.h"
 
namespace ginger {
	int Game::start()
	{
		_window = new sf::RenderWindow(sf::VideoMode(_gWidth, _gHeight), _gameTitle);
		_view = new sf::View(sf::Vector2f(400, 300), sf::Vector2f((float) _gWidth, (float) _gHeight));
		_view->move(0, 200);

		_window->setView(*_view);
		
		prepareMenu();

		_log.add(ginger::GAME_START);
		return true;
	}

	void Game::stop()
	{
		delete _window;
		delete _view;

		_log.add(ginger::GAME_STOP);
	}

	void Game::cycle()
	{
		sf::Clock clock;
		float time = 0.0f;
		bool pause = true;
		float lastStateChangeAt = 0.0f;

		ginger::Scene scene(&_log);
		scene.setRenderWindow(_window);
		scene.prepareMap("../assets/levels/test.tmx", "test");

		_window->setVerticalSyncEnabled(true);
		
		_log.add(ginger::GAME_CYCLE_START);

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
				if (!lastStateChangeAt || (lastStateChangeAt > time * 0.6f)) {
					pause = !pause;
					lastStateChangeAt = 1.0f;
				}
				else {
					lastStateChangeAt++;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				sf::Vector2f tempPos;
				scene.player->get(tempPos);

				tempPos.y = 0.0f;
				scene.player->set(tempPos.x, tempPos.y);
			}

			_window->clear();

			/* Pause Menu or Update and render Scene */
			if (!pause) {
				_window->setView(*_view);
				scene.update(time);
				scene.draw();
			}
			else {
				drawMenu();
			}

			_window->display();

			time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
			clock.restart();
		}

		_log.add(ginger::GAME_CYCLE_STOP);
	}

	void Game::drawMenu()
	{
		sf::View viewMenu(sf::Vector2f(400, 300), sf::Vector2f((float) _gWidth, (float) _gHeight));
		viewMenu.move(0, 200);
		_window->setView(viewMenu);
		_window->draw(_defaultText);
	}

	void Game::prepareMenu()
	{
		if (_defaultFont.loadFromFile(_defaultFontPath)) {
			_log.add(ginger::LOADING_FONT_START);
			_log.add(_defaultFontPath);
			_log.add(ginger::LOADING_FONT_STOP);
		}

		_defaultText.setFont(_defaultFont);
		_defaultText.setColor(sf::Color::White);
		_defaultText.setString(L"Пауза");
		_defaultText.setPosition(sf::Vector2f(640 / 2, 480 / 2));
	}
}