#ifndef GINGER_ENTITY
#define GINGER_ENTITY


#include <SFML/Graphics.hpp>
#include "../components/components.h"


namespace ginger {

	class Entity {
	private:
		ginger::Component components;
	};
}


#endif //GINGER_ENTITY