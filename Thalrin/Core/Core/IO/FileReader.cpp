#include "FileReader.h"

#include <fstream>
#include <sstream>
#include <Core/Debug.h>

namespace Core::IO
{
	std::string FileReader::ReadTextFile(const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open()) {
			Debug::LogFatal("Failed to open file: %s", filepath.c_str());
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	std::vector<char> FileReader::ReadBinaryFile(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			Debug::LogFatal("Failed to open shader file: %s", filepath.c_str());
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		return buffer;
	}
}