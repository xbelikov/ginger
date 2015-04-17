#include <windows.h>
#include <string>

#ifndef GINGER_UTILS
#define GINGER_UTILS

namespace ginger {
	void string_to_wstring(std::string& s, std::wstring &ws);
}

#endif //GINGER_UTILS