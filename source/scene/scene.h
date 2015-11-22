#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <tinyxml.h>

#ifndef GINGER_SCENE
#define GINGER_SCENE

#include "../animation/animation_list.h"
#include "../logger/logger.h"
#include "../map/map.h"
#include "scene_object.h"
#include "player.h"


namespace ginger {
	class Scene
	{
	public:
		Scene(ginger::Logger* log);
		~Scene();
		int prepareMap(const char* filePath, const char* mapName);
		void setRenderWindow(sf::RenderWindow* w);
		void update(float time);
		void draw();

		ginger::Player*						player;
		std::map<std::string, ginger::Map>	maps;
		std::wstring						name;

		std::string							currentMap;
		ginger::MapObject					curStartPos;
		ginger::MapObject					curEndPos;

		std::vector<ginger::MapObject*>*	mapObjectsForCollisionTest = 0;
	private:
		ginger::Logger*						_log = 0;
		sf::RenderWindow*					_window = 0;
	};
}

#endif