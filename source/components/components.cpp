#include "components.h"

namespace ginger {

	bool Components::createComponent(Type t, const char* name) {
		bool result = false;

		switch (t) {
		case CHARACTER_STATS:
			result = createCharacterStats(name);
			break;

		case SPRITE:
			result = createSprite(name);
			break;
		}

		return result;
	}

	bool Components::createCharacterStats(const char* name) {
		if (addComponentToList(ginger::CharacterStats(), name)) {
			return true;
		}
		
		return false;
	}

	bool Components::createSprite(const char* name) {
		if (addComponentToList(ginger::Sprite(), name)) {
			return true;
		}

		return false;
	}

	bool Components::addComponentToList(ginger::Component c, const char* name) {
		if (components.find(name) != components.end()) {
			components[name] = c;

			return true;
		}

		return false;
	}
}