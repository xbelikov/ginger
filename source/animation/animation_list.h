#ifndef GINGER_ANIMATION_LIST
#define GINGER_ANIMATION_LIST


#include "animation.h"
#include "../entity/entity.h"


namespace ginger {
	class AnimationList : public ginger::Entity
	{
	public:
		AnimationList() {};
		void loadTexture(const char* textureFileName);

		void createAnim(const wchar_t* _animTitle, std::vector<sf::IntRect>& frames, int speed);
		
		void updateAnim(float time, float _x, float _y, bool flip);
		//void draw(sf::RenderWindow& window, int x, int y);
		sf::IntRect getCurrentFrame() const;
		sf::Texture getTexture();

		void setAnimByTitle(const wchar_t* animTitle);
		void set(float x, float y);

		void play();
		void flip(bool f);
		void tick(float time);
		void pause();
		void setTransparentColor(sf::Color color);

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			target.draw(*_curAnim->getSprite());
		};

		sf::Sprite			_sprite;
		sf::Texture			_texture;
		ginger::Animation*	_curAnim = 0;

		std::map<std::wstring, ginger::Animation> _list;
	};
}

#endif //GINGER_ANIMATION_LIST