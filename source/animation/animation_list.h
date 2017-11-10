#ifndef GINGER_ANIMATION_LIST
#define GINGER_ANIMATION_LIST


#include "animation.h"


namespace ginger {
	class AnimationList : public sf::Drawable
	{
	public:
		AnimationList() {};

		/**
		 * Loading texture from file
		 * @param const char* textureFileName
		 */
		void loadTexture(const char* textureFileName);

		/**
		 * Create animation by frames
		 * @param const wchar_t* _animTitle
		 */
		void createAnim(const wchar_t* _animTitle, std::vector<sf::IntRect>& frames, int speed);
		
		/**
		 * Update animation state by time, position and direction
		 * @param float time
		 * @param float _x
		 * @param float _y
		 * @param bool flip
		 */
		void updateAnim(float time, float _x, float _y, bool flip);

		/**
		 * Set positition for current frame
		 */
		void set(float x, float y);

		/*
		 * Get current frame position
		 */
		void get(sf::Vector2f &v);

		/**
		 * Flip direction
		 */
		void flip(bool f);


		void play();
		void tick(float time);
		void pause();
		void setTransparentColor(sf::Color color);

		sf::IntRect getCurrentFrame() const;
		sf::Texture getTexture();

		void setAnimByTitle(const wchar_t* animTitle);

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
			target.draw(*_curAnim->getSprite());
		};

		sf::Sprite			_sprite;
		sf::Texture			_texture;
		ginger::Animation*	_curAnim = nullptr;
		sf::Vector2f		_curPos;

		std::map<std::wstring, ginger::Animation> _list;
	};
}

#endif //GINGER_ANIMATION_LIST