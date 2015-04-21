#include "utils.h"
#include <cstdlib>

namespace ginger {
	void string_to_wstring(std::string& s, std::wstring &ws)
	{
		int wchars_num = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[wchars_num];
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wstr, wchars_num);

		ws = wstr;

		delete[] wstr;
	}


	void getColorFromHex(std::string& hex, sf::Color& targetColor) {
		int r, g, b;
		std::string s;

		if (hex.size() == 6) {
			std::string _1, _2;

			_1 = hex[0];
			_2 = hex[1];
			s = _1;
			s += _2;
			r = strtol(s.c_str(), NULL, 16);

			_1 = hex[2];
			_2 = hex[3];
			s = _1;
			s += _2;
			g = strtol(s.c_str(), NULL, 16);

			_1 = hex[4];
			_2 = hex[5];
			s = _1;
			s += _2;
			b = strtol(s.c_str(), NULL, 16);
			
			targetColor.r = r;
			targetColor.g = g;
			targetColor.b = b;
		}
		else if (hex.size() == 3) {
			std::string _1, _2;

			_1 = hex[0];
			_2 = hex[0];
			s = _1;
			s += _2;
			r = strtol(s.c_str(), NULL, 16);

			_1 = hex[1];
			_2 = hex[1];
			s = _1;
			s += _2;
			g = strtol(s.c_str(), NULL, 16);

			_1 = hex[2];
			_2 = hex[2];
			s = _1;
			s += _2;
			b = strtol(s.c_str(), NULL, 16);

			targetColor.r = r;
			targetColor.g = g;
			targetColor.b = b;
		}
	}
}