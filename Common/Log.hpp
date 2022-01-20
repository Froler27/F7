#pragma once

#include <string>
#include <iostream>

#define  _F7_LOG_INFO

enum class LogType
{
	NoLog = 0,
	Info = 1,
	Error
};

class Log
{
public:
	enum class ESymbol {
		ENDL,
		END
	};

public:
	Log();
	~Log();

	Log& info()  { _type = LogType::Info;   return *this; }
	Log& error() { _type = LogType::Error;  return *this; }
	Log& noLog() { _type = LogType::NoLog;  return *this; }

	Log& infoLine()  { _bLine = true; return info() ; }
	Log& errorLine() { _bLine = true; return error(); }
	Log& noLogLine() { _bLine = true; return noLog(); }

	Log& operator<<(const char* info);
	Log& operator<<(const std::string& info);
	Log& operator<<(int info);
	Log& operator<<(ESymbol eSymbol);
	Log& show();
	Log& show(LogType eType);

private:
	void Endl();

	LogType _type{ LogType::NoLog };
	LogType _infoType{ LogType::NoLog };
	bool _bLine{ false };
};

using LogSymbol = Log::ESymbol;

#ifdef _F7_LOG_INFO
#define F7Info Log().info()
#define F7InfoLine Log().infoLine()
#else
#define F7Info Log().noLog()
#define F7InfoLine Log().noLogLine()
#endif // _F7_LOG_INFO


