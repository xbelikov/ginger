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
	class Map : public sf::Drawable, public sf::Transformable {
	public:
		Map(ginger::Logger* log);
		void loadFromFile(const char* filePath);

	private:
		ginger::Logger*				_log = 0;
		ginger::Layers				_layers;
		std::wstring				_title;

		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(_layers);
		}
	};
}

#endif //GINGER_MAP