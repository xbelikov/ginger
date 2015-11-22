#include "animation.h"

namespace ginger {
	void Animation::addFrame(int x, int y, int w, int h, bool flip) {
		if (flip) {
			_framesFlip.push_back(sf::IntRect(x, y, w, h));
		} else {
			_frames.push_back(sf::IntRect(x, y, w, h));
		}
	}

	Animation::Animation(const wchar_t* _animTitle, sf::Texture* t, int spd)  {
		_title = _animTitle;
		_texture = t;
		speed = spd;
		_sprite.setTexture(*t);
	}

	sf::Sprite* Animation::getSprite()
	{
		return &_sprite;
	}

	void Animation::setPosition(float x, float y)
	{
		_sprite.setPosition(x, y);
	}

	void Animation::getPosition(sf::Vector2f& v)
	{
		v = _sprite.getPosition();
	}

	void Animation::tick(float time)
	{
		if (!isPlaying) {
			return;
		}

		if (_currentTick > (speed) || !_currentTick) {
			updateTextureRect();

			if (_currentFrame == (_frames.size()-1)) {
				_currentFrame = 0;
			} else {
				_currentFrame++;
			}

			_currentTick = 1;
		} else {
			_currentTick += (int) round(time);
		}
	}

	void Animation::reset()
	{
		_currentTick = 0;
		_currentFrame = 0;
	}

	sf::IntRect Animation::getTargetRect()
	{
		if (!flip) {
			return _frames[_currentFrame];
		}
		else {
			return _framesFlip[_currentFrame];
		}
	}

	void Animation::updateTextureRect()
	{
		sf::IntRect targetRect = getTargetRect();
		_sprite.setTextureRect(targetRect);
	}
}