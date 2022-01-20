#include "Log.hpp"
#include <iostream>

#define F7Out std::cout

using namespace std;

Log::Log()
{
}


Log::~Log()
{
}

Log& Log::operator<<(const char* info)
{
	if (_type == LogType::NoLog)
		return *this;
	F7Out << info;
	if (_bLine)
		Endl();
	return *this;
}

Log& Log::operator<<(const std::string& info)
{
	if (_type == LogType::NoLog)
		return *this;
	F7Out << info;
	if (_bLine)
		Endl();
	return *this;
}

Log& Log::operator<<(int info)
{
	if (_type == LogType::NoLog)
		return *this;
	F7Out << info;
	if (_bLine)
		Endl();
	return *this;
}

Log& Log::operator<<(LogSymbol eSymbol)
{
	if (_type == LogType::NoLog)
		return *this;

	switch (eSymbol)
	{
	case LogSymbol::ENDL:
	{
		Endl();
	}
		break;
	case LogSymbol::END:
	{
		F7Out << "\n";
	}
		break;
	default:
		break;
	}
	return *this;
}

Log& Log::show()
{
	switch (_type)
	{
	case LogType::Info:
	{
		F7Out << "Info: ";
	}
		break;
	case LogType::Error:
	{
		F7Out << "Error: ";
	}
		break;
	default:
		break;
	}
	
	return *this;
}

Log& Log::show(LogType eType)
{
	_type = eType;
	return show();
}

void Log::Endl()
{
	F7Out << std::endl;
}
