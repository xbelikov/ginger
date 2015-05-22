#include "animation.h"


#ifndef GINGER_ANIMATION_LIST
#define GINGER_ANIMATION_LIST

namespace ginger {
	class AnimationList
	{
	public:
		AnimationList() {};
		void loadTexture(const char* textureFileName);

		void create(const wchar_t* _animTitle, std::vector<sf::IntRect>& frames, int speed);
		
		void draw(sf::RenderWindow& window, int x, int y);
		sf::Sprite* getCurrentFrame() const;

		void set(const wchar_t* animTitle);
		void set(float x, float y);

		void play();
		void flip(bool f);
		void tick(float time);
		void pause();
		void setTransparentColor(sf::Color color);

	private:
		sf::Texture			_texture;
		ginger::Animation*	_curAnim = 0;

		std::map<std::wstring, ginger::Animation> _list;
	};
}

#endif //GINGER_ANIMATION_LIST