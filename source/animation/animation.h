#include <SFML/Graphics.hpp>
#include <vector>

namespace ginger {
	class Animation
	{
	public:
		Animation() {};
		Animation(const wchar_t* _animTitle, sf::Texture* t, int speed);

		void addFrame(int x, int y, int w, int h, bool flip);
		
		sf::Sprite* getSprite();
		
		void setPosition(float x, float y);
		void getPosition(sf::Vector2f& v);
		void reset();
		void tick(float time);

		bool			isPlaying = true;
		bool			flip = false;
		int				speed = 0;

		std::wstring	getTitle() { return _title; };
	private:
		std::vector<sf::IntRect> _frames;
		std::vector<sf::IntRect> _framesFlip;

		sf::Sprite		_sprite;
		sf::Texture*	_texture = 0;

		int				_currentFrame = 0;
		int				_currentTick = 0;

		int				_offsetX = 10;

		std::wstring	_title = L"unnamed_animation";
	};
}