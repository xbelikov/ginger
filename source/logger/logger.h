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
	static const char* LOGGER_START = "Logger Start";
	static const char* LOGGER_STOP = "Logger Stop";
	static const char* GAME_START = "Game Start";
	static const char* GAME_STOP = "Game Stop";
	static const char* GAME_CYCLE_START = "Cycle Start";
	static const char* GAME_CYCLE_STOP = "Cycle Stop";
	static const char* LOADING_FONT_START = "Loading font:";
	static const char* LOADING_FONT_STOP = "Font loaded";
	static const char* LOADING_MAP_TILES_OK = "> Loading map tiles OK";
	static const char* LOADING_MAP_IMAGES_OK = "> Loading map images OK";
	static const char* LOADING_MAP_OBJECTS_OK = "> Loading map objects OK";

	class Logger
	{
	public:
		Logger();
		~Logger();
		/*
		void			add(std::wstring& msg);
		void			add(const wchar_t* msg);
		*/
		void			add(const char* msg);
		void			getCurrentDateTime(char* tb, int size);

	private:
		const char*		_logFileName = "./ginger.log";
		std::string		_buffer;
		std::ofstream	_target;

		void			_saveAndClose();
		int				_open();

		void			_addStartMsg();
		void			_addEndMsg();
	};
}

#endif //GINGER_LOGGER