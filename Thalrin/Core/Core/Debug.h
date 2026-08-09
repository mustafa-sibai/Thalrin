#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Core/API.h"

class CORE_API Debug
{
private:
	static std::ofstream logFile;
	static std::string logFileName;
	static bool initialized;

private:
	Debug() = delete;
	~Debug() = delete;

public:
	template<typename... Args>
	static void LogInfo(const char* fmt, Args... args)
	{
		Log(Format(fmt, args...), "INFO", FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, std::cout);
	}

	template<typename... Args>
	static void LogWarning(const char* fmt, Args... args)
	{
		Log(Format(fmt, args...), "WARNING", FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, std::cout);
	}

	template<typename... Args>
	static void LogError(const char* fmt, Args... args)
	{
		Log(Format(fmt, args...), "ERROR", FOREGROUND_INTENSITY | FOREGROUND_RED, std::cerr);
	}

	template<typename... Args>
	static void LogFatal(const char* fmt, Args... args)
	{
		Log(Format(fmt, args...), "FATAL", FOREGROUND_INTENSITY | FOREGROUND_RED, std::cerr);
		exit(EXIT_FAILURE);
	}

private:
	template<typename... Args>
	static std::string Format(const char* fmt, Args... args)
	{
		int size = std::snprintf(nullptr, 0, fmt, args...);

		if (size <= 0)
			return std::string(fmt);

		std::string result(size, '\0');
		std::snprintf(result.data(), size + 1, fmt, args...);
		return result;
	}

	static void Log(const std::string& message, const std::string& level, WORD color, std::ostream& outputStream);
	static void InitializeLogFile();
};