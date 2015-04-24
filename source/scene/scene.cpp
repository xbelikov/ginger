#include "scene.h"
#include "../utils/utils.h"
 
namespace ginger {
	Scene::Scene(ginger::Logger* log) {
		_log = log;
		player = new ginger::Player(_log);
	}

	Scene::~Scene() {
		delete player;
	}

	int Scene::prepareMap(const char* filePath, const char* mapName) {
		ginger::Map map(_log);
		maps[mapName] = map;

		maps[mapName].loadFromFile(filePath);
		mapObjectsForCollisionTest = maps[mapName].getStaticObjectsForCollisionTest();

		int startPosIndex = maps[mapName].getLevelObjectIndex(LEVEL_OBJECTS::LEVEL_START);
		int endPosIndex = maps[mapName].getLevelObjectIndex(LEVEL_OBJECTS::LEVEL_END);

		if (startPosIndex != GINGER_MAP_OBJECT_NOT_FOUND) {
			maps[mapName].getObject(startPosIndex, curStartPos);
		}

		if (endPosIndex != GINGER_MAP_OBJECT_NOT_FOUND) {
			maps[mapName].getObject(endPosIndex, curEndPos);
		}

		currentMap = mapName;

		return 1;
	}

	void Scene::setRenderWindow(sf::RenderWindow* w) {
		_window = w;
	}

	/* Update state for all objects and player */
	void Scene::update(float time) {
		player->update(time, mapObjectsForCollisionTest);
	}

	void Scene::draw() {
		_window->draw(maps[currentMap]);
		_window->draw(*player);
	}














	Player::Player(ginger::Logger* log)
	{
		_log = log;
		_loadSpriteData();

		_anim.set(L"idle", 0, 0);
	}

	void Player::_loadSpriteData()
	{
		TiXmlDocument spriteData(_xmlFilePath);
		spriteData.LoadFile();

		_log->add(_xmlFilePath);

		TiXmlElement *head;
		head = spriteData.FirstChildElement("sprites");

		/* --- TODO: надо из этих атрибутов настраивать текстуру --- */
		std::string	textureFile = head->Attribute("image");
		std::string	transparentColor = head->Attribute("transparentColor");
		sf::Color tColor;
		//ginger::getColorFromHex(transparentColor, tColor);
		/* --- */

		/* --- FIXME: выше написал --- */
		_anim.loadTexture(_texFilePath);
		_anim.setTransparentColor(tColor);
		_log->add(_texFilePath);
		/* --- */

		TiXmlElement *animEl;
		animEl = head->FirstChildElement("animation");

		while (animEl) {
			std::string					animTitle = animEl->Attribute("title");
			int							speed = atoi(animEl->Attribute("delay"));
			std::vector<sf::IntRect>	frames;
			TiXmlElement*				cut;

			_log->add("Загружаем анимацию:");
			_log->add(animTitle.c_str());
			_log->add("---");

			cut = animEl->FirstChildElement("cut");

			while (cut) {
				int x, y, w, h;

				x = atoi(cut->Attribute("x"));
				y = atoi(cut->Attribute("y"));
				w = atoi(cut->Attribute("w"));
				h = atoi(cut->Attribute("h"));

				frames.push_back(sf::IntRect(x, y, w, h));

				cut = cut->NextSiblingElement("cut");
			}

			std::wstring wtitle;
			ginger::string_to_wstring(animTitle, wtitle);

			_anim.create(wtitle.c_str(), frames, speed);

			animEl = animEl->NextSiblingElement("animation");
		}
	}
/*
	void Player::update(float time, std::vector<ginger::SceneObject>& objects)
	{
		std::wstring animTitle = L"idle";
		checkCollisions(objects);

		// --- keycheck --- /
		keyCheck(time, animTitle);
		// --- /

		updateAnimation(time, animTitle);
	}
*/
	void Player::update(float time, std::vector<ginger::MapObject*>* objects)
	{
		std::wstring animTitle = L"idle";
		checkCollisions(objects);

		/* --- keycheck --- */
		keyCheck(time, animTitle);
		/* --- */

		updateAnimation(time, animTitle);
	}

	void Player::checkCollisions(std::vector<ginger::SceneObject>& objects) {
		collisionTestLeft = false;
		collisionTestRight = false;
		collisionTestTop = false;
		collisionTestBottom = false;
		
		if (!boundingBox.height && !boundingBox.width) {
			sf::Sprite* s = _anim.getCurrentFrame();
			boundingBox = s->getTextureRect();
		}
		
		/* --- collision test --- */
		for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			sf::Vector2f	l((float) _x, (float) _y), 
							r((float) (_x + boundingBox.width), (float) (_y + boundingBox.height / 2)),
							t((float) (_x + boundingBox.width /2), (float) _y), 
							b((float) (_x + boundingBox.width / 2), (float) _y + boundingBox.height);


			if (!collisionTestLeft && it->collDetect(l)) {
				collisionTestLeft = true;
				_log->add("collisionTestLeft = true;");
			}

			if (!collisionTestRight && it->collDetect(r)) {
				collisionTestRight = true;
				_log->add("collisionTestRight = true;");
			}

			if (!collisionTestTop && it->collDetect(t)) {
				collisionTestTop = true;
				_log->add("collisionTestTop = true;");
			}

			if (!collisionTestBottom && it->collDetect(b)) {
				onGround = true;
				jumpLimit = false;
				collisionTestBottom = true;
				//_log->add("onGround = true;");
			}
		}
		/* --- */

		if (!collisionTestBottom) {
			onGround = false;
		}
	}

	void Player::checkCollisions(std::vector<ginger::MapObject*>* objects) {
		collisionTestLeft = false;
		collisionTestRight = false;
		collisionTestTop = false;
		collisionTestBottom = false;
		
		if (!boundingBox.height && !boundingBox.width) {
			sf::Sprite* s = _anim.getCurrentFrame();
			boundingBox = s->getTextureRect();
		}
		
		/* --- collision test --- */
		for (std::vector<ginger::MapObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
			sf::Vector2f	l((float) _x, (float) _y), 
							r((float) (_x + boundingBox.width), (float) (_y + boundingBox.height / 2)),
							t((float) (_x + boundingBox.width /2), (float) _y), 
							b((float) (_x + boundingBox.width / 2), (float) _y + boundingBox.height);

			ginger::MapObject* o = *it;
			
			if (!collisionTestLeft && o->collDetect(l)) {
				collisionTestLeft = true;
				_log->add("collisionTestLeft = true;");
			}

			if (!collisionTestRight && o->collDetect(r)) {
				collisionTestRight = true;
				_log->add("collisionTestRight = true;");
			}

			if (!collisionTestTop && o->collDetect(t)) {
				collisionTestTop = true;
				_log->add("collisionTestTop = true;");
			}

			if (!collisionTestBottom && o->collDetect(b)) {
				onGround = true;
				jumpLimit = false;
				collisionTestBottom = true;
				//_log->add("onGround = true;");
			}
		}
		/* --- */

		if (!collisionTestBottom) {
			onGround = false;
		}
	}

	void Player::keyCheck(float time, std::wstring& animTitle) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (!collisionTestLeft) {
				_x -= time * 0.2f;
			}

			_flip = true;
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (!collisionTestRight) {
				_x += time * 0.2f;
			}

			_flip = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			
			animTitle = L"jump";
			
			if (!jump && onGround) {
				_yJumpStart = _y; 
			}

			if ((_y > (_yJumpStart - 100.0f)) && !jumpLimit) {
				_y -= time * 0.7f;
				jump = true;
				
				onGround = false;
				_log->add("onGround = false;");
			} else {
				jump = false;
				jumpLimit = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			animTitle = L"hit";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (onGround) {
				animTitle = L"run";
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (onGround) {
				animTitle = L"run";
			}
		}
		else if (onGround) {
				animTitle = L"idle";
		}

		if (!onGround){
			_y += time * 0.2f;
			animTitle = L"jump";
		}
	}

	void Player::updateAnimation(float time, std::wstring& animTitle) {
		_anim.set(animTitle.c_str(), _x, _y);
		_anim.flip(_flip);
		_anim.tick(time);
	}
}