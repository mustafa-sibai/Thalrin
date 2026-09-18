#include "UDPServer.h"
#include <ws2tcpip.h>
#include <Thalrin/Networking/Packets/PositionPacket.h>
#include <Thalrin/Debug.h>

namespace Thalrin::Networking
{
	UDPServer::UDPServer() :
		m_socket(INVALID_SOCKET), slidingBuffer(1024)
	{}

	UDPServer::~UDPServer()
	{
		if (m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}
		WSACleanup();
	}

	void UDPServer::Initialize()
	{
		WSADATA wsaData;
		int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (error != 0)
		{
			Debug::LogFatal("Failed to initialize Winsock: %d", error);
			return;
		}

		m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_socket == INVALID_SOCKET)
		{
			Debug::LogFatal("Failed to create socket: %d", WSAGetLastError());
			WSACleanup();
			return;
		}

		u_long nonBlocking = 1;
		error = ioctlsocket(m_socket, FIONBIO, &nonBlocking);
		if (error == SOCKET_ERROR)
		{
			Debug::LogFatal("Failed to set socket to non-blocking mode: %d", WSAGetLastError());
			closesocket(m_socket);
			WSACleanup();
			return;
		}

		sockaddr_in serverAddress{};
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddress.sin_port = htons(3000);

		error = bind(m_socket, (sockaddr*)&serverAddress, sizeof(serverAddress));
		if (error == SOCKET_ERROR)
		{
			Debug::LogFatal("Failed to bind socket: %d", WSAGetLastError());
			closesocket(m_socket);
			WSACleanup();
			return;
		}
	}

	void UDPServer::Update()
	{
		sockaddr_in clientAddress{};
		int clientAddressSize = sizeof(clientAddress);

		char buffer[1024];
		int bytesRead = recvfrom(m_socket, buffer, 1024 - 1, 0, (sockaddr*)&clientAddress, &clientAddressSize);


		if (bytesRead > 0)
		{
			Thalrin::Networking::Packets::PositionPacket positionPacket;
			positionPacket.Deserialize((uint8_t*)buffer);

			slidingBuffer.Write(reinterpret_cast<const uint8_t*>(buffer), bytesRead);

			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &clientAddress.sin_addr, ip, sizeof(ip));

			Debug::LogInfo("Received message from %s:%d", ip, ntohs(clientAddress.sin_port));
		}
		else if (bytesRead == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				Debug::LogError("recvfrom failed: %d", error);
			}
		}
	}
}