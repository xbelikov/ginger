#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "../logger/logger.h"
#include <SFML/Graphics.hpp>

namespace ginger {
	struct MapObject;
	class Physical
	{
	public:
		Physical(ginger::Logger* log) { _log = log; };
		Physical() {};

		bool collDetect(sf::FloatRect &objectBox) {};
		bool collDetect(sf::Vector2f &objectPoint) {};

		void checkCollisions(std::vector<MapObject*>* objects, sf::IntRect &boundingBox, sf::Vector2f &currentPos);

		bool collisionTestLeft = false;
		bool collisionTestRight = false;
		bool collisionTestTop = false;
		bool collisionTestBottom = false;
		bool onGround = false;
		bool jumpLimit = false;
	
	protected:
		void getCollisionTargets(sf::Vector2f &cp, sf::IntRect &bb, sf::Vector2f &t, sf::Vector2f &b, sf::Vector2f &l, sf::Vector2f &r);
	
	private:
		void log(const char* str);
		ginger::Logger* _log = nullptr;
	};
}

#endif //PHYSICAL_H