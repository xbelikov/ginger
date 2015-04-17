#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <tinyxml.h>

#include "../animation/animation_list.h"
#include "../logger/logger.h"

namespace ginger {
	/*
	class SceneObject : public sf::Drawable
	{
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		sf::Sprite _sprite;
	};
	*/

	class Player : public sf::Drawable, public sf::Transformable
	{
	public:
		Player(ginger::Logger* log);

		void update(float time);
		void checkKey();
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			sf::Sprite* sprite = _anim.getCurrentFrame();
			target.draw(*sprite, states);
		};

		void _loadSpriteData();

		//sf::Texture				_texture;
		//sf::Sprite				_sprite;

		ginger::AnimationList	_anim;

		const char*				_xmlFilePath = "../assets/animations/ginger.xml";
		const char*				_texFilePath = "../assets/ginger.png";

		ginger::Logger*			_log;
		int						_health;
		float					_x = 0.0f;
		float					_y = 0.0f;
		bool					_flip = false;
	};

	class Scene
	{
	public:
		void add();
		int loadFromFile();
	
	private:
		std::wstring _name;
		//std::map<std::wstring, ginger::SceneObject> _sceneObjects;
		//std::map<std::wstring, std::vector<ginger::SceneObject&>> _layers;
	};
}