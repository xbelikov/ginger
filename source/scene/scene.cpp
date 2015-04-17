#include "scene.h"
#include "../utils/utils.h"

namespace ginger {
	void Scene::add()
	{

	}

	int Scene::loadFromFile()
	{
		return 0;
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
		/* --- */

		/* --- FIXME: выше написал --- */
		_anim.loadTexture(_texFilePath);
		_log->add(_texFilePath);
		/* --- */

		TiXmlElement *animEl;
		animEl = head->FirstChildElement("animation");

		while (animEl) {
			std::string					animTitle = animEl->Attribute("title");
			int							speed = atoi(animEl->Attribute("delay"));
			std::vector<sf::IntRect>	frames;
			TiXmlElement*				cut;

			_log->add(L"Загружаем анимацию:");
			_log->add(animTitle.c_str());
			_log->add(L"---");

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

	void Player::update(float time)
	{
		std::wstring animTitle = L"idle";

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_x -= time * 0.3;
			animTitle = L"run";
			_flip = true;

		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_x += time * 0.3;
			animTitle = L"run";
			_flip = false;

		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			animTitle = L"hit";
		} else {
			animTitle = L"idle";
		}

		_anim.set(animTitle.c_str(), _x, _y);
		_anim.flip(_flip);
		_anim.tick(time);
	}
}