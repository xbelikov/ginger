#include "physical.h"
#include "../map/map.h"

namespace ginger {

	void Physical::getCollisionTargets(sf::Vector2f &cp, sf::IntRect &bb, sf::Vector2f &t, sf::Vector2f &b, sf::Vector2f &l, sf::Vector2f &r)
	{
		l.x = cp.x;
		l.y = cp.y;

		r.x = cp.x + bb.width;
		r.y = cp.y + bb.height / 2;

		t.x = cp.x + bb.width / 2;
		t.y = cp.y;

		b.x = cp.x + bb.width / 2;
		b.y = cp.y + bb.height;
	}

	void Physical::checkCollisions(std::vector<ginger::MapObject*>* objects, sf::IntRect &boundingBox, sf::Vector2f &currentPos)
	{
		collisionTestLeft = false;
		collisionTestRight = false;
		collisionTestTop = false;
		collisionTestBottom = false;

		sf::Vector2f l, r, t, b;
		getCollisionTargets(currentPos, boundingBox, t, b, l, r);

		/* --- collision test --- */
		for (auto i = objects->begin(); i != objects->end(); ++i) {
			auto it = *i;
			if (!collisionTestLeft && it->collDetect(l)) {
				collisionTestLeft = true;
				log("collisionTestLeft = true;");
			}

			if (!collisionTestRight && it->collDetect(r)) {
				collisionTestRight = true;
				log("collisionTestRight = true;");
			}

			if (!collisionTestTop && it->collDetect(t)) {
				collisionTestTop = true;
				log("collisionTestTop = true;");
			}

			if (!collisionTestBottom && it->collDetect(b)) {
				onGround = true;
				jumpLimit = false;
				collisionTestBottom = true;
				//log("onGround = true;");
			}
		}
		/* --- */

		if (!collisionTestBottom) {
			onGround = false;
		}
	}

	void Physical::log(const char* str)
	{
		if (_log != nullptr) {
			_log->add(str);
		}
	}
}