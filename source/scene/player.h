#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#ifndef GINGER_SCENE_PLAYER
#define GINGER_SCENE_PLAYER


#include <tinyxml.h>

#include "../animation/animation_list.h"
#include "../components/physical.h"
#include "../logger/logger.h"
#include "../map/map.h"
#include "scene_object.h"



namespace ginger {
	class Player : public ginger::AnimationList, public Physical //sf::Drawable, public sf::Transformable
	{
	public:
		Player(ginger::Logger* log);

		static const int DIRECTION_RIGHT = 1;
		static const int DIRECTION_LEFT = 2;

		void 	update(float time, std::vector<ginger::MapObject*>* objects);

		void	setAnimation(std::wstring& animTitle);
		void	updateAnimation(float time);

		bool	keyCheck(float time);

		void	move(int direction, float time);
		void	jumping(float time);
		void	hit(float time);
		void	stay(float time);
		void	falling(float time);

		int		health = 100;
		bool	jump = false;

		sf::IntRect boundingBox;
	private:
		void getCollisionTest();
		void _loadSpriteData();

		const char*				_xmlFilePath = "../assets/animations/ginger.xml";
		const char*				_texFilePath = "../assets/images/ginger_with_alpha.png";

		ginger::Logger*			_log;
		/*
		float					_x = 0.0f;
		float					_y = 0.0f;
		*/
		float					_yJumpStart = 0.0f;
		bool					_flip = false;
	};
}

#endif