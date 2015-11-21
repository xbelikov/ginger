#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <tinyxml.h>

#include "../animation/animation_list.h"
#include "../logger/logger.h"
#include "../map/map.h"
#include "../entity/entity.h"

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

	class Player : public ginger::AnimationList //sf::Drawable, public sf::Transformable
	{
	public:
		Player(ginger::Logger* log);

		static const int DIRECTION_RIGHT = 1;
		static const int DIRECTION_LEFT = 2;

		//void	update(float time, std::vector<ginger::SceneObject>& objects);
		void 	update(float time, std::vector<ginger::MapObject*>* objects);
		void 	checkCollisions(std::vector<ginger::SceneObject>& objects);
		void	checkCollisions(std::vector<ginger::MapObject*>* objects);

		void	setAnimation(std::wstring& animTitle);
		void	updateAnimation(float time);

		bool	keyCheck(float time);

		void	move(int direction, float time);
		void	jumping(float time);
		void	hit(float time);
		void	stay(float time);
		void	falling(float time);

		bool	onGround = true;
		int		health = 100;
		bool	jump = false;
		bool	jumpLimit = false;

		sf::IntRect boundingBox;

		bool collisionTestLeft = false;
		bool collisionTestRight = false;
		bool collisionTestTop = false;
		bool collisionTestBottom = false;

	private:
		void _loadSpriteData();
		//ginger::AnimationList	_anim;
		//sf::Sprite			_currentSprite;

		const char*				_xmlFilePath = "../assets/animations/ginger.xml";
		const char*				_texFilePath = "../assets/images/ginger_with_alpha.png";

		ginger::Logger*			_log;
		/*
		float					_x = 0.0f;
		float					_y = 0.0f;
		*/
		float					_yJumpStart = 0.0f;
		bool					_flip = false;
	};

	class Scene
	{
	public:
		Scene(ginger::Logger* log);
		~Scene();
		int prepareMap(const char* filePath, const char* mapName);
		void setRenderWindow(sf::RenderWindow* w);
		void update(float time);
		void draw();

		ginger::Player*						player;
		std::map<std::string, ginger::Map>	maps;
		std::wstring						name;

		std::string							currentMap;
		ginger::MapObject					curStartPos;
		ginger::MapObject					curEndPos;

		std::vector<ginger::MapObject*>*	mapObjectsForCollisionTest = 0;
	private:
		ginger::Logger*						_log = 0;
		sf::RenderWindow*					_window = 0;
	};
}