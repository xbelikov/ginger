#ifndef GINGER_LAYERS
#define GINGER_LAYERS


#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
 
#include "map_image.h"
#include "map_tileset.h"
#include "map_object.h"

namespace ginger {
	enum LayerTypes {
		IMAGES,
		TILES,
		OBJECTS
	};

	class Layers: public sf::Drawable, public sf::Transformable {

	public:
		std::map<std::string,	ginger::MapTileset>	tiles;
		std::map<std::string,	ginger::MapImage>	images;

		std::vector<ginger::MapObject>				staticObjects;
		std::map<std::string, std::vector<int>>		staticObjectsByTypes;
		
													/* -- ENABLE DRAW OBJECTS -- */
		bool										enableDrawObjects = true;

		int											globalOffsetX = 0;
		int											globalOffsetY = 0;

		void										update();

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			//Draw background layer
			for (MapImageIterator it = images.begin(); it != images.end(); ++it) {
				rt.draw(it->second);
			}

			//ÐDraw tiles
			for (MapTilesetIterator it = tiles.begin(); it != tiles.end(); ++it) {
				rt.draw(it->second);
			}

			//Draw objects
			if (enableDrawObjects) {
				for (MapObjectIterator it = staticObjects.begin(); it != staticObjects.end(); ++it) {
					rt.draw(*it);
				}
			}
		}
	};
}

#endif //GINGER_LAYERS