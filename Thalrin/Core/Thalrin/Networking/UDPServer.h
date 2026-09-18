#pragma once
#include <winsock2.h>
#include <Thalrin/Networking/SlidingBuffer.h>
#include <Thalrin/API.h>

namespace Thalrin::Networking
{
	class THALRIN_API UDPServer
	{
	private:
		SOCKET m_socket;
		SlidingBuffer slidingBuffer;

	public:
		UDPServer();
		~UDPServer();

		void Initialize();
		void Update();
	};
}