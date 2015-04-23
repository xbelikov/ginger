#include "logger.h"
#include "../utils/utils.h"

namespace ginger {
	Logger::Logger()
	{
		if (_open()) {
			_addStartMsg();
		};
	}

	Logger::~Logger()
	{
		_addEndMsg();
		_saveAndClose();
	}
	/*
	void Logger::add(std::wstring& msg)
	{
		char curTime[24];
		getCurrentDateTime(curTime, 22);
		
		#ifdef GINGER_DEBUG
		std::cout << "[" + std::string(curTime) + "] " + _msg << std::endl;
		#endif

		_buffer += "[";
		_buffer += curTime;
		_buffer += "] ";
		_buffer += _msg;
		_buffer += "\n";
	}
	void Logger::add(const wchar_t* msg)
	{
		char curTime[24];
		getCurrentDateTime(curTime, 22);

		#ifdef GINGER_DEBUG
		std::cout << "[" + std::string(curTime) + "] " + std::string(_msg) << std::endl;
		#endif

		_buffer += "[";
		_buffer += curTime;
		_buffer += "] ";
		_buffer += _msg;
		_buffer += "\n";
	}
	*/
	void Logger::add(const char* _msg)
	{
		std::string smsg = _msg;
		std::wstring msg;
		ginger::string_to_wstring(smsg, msg);

		char curTime[24];
		getCurrentDateTime(curTime, 22);

		#ifdef GINGER_DEBUG
		std::cout << "\n[" + std::string(curTime) + "] " + std::string(_msg) << std::endl;
		#endif

		_buffer += "[";
		_buffer += curTime;
		_buffer += "] ";
		_buffer += _msg;
	}

	void Logger::getCurrentDateTime(char* tb, int size)
	{
		time_t  timec;
		time(&timec);

		tm timeinfo;
		localtime_s(&timeinfo, &timec);
	
		strftime(tb, size, "%d.%m.%Y %H:%M:%S", &timeinfo);
	}

	void Logger::_saveAndClose()
	{
		if (_target.is_open()) {
			_target << _buffer;
			_target.close();
		}
	}

	int Logger::_open()
	{ 
		_target.imbue(std::locale("rus"));
		_target.open(_logFileName);

		if (_target.is_open()) {
			return 1;
		}

		return 0;
	}

	void Logger::_addStartMsg()
	{
		add(ginger::LOGGER_START);
	}

	void Logger::_addEndMsg()
	{
		add(ginger::LOGGER_STOP);
	}
} 