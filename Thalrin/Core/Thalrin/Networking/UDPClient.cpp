#include "UDPClient.h"
#include <ws2tcpip.h>
#include <Thalrin/Networking/Packets/PositionPacket.h>
#include <Thalrin/Debug.h>

namespace Thalrin::Networking
{
	using namespace Thalrin::Networking::Packets;
	using namespace Thalrin::Math;

	UDPClient::UDPClient() :
		m_socket(INVALID_SOCKET),
		m_serverAddress{}
	{}

	UDPClient::~UDPClient()
	{
		if (m_socket != INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}

		WSACleanup();
	}

	void UDPClient::Initialize()
	{
		WSADATA wsaData;
		int startup = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (startup != 0)
		{
			Debug::LogFatal("Failed to initialize Winsock: %d", startup);
			return;
		}

		m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_socket == INVALID_SOCKET)
		{
			Debug::LogFatal("Failed to create socket: %d", WSAGetLastError());
			return;
		}

		u_long nonBlocking = 1;
		int mode = ioctlsocket(m_socket, FIONBIO, &nonBlocking);
		if (mode == SOCKET_ERROR)
		{
			Debug::LogFatal("Failed to set socket to non-blocking mode: %d", WSAGetLastError());
			return;
		}

		m_serverAddress.sin_family = AF_INET;
		m_serverAddress.sin_port = htons(3000);

		int address = inet_pton(AF_INET, "127.0.0.1", &m_serverAddress.sin_addr);
		if (address != 1)
		{
			Debug::LogFatal("Invalid server address");
			return;
		}
	}

	void UDPClient::Update()
	{
		SendHandshake();

		/*
		const char* message = "Hello from UDP Client!";
		int bytesSent = sendto(m_socket, message, (int)strlen(message), 0, (sockaddr*)&m_serverAddress, sizeof(m_serverAddress));
		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				Debug::LogError("Failed to send UDP message: %d", error);
			}
		}
		*/
	}

	void UDPClient::SendPacket(const NetworkBuffer& networkBuffer)
	{
		int bytesSent = sendto(m_socket, (const char*)networkBuffer.data(), (int)networkBuffer.size(), 0, (sockaddr*)&m_serverAddress, sizeof(m_serverAddress));
		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				Debug::LogError("Failed to send UDP message: %d", error);
			}
		}
	}

	void UDPClient::SendHandshake()
	{
		PositionPacket positionPacket(Vector2f(10.0f, 20.0f));
		SendPacket(positionPacket.Serialize());
	}
}