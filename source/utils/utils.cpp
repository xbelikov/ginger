#include "utils.h"

namespace ginger {
	void string_to_wstring(std::string& s, std::wstring &ws)
	{
		int wchars_num = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[wchars_num];
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wstr, wchars_num);

		ws = wstr;

		delete[] wstr;
	}
}