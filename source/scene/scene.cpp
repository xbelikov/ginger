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

		/* --- TODO: ���� �� ���� ��������� ����������� �������� --- */
		std::string	textureFile = head->Attribute("image");
		std::string	transparentColor = head->Attribute("transparentColor");
		sf::Color tColor;
		//ginger::getColorFromHex(transparentColor, tColor);
		/* --- */

		/* --- FIXME: ���� ������� --- */
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

			_log->add(L"��������� ��������:");
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
				_log->add(L"collisionTestLeft = true;");
			}

			if (!collisionTestRight && it->collDetect(r)) {
				collisionTestRight = true;
				_log->add(L"collisionTestRight = true;");
			}

			if (!collisionTestTop && it->collDetect(t)) {
				collisionTestTop = true;
				_log->add(L"collisionTestTop = true;");
			}

			if (!collisionTestBottom && it->collDetect(b)) {
				onGround = true;
				jumpLimit = false;
				collisionTestBottom = true;
				//_log->add(L"onGround = true;");
			}
		}
		/* --- */

		if (!collisionTestBottom) {
			onGround = false;
		}


		/* --- keycheck --- */
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (!collisionTestLeft) {
				_x -= time * 0.2;
			}

			_flip = true;
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (!collisionTestRight) {
				_x += time * 0.2;
			}

			_flip = false;
		}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				
				animTitle = L"jump";
				
				if (!jump && onGround) {
					_yJumpStart = _y; 
				}

				if ((_y > (_yJumpStart - 100.0f)) && !jumpLimit) {
					_y -= time * 0.7;
					jump = true;
					
					onGround = false;
					_log->add(L"onGround = false;");
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
				_y += time * 0.2;
				animTitle = L"jump";
			}
		/* --- */



		_anim.set(animTitle.c_str(), _x, _y);
		_anim.flip(_flip);
		_anim.tick(time);
	}
}