#include "map.h"

namespace ginger {
	Map::Map(ginger::Logger* log) {
		_log = log;
	}

	void Map::loadFromFile(const char* filePath) {
		TiXmlDocument mapData(filePath);
		
		mapData.LoadFile();

		_log->add(L"Загрузка карты:|-->");
		_log->add(filePath);

		TiXmlElement	*map = 0,
						*tileset = 0,
						*tileData = 0,
						*tileItem = 0,
						*tilesetImage = 0,
						*imagelayer = 0,
						*imagelayerImage = 0,
						*tileLayer = 0,
						*objectGroup = 0;

		ginger::MapTileset* mapTileset = 0;
		ginger::MapImage* mapImage = 0;
		ginger::MapObject* mapObject = 0;

		map = mapData.FirstChildElement("map");

		//атрибуты map
		int mapWidth = atoi(map->Attribute("width"));
		int mapHeight = atoi(map->Attribute("height"));
		int tilewidth = atoi(map->Attribute("tilewidth"));
		int tileheight = atoi(map->Attribute("tileheight"));
		

		tileset = map->FirstChildElement("tileset");

		//атрибуты tileset
		std::string tilesetName = tileset->Attribute("name");
		int tilesetFirstGid = atoi(tileset->Attribute("firstgid"));
		int tilesetMargin = atoi(tileset->Attribute("margin"));
		int tilesetSpacing = atoi(tileset->Attribute("spacing"));

		tilesetImage = tileset->FirstChildElement("image");

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
			_log->add(L"Ошибка: не удалось выделить память для блока mapTileset");
			return;
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

		tileLayer = map->FirstChildElement("layer");
		tileData = tileLayer->FirstChildElement("data");
		tileItem = tileData->FirstChildElement("tile");

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
		//--------------------------------------------------------------------------------------------




		

		imagelayer = map->FirstChildElement("imagelayer");
		imagelayerImage = imagelayer->FirstChildElement("image");

		std::string imagelayerName = imagelayer->Attribute("name");
		int imagelayerOffsetX = atoi(imagelayer->Attribute("x"));
		int imagelayerOffsetY = atoi(imagelayer->Attribute("y"));
		std::string imagelayerFile = imagelayerImage->Attribute("source");

		//создадим и заполним структуру для tileset
		try {
			mapImage = new ginger::MapImage;
		}
		catch (std::bad_alloc &ab) {
			_log->add(L"Ошибка: не удалось выделить память для блока mapImage");
			return;
		}

		mapImage->name = imagelayerName;
		
		sf::Vector2<int> imagelayerSize;
		//imagelayerSize.x = mapImage->texture.getSize().x;
		//imagelayerSize.y = mapImage->texture.getSize().y;

		_layers.images[imagelayerName] = *mapImage;
		_layers.images[imagelayerName].texture.loadFromFile(std::string("../assets/images/") + std::string(imagelayerFile));
		_layers.images[imagelayerName].sprite.setTexture(_layers.images[imagelayerName].texture);
		imagelayerSize.x = _layers.images[imagelayerName].texture.getSize().x;
		imagelayerSize.y = _layers.images[imagelayerName].texture.getSize().y;
		_layers.images[imagelayerName].sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(-imagelayerOffsetX, -imagelayerOffsetY), imagelayerSize));

		delete mapImage;
		//--------------------------------------------------------------------------------------------






		_log->add(L"<--загрузили|");
	}
}