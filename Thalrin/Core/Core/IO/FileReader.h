#pragma once
#include <string>
#include <vector>
#include "Core/API.h"

namespace Core::IO
{
	class CORE_API FileReader
	{
	public:
		static std::string ReadTextFile(const std::string& filepath);
		static std::vector<char> ReadBinaryFile(const std::string& filepath);
	};
}