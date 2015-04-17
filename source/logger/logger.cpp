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
	
	void Logger::add(std::wstring& msg)
	{
		wchar_t curTime[24];
		getCurrentDateTime(curTime, 22);
		
		#ifdef GINGER_DEBUG
		std::wcout << L"[" + std::wstring(curTime) + L"] " + msg << std::endl;
		#endif

		_buffer += L"[";
		_buffer += curTime;
		_buffer += L"] ";
		_buffer += msg;
		_buffer += L"\n";
	}

	void Logger::add(const wchar_t* msg)
	{
		wchar_t curTime[24];
		getCurrentDateTime(curTime, 22);

		#ifdef GINGER_DEBUG
		std::wcout << L"[" + std::wstring(curTime) + L"] " + std::wstring(msg) << std::endl;
		#endif

		_buffer += L"[";
		_buffer += curTime;
		_buffer += L"] ";
		_buffer += msg;
		_buffer += L"\n";
	}

	void Logger::add(const char* _msg)
	{
		std::string smsg = _msg;
		std::wstring msg;
		ginger::string_to_wstring(smsg, msg);

		wchar_t curTime[24];
		getCurrentDateTime(curTime, 22);

		#ifdef GINGER_DEBUG
		std::wcout << L"[" + std::wstring(curTime) + L"] " + std::wstring(msg) << std::endl;
		#endif

		_buffer += L"[";
		_buffer += curTime;
		_buffer += L"] ";
		_buffer += msg;
		_buffer += L"\n";
	}

	void Logger::getCurrentDateTime(wchar_t* tb, int size)
	{
		time_t  timec;
		time(&timec);

		tm timeinfo;
		localtime_s(&timeinfo, &timec);
	
		wcsftime(tb, size, L"%d.%m.%Y %H:%M:%S", &timeinfo);
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
		add(L"стартуем");
	}

	void Logger::_addEndMsg()
	{
		add(L"завершаем");
	}
}