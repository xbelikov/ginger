#include "game.h"
 
namespace ginger {
	int Game::start()
	{
		_window = new sf::RenderWindow(sf::VideoMode(_gWidth, _gHeight), _gameTitle);
		_view = new sf::View(sf::Vector2f(400, 300), sf::Vector2f(_gWidth, _gHeight));
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
		std::vector<ginger::MapObject*>* objects = 0;
		ginger::MapObject* startPos = 0;
		ginger::MapObject* endPos = 0;

		ginger::Map map(&_log);
		
		map.loadFromFile("../assets/levels/test.tmx");
		objects = map.getStaticObjectsForCollisionTest();
		startPos = map.getLevelObject(LEVEL_OBJECTS::LEVEL_START);
		endPos = map.getLevelObject(LEVEL_OBJECTS::LEVEL_END);
		
		ginger::Player player(&_log);

		/* --- доавим тестовую землю --- 
		std::vector<ginger::SceneObject> objects;
		ginger::SceneObject ground;
		ground.boundingBox = sf::FloatRect(5.0f, 300.0f, 100.0f, 10.0f);
		ground.collision = true;
		objects.push_back(ground);

		ground.boundingBox = sf::FloatRect(5.0f, 400.0f, 600.0f, 10.0f);
		objects.push_back(ground);
		/* --- */

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
				_window->setView(*_view);
				_window->draw(map);
				/*
				for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
					_window->draw(*it);
				}
				*/
				player.update(time, objects);
				_window->draw(player);
			}
			else {
				drawMenu();
			}

			_window->display();

			time = (float) clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}

		_log.add(ginger::GAME_CYCLE_STOP);
	}

	void Game::drawMenu()
	{
		sf::View viewMenu(sf::Vector2f(400, 300), sf::Vector2f(_gWidth, _gHeight));
		viewMenu.move(0, 100);
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

	/*
	void Game::_drawScene(ginger::Scene& scene)
	{

	}
	*/
}