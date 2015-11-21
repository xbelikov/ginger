#include <SFML/Graphics.hpp>

#ifndef GINGER_ENTITY
#define GINGER_ENTITY

namespace ginger {

	class Entity: public sf::Transformable, public sf::Drawable {
	public: 
		virtual void update(float time) {};

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
	};
}


#endif //GINGER_ENTITY