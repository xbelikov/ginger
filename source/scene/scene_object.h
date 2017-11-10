#ifndef GINGER_SCENE_OBJECT
#define GINGER_SCENE_OBJECT


#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <tinyxml.h>

#include "../animation/animation_list.h"
#include "../components/physical.h"
#include "../logger/logger.h"


namespace ginger {
	class SceneObject : public sf::Drawable, public sf::Transformable, public Physical
	{
	public:
		bool collision = true;
		sf::FloatRect boundingBox;

		bool collDetect(sf::FloatRect &objectBox);
		bool collDetect(sf::Vector2f &objectPoint);
	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			sf::RectangleShape rsh(sf::Vector2f(boundingBox.width, boundingBox.height));
			rsh.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
			rsh.setFillColor(sf::Color(255, 255, 255, 255));
			target.draw(rsh);
		};

		sf::Sprite _sprite;
	};
}

#endif