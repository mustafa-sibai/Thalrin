#pragma once
#include <string>
#include <vector>
#include <Thalrin/API.h>

namespace Thalrin::Networking
{
	class THALRIN_API Http
	{
	private:
		static bool curlInitialized;
		struct Impl;
		Impl* impl;

	public:
		Http();
		~Http();

		void Initialize();
		bool Get(const std::string& url, std::string& responseBody, const std::vector<std::string>& headers);
	};
}