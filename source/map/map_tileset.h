#ifndef GINGER_MAP_TILESET
#define GINGER_MAP_TILESET


#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


namespace ginger {
	struct MapTileset : public sf::Drawable, public sf::Transformable {
		sf::Texture		texture;
		sf::Color		transparentColor;

		int				firstGid = 1;
		std::string		name = "tileset";

		int				tileWidth = 0;
		int				tileHeight = 0;

		int				mapwidth = 0;
		int				mapheight = 0;

		int				spacing = 0;
		int				margin = 0;

		std::vector<int>		tiles;
		std::vector<sf::Sprite> set;

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
	};

	typedef std::map<std::string, ginger::MapTileset>::const_iterator MapTilesetIterator;
}

#endif