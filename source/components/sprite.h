#ifndef GINGER_SPRITE
#define GINGER_SPRITE

#include "component.h"
#include "../animation/animation_list.h"

namespace ginger {
	
	class Sprite : public Component, public AnimationList {
	public:
		enum VerticalAlign {
			TOP,
			MIDDLE,
			BOTTOM
		};

		enum HorizontalAlign {
			LEFT,
			RIGHT,
			CENTER
		};

		Sprite();

	private:
		int width;
		int height;
		VerticalAlign vAlign;
		HorizontalAlign hAlign;

		const char* textureFileName;
		const char* animationsFileName;
	};
}

#endif;