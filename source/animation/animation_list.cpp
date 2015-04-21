#include "animation_list.h"

namespace ginger {
	void AnimationList::loadTexture(const char* textureFileName)
	{
		_texture.loadFromFile(textureFileName);
	}

	void AnimationList::create(const wchar_t* animTitle, std::vector<sf::IntRect>& frames, int speed)
	{
		if (_list.find(std::wstring(animTitle)) == _list.end()) {
			_list[animTitle] = ginger::Animation(animTitle, &_texture, speed);
		}

		for (std::vector<sf::IntRect>::iterator it = frames.begin(); it != frames.end(); ++it) {
			_list[animTitle].addFrame(it->left, it->top, it->width, it->height, false);
			_list[animTitle].addFrame(it->left + it->width, it->top, -it->width, it->height, true);
		}

		set(animTitle, 0, 0);
	}

	void AnimationList::draw(sf::RenderWindow& window, int x, int y)
	{
		//_curAnim->setPosition(x, y);
		//window.draw(_curAnim->getSprite());
	}

	sf::Sprite* AnimationList::getCurrentFrame() const
	{
		sf::Sprite* s = _curAnim->getSprite();
		return s;
	}

	void AnimationList::set(const wchar_t* animTitle, float x, float y)
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
}