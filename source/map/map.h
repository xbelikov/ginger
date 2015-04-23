#include <vector>
#include <SFML/Graphics.hpp>
#include "layers.h"
#include <map>
#include <string>

#include <tinyxml.h>
#include "../utils/utils.h"
#include "../logger/logger.h"

#ifndef GINGER_MAP
#define GINGER_MAP

namespace ginger {
	enum LEVEL_OBJECTS {
		LEVEL_START,
		LEVEL_END
	};

	class Map : public sf::Drawable, public sf::Transformable {
	public:
		Map(ginger::Logger* log);
		void loadFromFile(const char* filePath);
		std::vector<ginger::MapObject*>* getStaticObjectsForCollisionTest();
		ginger::MapObject* getLevelObject(LEVEL_OBJECTS o);

	private:
		ginger::Logger*					_log = 0;
		ginger::Layers					_layers;
		std::wstring					_title;
		std::vector<ginger::MapObject*> _objectsForCollisionTest;
		std::map<int, ginger::MapObject*> _levelObjects;

		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(_layers);
		}
	};
}

#endif //GINGER_MAP