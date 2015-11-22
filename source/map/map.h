#ifndef GINGER_MAP
#define GINGER_MAP


#include <vector>
#include <SFML/Graphics.hpp>
#include "layers.h"
#include <map>
#include <string>

#include <tinyxml.h>
#include "../utils/utils.h"
#include "../logger/logger.h"


#define GINGER_MAP_OBJECT_NOT_FOUND -1
#define GINGER_MAP_TYPE_COLLISION "collision"

namespace ginger {
	enum LEVEL_OBJECTS {
		LEVEL_START,
		LEVEL_END
	};

	class Map : public sf::Drawable, public sf::Transformable {
	public:
		Map() {};
		Map(ginger::Logger* log);
		void loadFromFile(const char* filePath);
		
		std::vector<ginger::MapObject*>* getStaticObjectsForCollisionTest();

		void Map::getObject(int index, ginger::MapObject& target);

		int getLevelObjectIndex(LEVEL_OBJECTS o);
		void getLevelObjectIndexes(LEVEL_OBJECTS o, std::vector<int>& objectIndexes);

	private:
		ginger::Logger*					_log = 0;
		ginger::Layers					_layers;
		std::wstring					_title;
		std::vector<ginger::MapObject*> _objectsForCollisionTest;

		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(_layers);
		}

		ginger::MapObject startPos;
		ginger::MapObject endPos;

		int mapWidth = 0;
		int mapHeight = 0;
		int tilewidth = 0;
		int tileheight = 0;

		int				_findMapData(TiXmlElement* map);
		int				_findTilesetData(TiXmlElement* map);
		int				_findImageLayerData(TiXmlElement* map);
		int				_findObjectGroupData(TiXmlElement* map);
	};
}

#endif //GINGER_MAP