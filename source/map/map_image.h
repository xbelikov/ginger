#ifndef GINGER_MAP_IMAGE
#define GINGER_MAP_IMAGE


#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


namespace ginger {
	struct MapImage : public sf::Drawable, public sf::Transformable {
		std::string name = "image";
		sf::Texture texture;
		sf::Sprite	sprite;

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
	};

	typedef std::map<std::string, ginger::MapImage>::const_iterator MapImageIterator;
}

#endif