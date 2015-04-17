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

	void Player::update(float time, std::vector<ginger::SceneObject>& objects)
	{
		std::wstring animTitle = L"idle";
		bool collisionTestLeft = false;
		bool collisionTestRight = false;
		bool collisionTestTop = false;
		bool collisionTestBottom = false;
		
		if (!boundingBox.height && !boundingBox.width) {
			sf::Sprite* s = _anim.getCurrentFrame();
			//FIXME: не работает
			boundingBox = s->getTextureRect();
		}
		/* --- collision test --- */
		for (std::vector<ginger::SceneObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			sf::Vector2f	l((float) _x, (float) _y), 
							r((float) (_x + boundingBox.width), (float) (_y + boundingBox.height / 2)),
							t((float) (_x + boundingBox.width /2), (float) _y), 
							b((float) (_x + boundingBox.width / 2), (float) _y + boundingBox.height);


			if (it->collDetect(l)) {
				collisionTestLeft = true;
				_log->add(L"collisionTestLeft = true;");
			}

			if (it->collDetect(r)) {
				collisionTestRight = true;
				_log->add(L"collisionTestRight = true;");
			}

			if (it->collDetect(t)) {
				collisionTestTop = true;
				_log->add(L"collisionTestTop = true;");
			}

			if (it->collDetect(b)) {
				onGround = true;
				collisionTestBottom = true;
				_log->add(L"onGround = true;");
			} else {
				onGround = false;
				_log->add(L"onGround = false;");
			}
		}
		/* --- */


		/* --- keycheck --- */
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (!collisionTestLeft) {
				_x -= time * 0.3;
			}
			_flip = true;
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (!collisionTestRight) {
				_x += time * 0.3;
			}

			_flip = false;
		}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				jump = true;

				animTitle = L"jump";
				_yJumpStart = _y;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
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

			if (jump) {
				if (_y < (_yJumpStart - 100.0f)) {
					_y -= time * 0.3;
				}
				else {
					onGround = false;
					jump = false;
				}
			}
			
			if (!onGround){
				_y += time * 0.1;
				animTitle = L"jump";
			}
		/* --- */



		_anim.set(animTitle.c_str(), _x, _y);
		_anim.flip(_flip);
		_anim.tick(time);
	}
}