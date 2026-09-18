#pragma once
#include <winsock2.h>
#include <Thalrin/Networking/Serialization/NetworkBuffer.h>
#include <Thalrin/API.h>

namespace Thalrin::Networking
{
	using namespace Thalrin::Networking::Serialization;

	class THALRIN_API UDPClient
	{
	private:
		SOCKET m_socket;
		sockaddr_in m_serverAddress;

	public:
		UDPClient();
		~UDPClient();

		void Initialize();
		void Update();

		void SendPacket(const NetworkBuffer& networkBuffer);
		void SendHandshake();
	};
}