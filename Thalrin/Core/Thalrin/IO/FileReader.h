#pragma once
#include <string>
#include <vector>
#include <Thalrin/API.h>

namespace Thalrin::IO
{
	class THALRIN_API FileReader
	{
	public:
		static std::string ReadTextFile(const std::string& filepath);
		static std::vector<char> ReadBinaryFile(const std::string& filepath);
	};
}