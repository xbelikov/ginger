#ifndef GINGER_COMPONENTS
#define GINGER_COMPONENTS

#include "character_stats.h"
#include "sprite.h"

namespace ginger {
	
	class Components {
	public:
		enum Type {
			CHARACTER_STATS,
			SPRITE
		};

		bool createComponent(Type t, const char* name);
		int getComponentIndex(const char* name);
		Component getComponent(Type t);

		std::map<std::string, ginger::Component> components;

	private:
		bool addComponentToList(ginger::Component c, const char* name);
		bool createCharacterStats(const char* name);
		bool createSprite(const char* name);
	};

}

#endif