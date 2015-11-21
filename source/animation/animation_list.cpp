#include "animation_list.h"

namespace ginger {
	void AnimationList::loadTexture(const char* textureFileName)
	{
		_texture.loadFromFile(textureFileName);
	}

	void AnimationList::createAnim(const wchar_t* animTitle, std::vector<sf::IntRect>& frames, int speed)
	{
		if (_list.find(std::wstring(animTitle)) == _list.end()) {
			_list[animTitle] = ginger::Animation(animTitle, &_texture, speed);
		}

		for (std::vector<sf::IntRect>::iterator it = frames.begin(); it != frames.end(); ++it) {
			_list[animTitle].addFrame(it->left, it->top, it->width, it->height, false);
			_list[animTitle].addFrame(it->left + it->width, it->top, -it->width, it->height, true);
		}

		_sprite.setTexture(getTexture());

		setAnimByTitle(animTitle);
		set(0.0f, 0.0f);
	}

	/*
	void AnimationList::draw(sf::RenderWindow& window, int x, int y)
	{
		//_curAnim->setPosition(x, y);
		//window.draw(_curAnim->getSprite());
	}
	*/

	sf::IntRect AnimationList::getCurrentFrame() const
	{
		//sf::Sprite* s = _curAnim->getSprite();
		//return s;
		return _curAnim->getTargetRect();
	}

	sf::Texture AnimationList::getTexture()
	{
		return _texture;
	}

	void AnimationList::setAnimByTitle(const wchar_t* animTitle)
	{
		bool eqTitles = false;
		bool hasAnim = (_curAnim != 0);

		if (hasAnim) {
			//_curAnim->reset();

			if (std::wstring(animTitle) == _curAnim->getTitle()) {
				eqTitles = true;
			} else {
				_curAnim->reset();
			}
		}

		if (!eqTitles) {
			_curAnim = &_list[animTitle];
			_curAnim->updateTextureRect();
		}
	}

	void AnimationList::set(float x, float y)
	{
		bool hasAnim = (_curAnim != 0);

		if (hasAnim) {
			_curAnim->setPosition(x, y);
		}
	}

	void AnimationList::play()
	{
		_curAnim->isPlaying = true;
	}

	void AnimationList::flip(bool f)
	{
		_curAnim->flip = f;
	}

	void AnimationList::tick(float time)
	{
		_curAnim->tick(time);
	}

	void AnimationList::pause()
	{
		_curAnim->isPlaying = false;
	}

	void AnimationList::setTransparentColor(sf::Color color)
	{
		sf::Image img = _texture.copyToImage();
		img.createMaskFromColor(color);
		_texture.loadFromImage(img);
	}

	void AnimationList::updateAnim(float time, float _x, float _y, bool _flip) {
		//sf::Vector2f currentPos = getPosition();
		//float _x = currentPos.x;
		//float _y = currentPos.y;

		//_anim.set(_x, _y);
		//_anim.flip(_flip);
		//_anim.tick(time);

		//_currentSprite.setTexture(_anim.getTexture());
		//_currentSprite.setTextureRect(_anim.getCurrentFrame());
		
		set(_x, _y);
		flip(_flip);
		tick(time);

		_sprite.setTextureRect(getCurrentFrame());
	}
}