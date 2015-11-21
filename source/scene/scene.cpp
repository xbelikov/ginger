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

		//_anim.setAnimByTitle(L"idle");
		setAnimByTitle(L"idle");
	}

	void Player::_loadSpriteData()
	{
		TiXmlDocument spriteData(_xmlFilePath);
		spriteData.LoadFile();

		_log->add(_xmlFilePath);

		TiXmlElement *head;
		head = spriteData.FirstChildElement("sprites");

		/* --- TODO: ���� �� ���� ��������� ����������� �������� --- */
		std::string	textureFile = head->Attribute("image");
		std::string	transparentColor = head->Attribute("transparentColor");
		sf::Color tColor;
		//ginger::getColorFromHex(transparentColor, tColor);
		/* --- */

		/* --- FIXME: ���� ������� --- */
		//_anim.loadTexture(_texFilePath);
		//_anim.setTransparentColor(tColor);

		loadTexture(_texFilePath);
		setTransparentColor(tColor);
		_log->add(_texFilePath);
		/* --- */

		TiXmlElement *animEl;
		animEl = head->FirstChildElement("animation");

		while (animEl) {
			std::string					animTitle = animEl->Attribute("title");
			int							speed = atoi(animEl->Attribute("delay"));
			std::vector<sf::IntRect>	frames;
			TiXmlElement*				cut;

			_log->add("��������� ��������:");
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

			//_anim.create(wtitle.c_str(), frames, speed);
			createAnim(wtitle.c_str(), frames, speed);

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
		//std::wstring animTitle = L"idle";
		checkCollisions(objects);
		
		if (!onGround) {
			falling(time);
		}

		/* --- keycheck --- */
		if (!keyCheck(time)) {
			if (onGround) {
				stay(time);
			}
		}
		/* --- */

		sf::Vector2f currentPos = getPosition();
		updateAnim(time, currentPos.x, currentPos.y, _flip);
	}

	void Player::checkCollisions(std::vector<ginger::SceneObject>& objects) {
		collisionTestLeft = false;
		collisionTestRight = false;
		collisionTestTop = false;
		collisionTestBottom = false;
		
		if (!boundingBox.height && !boundingBox.width) {
			//sf::Sprite* s = _anim.getCurrentFrame();
			//sf::IntRect r = _anim.getCurrentFrame();
			boundingBox = getCurrentFrame(); // s->getTextureRect();
		}
		
		/* --- collision test --- */
		sf::Vector2f currentPos = getPosition();
		for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			sf::Vector2f	l((float) currentPos.x, (float) currentPos.y),
							r((float) (currentPos.x + boundingBox.width), (float)(currentPos.y + boundingBox.height / 2)),
							t((float) (currentPos.x + boundingBox.width / 2), (float)currentPos.y),
							b((float) (currentPos.x + boundingBox.width / 2), (float)currentPos.y + boundingBox.height);


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
			//sf::Sprite* s = _anim.getCurrentFrame();
			//sf::IntRect r = _anim.getCurrentFrame();
			boundingBox = getCurrentFrame(); //s->getTextureRect();
		}
		
		sf::Vector2f currentPos = getPosition();
		/* --- collision test --- */
		for (std::vector<ginger::MapObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
			sf::Vector2f	l((float)currentPos.x, (float)currentPos.y),
				r((float)(currentPos.x + boundingBox.width), (float)(currentPos.y + boundingBox.height / 2)),
				t((float)(currentPos.x + boundingBox.width / 2), (float)currentPos.y),
				b((float)(currentPos.x + boundingBox.width / 2), (float)currentPos.y + boundingBox.height);

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

	void Player::move(int direction, float time)
	{
		sf::Vector2f currentPos = getPosition();
		float _x = currentPos.x;
		float _y = currentPos.y;

		if (direction == DIRECTION_LEFT) {
			_x -= time * 0.2f;
			_flip = true;
		}
		else if (direction == DIRECTION_RIGHT) {
			_x += time * 0.2f;
			_flip = false;
		}

		if (onGround) {
			setAnimation(std::wstring(L"run"));
		}

		setPosition(sf::Vector2f(_x, _y));
	}

	void Player::jumping(float time)
	{
		sf::Vector2f currentPos = getPosition();
		float _x = currentPos.x;
		float _y = currentPos.y;

		setAnimation(std::wstring(L"jump"));

		if (!jump && onGround) {
			_yJumpStart = _y;
		}

		if ((_y > (_yJumpStart - 100.0f)) && !jumpLimit) {
			_y -= time * 0.7f;
			jump = true;

			onGround = false;
			_log->add("onGround = false;");
		}
		else {
			jump = false;
			jumpLimit = true;
		}

		setPosition(sf::Vector2f(_x, _y));
	}

	void Player::hit(float time)
	{
		setAnimation(std::wstring(L"hit"));
	}

	void Player::stay(float time)
	{
		setAnimation(std::wstring(L"idle"));
	}

	void Player::falling(float time)
	{
		sf::Vector2f currentPos = getPosition();
		float _x = currentPos.x;
		float _y = currentPos.y;

		_y += time * 0.2f;

		setPosition(sf::Vector2f(_x, _y));
		setAnimation(std::wstring(L"jump"));
	}

	bool Player::keyCheck(float time) {
		bool inMove = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			move(DIRECTION_LEFT, time);
			inMove = true;
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			move(DIRECTION_RIGHT, time);
			inMove = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			jumping(time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			hit(time);
		}
		else if (!inMove) {
			return false;
		}

		return true;
	}

	void Player::setAnimation(std::wstring& animTitle)
	{
		//_anim.setAnimByTitle(animTitle.c_str());
		setAnimByTitle(animTitle.c_str());
	}
}