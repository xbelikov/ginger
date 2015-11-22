#ifndef GINGER_UTILS
#define GINGER_UTILS


#include <windows.h>
#include <string>
#include <SFML/Graphics.hpp>


namespace ginger {
	void string_to_wstring(std::string& s, std::wstring &ws);
	void getColorFromHex(std::string& hex, sf::Color& targetColor);
}

#endif //GINGER_UTILS