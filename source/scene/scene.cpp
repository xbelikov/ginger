#include "scene.h"
#include "../utils/utils.h"
 
namespace ginger {
	Scene::Scene(ginger::Logger* log) {
		_log = log;
		player = new ginger::Player(_log);
	}

	Scene::~Scene() {
		delete player;
	}

	int Scene::prepareMap(const char* filePath, const char* mapName) {
		ginger::Map map(_log);
		maps[mapName] = map;

		maps[mapName].loadFromFile(filePath);
		mapObjectsForCollisionTest = maps[mapName].getStaticObjectsForCollisionTest();

		int startPosIndex = maps[mapName].getLevelObjectIndex(LEVEL_OBJECTS::LEVEL_START);
		int endPosIndex = maps[mapName].getLevelObjectIndex(LEVEL_OBJECTS::LEVEL_END);

		if (startPosIndex != GINGER_MAP_OBJECT_NOT_FOUND) {
			maps[mapName].getObject(startPosIndex, curStartPos);
		}

		if (endPosIndex != GINGER_MAP_OBJECT_NOT_FOUND) {
			maps[mapName].getObject(endPosIndex, curEndPos);
		}

		currentMap = mapName;

		return 1;
	}

	void Scene::setRenderWindow(sf::RenderWindow* w) {
		_window = w;
	}

	/* Update state for all objects and player */
	void Scene::update(float time) {
		player->update(time, mapObjectsForCollisionTest);
	}

	void Scene::draw() {
		_window->draw(maps[currentMap]);
		_window->draw(*player);
	}	
}