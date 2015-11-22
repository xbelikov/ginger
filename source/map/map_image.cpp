#include "map_image.h"

namespace ginger {
	void MapImage::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(sprite);
	}
}