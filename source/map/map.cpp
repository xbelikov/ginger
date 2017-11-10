#include "map.h"

namespace ginger {
	Map::Map(ginger::Logger* log) {
		_log = log;
	}

	void Map::loadFromFile(const char* filePath) {
		TiXmlDocument mapData(filePath);
		
		mapData.LoadFile();

		_log->add("Загрузка карты:|-->");
		_log->add(filePath);

		TiXmlElement *map = mapData.FirstChildElement("map");

		_findMapData(map);
		
		//тайлы
		if (_findTilesetData(map)) {
			_log->add(ginger::LOADING_MAP_TILES_OK);
		}
		//--------------------------------

		//фон
		if (_findImageLayerData(map)) {
			_log->add(ginger::LOADING_MAP_IMAGES_OK);
		}
		//--------------------------------

		//объекты
		if (_findObjectGroupData(map)) {
			_log->add(ginger::LOADING_MAP_OBJECTS_OK);
		}
		//--------------------------------

		_log->add("<--загрузили|");
	}

	int Map::_findMapData(TiXmlElement* map) {

		//атрибуты map
		mapWidth = atoi(map->Attribute("width"));
		mapHeight = atoi(map->Attribute("height"));
		tilewidth = atoi(map->Attribute("tilewidth"));
		tileheight = atoi(map->Attribute("tileheight"));

		return 1;
	}

	int	Map::_findTilesetData(TiXmlElement* map) {
		ginger::MapTileset* mapTileset = 0;
		TiXmlElement* tileset = map->FirstChildElement("tileset");
		TiXmlElement* tilesetImage = tileset->FirstChildElement("image");
		TiXmlElement* tileLayer = map->FirstChildElement("layer");
		TiXmlElement* tileData = tileLayer->FirstChildElement("data");
		TiXmlElement* tileItem = tileData->FirstChildElement("tile");

		//атрибуты tileset
		std::string tilesetName = tileset->Attribute("name");
		int tilesetFirstGid = atoi(tileset->Attribute("firstgid"));
		int tilesetMargin = atoi(tileset->Attribute("margin"));
		int tilesetSpacing = atoi(tileset->Attribute("spacing"));

		//картинка для tileset
		std::string tilesetImageFile = tilesetImage->Attribute("source");
		int tilesetImageWidth = atoi(tilesetImage->Attribute("width"));
		int tilesetImageHeight = atoi(tilesetImage->Attribute("height"));
		std::string transparentColor = tilesetImage->Attribute("trans");

		//создадим и заполним структуру для tileset
		try {
			mapTileset = new ginger::MapTileset;
		}
		catch (std::bad_alloc &ab) {
			std::string msg = "Ошибка: не удалось выделить память для блока mapTileset (" + std::string(ab.what()) + ")";
			_log->add(msg.c_str());
			return 0;
		}

		mapTileset->name = tilesetName;
		mapTileset->tileWidth = tilewidth;
		mapTileset->tileHeight = tileheight;
		mapTileset->firstGid = tilesetFirstGid;
		mapTileset->margin = tilesetMargin;
		mapTileset->spacing = tilesetSpacing;
		mapTileset->mapwidth = mapWidth;
		mapTileset->mapheight = mapHeight;
		ginger::getColorFromHex(transparentColor, mapTileset->transparentColor);

		int tilesNum = (tilesetImageWidth / (tilewidth + tilesetSpacing)) * (tilesetImageHeight / (tileheight + tilesetMargin));
		int x = tilesetSpacing;
		int y = tilesetMargin;

		for (int i = 0; i < tilesNum; i++) {
			mapTileset->set.push_back(sf::Sprite(mapTileset->texture, sf::IntRect(x, y, tilewidth, tileheight)));

			if ((x + tilewidth + tilesetSpacing) < tilesetImageWidth) {
				x += tilewidth + tilesetSpacing;
			}
			else {
				y += tileheight + tilesetMargin;
				x = tilesetSpacing;
			}
		}

		//разберем tileItem
		while (tileItem) {
			mapTileset->tiles.push_back(atoi(tileItem->Attribute("gid")));
			tileItem = tileItem->NextSiblingElement("tile");
		}

		//добавляем tileset
		_layers.tiles[tilesetName] = *mapTileset;

		std::string imageFilePath = std::string("../assets/images/") + std::string(tilesetImageFile);
		sf::Image tempImage;
		tempImage.loadFromFile(imageFilePath);
		tempImage.createMaskFromColor(_layers.tiles[tilesetName].transparentColor);
		_layers.tiles[tilesetName].texture.loadFromImage(tempImage);

		for (int i = 0; i < tilesNum; i++) {
			_layers.tiles[tilesetName].set[i].setTexture(_layers.tiles[tilesetName].texture);
		}

		delete mapTileset;

		return 1;
	}

	int	Map::_findImageLayerData(TiXmlElement* map) {
		ginger::MapImage* mapImage = 0;
		TiXmlElement* imagelayer = map->FirstChildElement("imagelayer");
		TiXmlElement* imagelayerImage = imagelayer->FirstChildElement("image");

		std::string imagelayerName = imagelayer->Attribute("name");
		int imagelayerOffsetX = atoi(imagelayer->Attribute("x"));
		int imagelayerOffsetY = atoi(imagelayer->Attribute("y"));
		std::string imagelayerFile = imagelayerImage->Attribute("source");

		sf::Vector2<int> imagelayerSize;

		//_layers.images[imagelayerName] = *mapImage;
		_layers.images[imagelayerName].name = imagelayerName;
		_layers.images[imagelayerName].texture.loadFromFile(std::string("../assets/images/") + std::string(imagelayerFile));
		_layers.images[imagelayerName].sprite.setTexture(_layers.images[imagelayerName].texture);
		imagelayerSize.x = _layers.images[imagelayerName].texture.getSize().x;
		imagelayerSize.y = _layers.images[imagelayerName].texture.getSize().y;
		_layers.images[imagelayerName].sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(0, 0), imagelayerSize));
		_layers.images[imagelayerName].sprite.setPosition(sf::Vector2f(imagelayerOffsetX, imagelayerOffsetY));

		return 1;
	}
	
	int	Map::_findObjectGroupData(TiXmlElement* map) {
		ginger::MapObject* mapObject = 0;
		TiXmlElement* objectGroup = map->FirstChildElement("objectgroup");
		TiXmlElement* objectItem = objectGroup->FirstChildElement("object");

		std::string objectgroupName = objectGroup->Attribute("name");
		
		while (objectItem) {
			int index = _layers.staticObjects.size();
			int objectId = atoi(objectItem->Attribute("id"));

			sf::IntRect	objectPosSize(
				atoi(objectItem->Attribute("x")),
				atoi(objectItem->Attribute("y")),
				atoi(objectItem->Attribute("width")),
				atoi(objectItem->Attribute("height"))
			);

			std::string objectName = objectItem->Attribute("name");
			std::string objectType = "";
			int			objectCollision = atoi(objectItem->Attribute("collision"));

			if (objectItem->Attribute("type")) {
				objectType = objectItem->Attribute("type");
			}

			ginger::MapObject mapObject;

			mapObject.name = objectName;
			mapObject.type = objectType;
			mapObject.rect = objectPosSize;
			mapObject.boundingBox.left = static_cast<float>(objectPosSize.left);
			mapObject.boundingBox.top = static_cast<float>(objectPosSize.top);
			mapObject.boundingBox.width = static_cast<float>(objectPosSize.width);
			mapObject.boundingBox.height = static_cast<float>(objectPosSize.height);

			if (objectCollision) {
				mapObject.collision = true;
				_layers.staticObjectsByTypes[GINGER_MAP_TYPE_COLLISION].push_back(index);
			}

			_layers.staticObjects.push_back(mapObject);

			if (objectType.size()) {
				if (_layers.staticObjectsByTypes.find(objectType) != _layers.staticObjectsByTypes.end()) {
					_layers.staticObjectsByTypes[objectType].push_back(index);
				}
				else {
					std::vector<int> tempV;
					tempV.push_back(index);
					_layers.staticObjectsByTypes[objectType] = tempV;
				}
			}

			objectItem = objectItem->NextSiblingElement();
		}

		return 1;
	}

	std::vector<ginger::MapObject*>* Map::getStaticObjectsForCollisionTest() {
		/*
		if(!_objectsForCollisionTest.size()) {
			if(_layers.staticObjectsByTypes.find("ground") != _layers.staticObjectsByTypes.end()) {
				std::vector<int> temp = _layers.staticObjectsByTypes["ground"];
				for(std::vector<int>::iterator it = temp.begin(); it < temp.end(); ++it) {
					_objectsForCollisionTest.push_back(&_layers.staticObjects[*it]);
				}
			}

			if(_layers.staticObjectsByTypes.find("platform") != _layers.staticObjectsByTypes.end()) {
				std::vector<int> temp = _layers.staticObjectsByTypes["platform"];
				for(std::vector<int>::iterator it = temp.begin(); it < temp.end(); ++it) {
					_objectsForCollisionTest.push_back(&_layers.staticObjects[*it]);
				}
			}
		}
		*/

		if (!_objectsForCollisionTest.size()) {
			if (_layers.staticObjectsByTypes.find(GINGER_MAP_TYPE_COLLISION) != _layers.staticObjectsByTypes.end()) {
				std::vector<int> temp = _layers.staticObjectsByTypes[GINGER_MAP_TYPE_COLLISION];
				for (std::vector<int>::iterator it = temp.begin(); it < temp.end(); ++it) {
					_objectsForCollisionTest.push_back(&_layers.staticObjects[*it]);
				}
			}
		}

		return &_objectsForCollisionTest;
	}

	/*
	* Get object index by type
	* write std::vector<int> indexes of objects into a second parameter
	*/
	void Map::getLevelObjectIndexes(LEVEL_OBJECTS o, std::vector<int>& objectIndexes) {
		switch (o) {
		case LEVEL_OBJECTS::LEVEL_START:
			if (_layers.staticObjectsByTypes.find("start") != _layers.staticObjectsByTypes.end()) {
				objectIndexes = _layers.staticObjectsByTypes["start"];
			}
			break;

		case LEVEL_OBJECTS::LEVEL_END:
			if (_layers.staticObjectsByTypes.find("start") != _layers.staticObjectsByTypes.end()) {
				objectIndexes = _layers.staticObjectsByTypes["start"];
			}
			break;
		}
	}

	/*
	 * Get object index by type
	 * return object index or -1
	 */
	int Map::getLevelObjectIndex(LEVEL_OBJECTS o) {
		std::vector<int> objectIndexes;

		switch (o) {
		case LEVEL_OBJECTS::LEVEL_START:
			if (_layers.staticObjectsByTypes.find("start") != _layers.staticObjectsByTypes.end()) {
				objectIndexes = _layers.staticObjectsByTypes["start"];
			}
			break;

		case LEVEL_OBJECTS::LEVEL_END:
			if (_layers.staticObjectsByTypes.find("exit") != _layers.staticObjectsByTypes.end()) {
				objectIndexes = _layers.staticObjectsByTypes["exit"];
			}
			break;
		}

		if (objectIndexes.size()) {
			return objectIndexes[0];
		}

		return GINGER_MAP_OBJECT_NOT_FOUND;
	}

	void Map::getObject(int index, ginger::MapObject& target) {
		target = _layers.staticObjects.at(index);
	}
}