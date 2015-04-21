#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <tinyxml.h>

#include "../animation/animation_list.h"
#include "../logger/logger.h"

namespace ginger {
	class SceneObject : public sf::Drawable, public sf::Transformable
	{
	public:
		bool collision = true;
		sf::FloatRect boundingBox;

		bool collDetect(sf::FloatRect &objectBox) {
			if (!collision) return false;

			if (boundingBox.intersects(objectBox)) {
				return true;
			}

			return false;
		}

		bool collDetect(sf::Vector2f &objectPoint) {
			if (!collision) return false;

			if (boundingBox.contains(objectPoint)) {
				return true;
			}

			return false;
		}
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			sf::RectangleShape rsh(sf::Vector2f(boundingBox.width, boundingBox.height));
			rsh.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
			rsh.setFillColor(sf::Color(255, 255, 255, 255));
			target.draw(rsh);
		};

		sf::Sprite _sprite;
	};

	class Player : public sf::Drawable, public sf::Transformable
	{
	public:
		Player(ginger::Logger* log);

		void	update(float time, std::vector<ginger::SceneObject>& objects);

		bool	onGround = true;
		int		health = 100;
		bool	jump = false;
		bool	jumpLimit = false;

		sf::IntRect boundingBox;
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			sf::Sprite* sprite = _anim.getCurrentFrame();
			target.draw(*sprite, states);
		};

		void _loadSpriteData();
		ginger::AnimationList	_anim;

		const char*				_xmlFilePath = "../assets/animations/ginger.xml";
		const char*				_texFilePath = "../assets/images/ginger_with_alpha.png";

		ginger::Logger*			_log;
		float					_x = 0.0f;
		float					_y = 0.0f;
		float					_yJumpStart = 0.0f;
		bool					_flip = false;
	};


	class Scene
	{
	public:
		void add();
		int loadFromFile();
	
		std::vector<sf::IntRect> object;
	private:
		std::wstring _name;
		//std::map<std::wstring, ginger::SceneObject> _sceneObjects;
		//std::map<std::wstring, std::vector<ginger::SceneObject&>> _layers;
	};
}