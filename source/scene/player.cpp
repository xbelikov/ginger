#include "player.h"
#include "../utils/utils.h"

namespace ginger {
	Player::Player(ginger::Logger* log) : Physical(log)
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

		/* --- TODO: надо из этих атрибутов настраивать текстуру --- */
		std::string	textureFile = head->Attribute("image");
		std::string	transparentColor = head->Attribute("transparentColor");
		sf::Color tColor;
		//ginger::getColorFromHex(transparentColor, tColor);
		/* --- */

		/* --- FIXME: выше написал --- */
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
		if (!boundingBox.height && !boundingBox.width) {
			boundingBox = getCurrentFrame();
		}

		sf::Vector2f currentPos;
		get(currentPos);

		checkCollisions(objects, boundingBox, currentPos);

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
		updateAnim(time, currentPos.x, currentPos.y, _flip);
	}

	void Player::move(int direction, float time)
	{
		sf::Vector2f currentPos;
		get(currentPos); //getPosition();

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

		set(_x, _y);
	}

	void Player::jumping(float time)
	{
		sf::Vector2f currentPos;
		get(currentPos); //getPosition();

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

		set(_x, _y);
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
		sf::Vector2f currentPos;
		get(currentPos); //getPosition();

		float _x = currentPos.x;
		float _y = currentPos.y;

		_y += time * 0.2f;

		set(_x, _y);
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