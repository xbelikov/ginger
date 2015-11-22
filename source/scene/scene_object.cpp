#include "scene_object.h"
#include "../utils/utils.h"

namespace ginger {
	bool SceneObject::collDetect(sf::FloatRect &objectBox) {
		if (!collision) return false;

		if (boundingBox.intersects(objectBox)) {
			return true;
		}

		return false;
	};

	bool SceneObject::collDetect(sf::Vector2f &objectPoint) {
		if (!collision) return false;

		if (boundingBox.contains(objectPoint)) {
			return true;
		}

		return false;
	};
}