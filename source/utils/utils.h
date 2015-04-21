#include <windows.h>
#include <string>
#include <SFML/Graphics.hpp>

#ifndef GINGER_UTILS
#define GINGER_UTILS

namespace ginger {
	void string_to_wstring(std::string& s, std::wstring &ws);
	void getColorFromHex(std::string& hex, sf::Color& targetColor);
}

#endif //GINGER_UTILS