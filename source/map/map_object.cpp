#include "map_object.h"

namespace ginger {
	void MapObject::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		sf::RectangleShape rsh(sf::Vector2f(boundingBox.width, boundingBox.height));
		rsh.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
		rsh.setFillColor(color);
		rt.draw(rsh);
	}

	bool MapObject::collDetect(sf::FloatRect &objectBox) {
		if (!collision) return false;

		if (boundingBox.intersects(objectBox)) {
			return true;
		}

		return false;
	}

	bool MapObject::collDetect(sf::Vector2f &objectPoint) {
		if (!collision) return false;

		if (boundingBox.contains(objectPoint)) {
			return true;
		}

		return false;
	}
}