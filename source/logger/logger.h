#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <wchar.h>
#include <time.h>

#define GINGER_DEBUG = 1;

#ifndef GINGER_LOGGER
#define GINGER_LOGGER

namespace ginger {
	class Logger
	{
	public:
		Logger();
		~Logger();
		void			add(std::wstring& msg);
		void			add(const wchar_t* msg);
		void			add(const char* msg);
		void			getCurrentDateTime(wchar_t* tb, int size);

	private:
		const char*		_logFileName = "./ginger.log";
		std::wstring	_buffer;
		std::wofstream	_target;

		void			_saveAndClose();
		int				_open();

		void			_addStartMsg();
		void			_addEndMsg();
	};
}

#endif //GINGER_LOGGER