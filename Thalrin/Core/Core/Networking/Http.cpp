#include "Http.h"
#include <curl/curl.h>
#include <iostream>

namespace Core::Networking
{
	bool Http::curlInitialized = false;

	struct Http::Impl
	{
		CURL* curl;
	};

	static size_t WriteCallback(void* responseData, size_t elementSize, size_t elementCount, void* outputBuffer)
	{
		size_t bytesReceived = elementSize * elementCount;
		std::string* responseText = static_cast<std::string*>(outputBuffer);

		if (responseText)
		{
			responseText->append(static_cast<char*>(responseData), bytesReceived);
		}

		return bytesReceived;
	}

	Http::Http() :
		impl(new Impl())
	{
		if (!curlInitialized)
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			curlInitialized = true;
		}
	}

	Http::~Http()
	{
		curl_easy_cleanup(impl->curl);
		delete impl;
		impl = nullptr;
	}

	void Http::Initialize()
	{
		impl->curl = curl_easy_init();
		if (!impl->curl)
		{
			std::cout << "curl init failed\n";
			return;
		}

		curl_easy_setopt(impl->curl, CURLOPT_URL, "https://httpbin.org/get");
		curl_easy_setopt(impl->curl, CURLOPT_CAINFO, "Certs/cacert-2025-12-02.pem");
		CURLcode result = curl_easy_perform(impl->curl);
		if (result != CURLE_OK)
		{
			std::cout << "request failed: " << curl_easy_strerror(result) << "\n";
		}
		else
		{
			std::cout << "request worked\n";
		}

	}

	bool Http::Get(const std::string& url, std::string& responseBody, const std::vector<std::string>& headers)
	{
		if (!impl->curl)
		{
			std::cout << "curl not initialized\n";
			return false;
		}

		responseBody.clear();

		curl_easy_reset(impl->curl);

		curl_easy_setopt(impl->curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(impl->curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(impl->curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(impl->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(impl->curl, CURLOPT_WRITEDATA, &responseBody);
		curl_easy_setopt(impl->curl, CURLOPT_CAINFO, "Certs/cacert-2025-12-02.pem");

		struct curl_slist* headerList = nullptr;
		for (const std::string& header : headers)
		{
			headerList = curl_slist_append(headerList, header.c_str());
		}

		if (headerList)
		{
			curl_easy_setopt(impl->curl, CURLOPT_HTTPHEADER, headerList);
		}

		CURLcode result = curl_easy_perform(impl->curl);

		long responseCode = 0;
		curl_easy_getinfo(impl->curl, CURLINFO_RESPONSE_CODE, &responseCode);

		if (headerList)
		{
			curl_slist_free_all(headerList);
			headerList = nullptr;
		}

		if (result != CURLE_OK)
		{
			std::cout << "GET failed: " << curl_easy_strerror(result) << "\n";
			return false;
		}

		if (responseCode < 200 || responseCode >= 300)
		{
			std::cout << "GET returned HTTP status " << responseCode << "\n";
			return false;
		}

		return true;
	}
}