#pragma once
#include <string>
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
	static void LogInfo(const std::string& message);
	static void LogWarning(const std::string& message);
	static void LogError(const std::string& message);
	static void LogFatal(const std::string& message);

private:
	static void Log(const std::string& message, const std::string& level, WORD color, std::ostream& outputStream);
	static void InitializeLogFile();
};