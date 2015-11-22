#include "map_tileset.h"

namespace ginger {
	void MapTileset::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		std::vector<int>::const_iterator it = tiles.begin();
		sf::Sprite temp = set[*it];

		for (int i = 0; i < mapheight; i++) {
			for (int j = 0; j < mapwidth; j++) {
				if (!*it) {
					++it;
					continue;
				}

				sf::Sprite temp = set[*it - 1];

				temp.setPosition((float)tileWidth * j, (float)tileHeight * i);
				rt.draw(temp);

				++it;
			}
		}
	}
}