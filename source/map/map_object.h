#ifndef GINGER_MAP_OBJECT
#define GINGER_MAP_OBJECT


#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


namespace ginger {
	struct MapObject : public sf::Drawable, public sf::Transformable {
		int					id = 0;
		std::string			name = "object";
		std::string			type = "default";
		sf::IntRect			rect;
		sf::FloatRect		boundingBox;
		sf::Color			color = sf::Color::Red;
		bool				collision = false;
		//sf::RectangleShape	rectShape;

		bool collDetect(sf::FloatRect &objectBox);
		bool collDetect(sf::Vector2f &objectPoint);

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
	};

	typedef std::vector<ginger::MapObject>::const_iterator MapObjectIterator;
}

#endif