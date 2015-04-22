#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef GINGER_LAYERS
#define GINGER_LAYERS

namespace ginger {
	enum LayerTypes {
		IMAGES,
		TILES,
		OBJECTS
	};

	struct MapTileset : public sf::Drawable, public sf::Transformable {
		sf::Texture		texture;
		sf::Color		transparentColor;

		int				firstGid = 1;
		std::string		name = "tileset";

		int				tileWidth = 0;
		int				tileHeight = 0;

		int				mapwidth = 0;
		int				mapheight = 0;

		int				spacing = 0;
		int				margin = 0;

		std::vector<int>		tiles;
		std::vector<sf::Sprite> set;
	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			//for (std::vector<int>::const_iterator it = tiles.begin(); it < tiles.end(); ++it) {
			
				std::vector<int>::const_iterator it = tiles.begin();
				sf::Sprite temp = set[*it];
				
				for (int i = 0; i < mapheight; i++) {
					for (int j = 0; j < mapwidth; j++) {
						if (!*it) {
							++it;
							continue;
						}

						sf::Sprite temp = set[*it-1];
						
						temp.setPosition(tileWidth * j, tileHeight * i);
						rt.draw(temp);
						
						++it;
					}
				}
			//}
		}
	};

	struct MapImage : public sf::Drawable, public sf::Transformable {
		std::string name = "image";
		sf::Texture texture;
		sf::Sprite	sprite;
	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			rt.draw(sprite);
		}
	};

	struct MapObject : public sf::Drawable, public sf::Transformable {
		int					id = 0;
		std::string			name = "object";
		std::string			type = "default";
		sf::IntRect			rect;
		sf::FloatRect		boundingBox;
		sf::Color			color = sf::Color::Red;
		//sf::RectangleShape	rectShape;

	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			sf::RectangleShape rsh(sf::Vector2f(boundingBox.width, boundingBox.height));
			rsh.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
			rsh.setFillColor(color);
			rt.draw(rsh);
		}
	};

	typedef std::map<std::string, ginger::MapImage>::const_iterator MapImageIterator;
	typedef std::map<std::string, ginger::MapTileset>::const_iterator MapTilesetIterator;
	typedef std::vector<ginger::MapObject>::const_iterator MapObjectIterator;

	struct Layers : public sf::Drawable, public sf::Transformable {
		std::map<std::string,	ginger::MapTileset>	tiles;
		std::map<std::string,	ginger::MapImage>	images;

		std::vector<ginger::MapObject>				staticObjects;
		std::map<std::string, std::vector<int>>		staticObjectsByTypes;
		
		bool										enableDrawObjects;

		int											globalOffsetX = 0;
		int											globalOffsetY = 0;

		void										update();
	private:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
			//������ ���� �����������
			for (MapImageIterator it = images.begin(); it != images.end(); ++it) {
				rt.draw(it->second);
			}

			//������ �����
			for (MapTilesetIterator it = tiles.begin(); it != tiles.end(); ++it) {
				rt.draw(it->second);
			}

			//������ ������� (���� ����)
			if (enableDrawObjects) {
				for (MapObjectIterator it = staticObjects.begin(); it != staticObjects.end(); ++it) {
					rt.draw(*it);
				}
			}
		}
	};
}

#endif //GINGER_LAYERS