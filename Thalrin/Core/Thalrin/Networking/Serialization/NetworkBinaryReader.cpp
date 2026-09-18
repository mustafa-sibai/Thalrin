#include "NetworkBinaryReader.h"
#include <stdexcept>
#include <winsock2.h>

namespace Thalrin::Networking::Serialization
{
	NetworkBinaryReader::NetworkBinaryReader()
		: m_buffer(NetworkBuffer()), m_position(0)
	{}

	NetworkBinaryReader::NetworkBinaryReader(const NetworkBuffer& buffer)
		: m_buffer(buffer), m_position(0)
	{}

	NetworkBinaryReader::~NetworkBinaryReader()
	{}

	NetworkBinaryReader::NetworkBinaryReader(const NetworkBinaryReader& other)
		: m_buffer(other.m_buffer), m_position(other.m_position)
	{}

	NetworkBinaryReader::NetworkBinaryReader(NetworkBinaryReader&& other) noexcept
		: m_buffer(std::move(other.m_buffer)), m_position(other.m_position)
	{
		other.m_position = 0;
	}

	NetworkBinaryReader& NetworkBinaryReader::operator=(const NetworkBinaryReader& other) {
		if (this != &other) {
			m_buffer = other.m_buffer;
			m_position = other.m_position;
		}
		return *this;
	}

	NetworkBinaryReader& NetworkBinaryReader::operator=(NetworkBinaryReader&& other) noexcept {
		if (this != &other) {
			m_buffer = std::move(other.m_buffer);
			m_position = other.m_position;
			other.m_position = 0;
		}
		return *this;
	}

	int16_t NetworkBinaryReader::ReadInt16()
	{
		if (m_position + sizeof(int16_t) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadInt16 - Buffer overflow");

		int16_t netValue = 0;
		std::memcpy(&netValue, &m_buffer[m_position], sizeof(int16_t));
		m_position += sizeof(int16_t);
		return ntohs(netValue);
	}

	uint16_t NetworkBinaryReader::ReadUInt16()
	{
		if (m_position + sizeof(uint16_t) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadUInt16 - Buffer overflow");

		uint16_t netValue = 0;
		std::memcpy(&netValue, &m_buffer[m_position], sizeof(uint16_t));
		m_position += sizeof(uint16_t);
		return ntohs(netValue);
	}

	int32_t NetworkBinaryReader::ReadInt32()
	{
		if (m_position + sizeof(int32_t) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadInt32 - Buffer overflow");

		int32_t netValue = 0;
		std::memcpy(&netValue, &m_buffer[m_position], sizeof(int32_t));
		m_position += sizeof(int32_t);
		return ntohl(netValue);
	}

	uint32_t NetworkBinaryReader::ReadUInt32()
	{
		if (m_position + sizeof(uint32_t) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadUInt32 - Buffer overflow");

		uint32_t netValue = 0;
		std::memcpy(&netValue, &m_buffer[m_position], sizeof(uint32_t));
		m_position += sizeof(uint32_t);
		return ntohl(netValue);
	}

	bool NetworkBinaryReader::ReadBool()
	{
		if (m_position + sizeof(uint8_t) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadBool - Buffer overflow");

		uint8_t value = 0;
		std::memcpy(&value, &m_buffer[m_position], sizeof(uint8_t));
		m_position += sizeof(uint8_t);
		return (value != 0);
	}

	float NetworkBinaryReader::ReadFloat()
	{
		if (m_position + sizeof(float) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadFloat - Buffer overflow");

		float value = 0;
		std::memcpy(&value, &m_buffer[m_position], sizeof(float));
		m_position += sizeof(float);
		return value;
	}

	double NetworkBinaryReader::ReadDouble()
	{
		if (m_position + sizeof(double) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadDouble - Buffer overflow");

		double value = 0;
		std::memcpy(&value, &m_buffer[m_position], sizeof(double));
		m_position += sizeof(double);
		return value;
	}

	std::string NetworkBinaryReader::ReadString()
	{
		int32_t length = ReadInt32();
		if (length < 0)
			throw std::runtime_error("NetworkBinaryReader::ReadString - Negative length");

		if (m_position + static_cast<size_t>(length) > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::ReadString - Buffer overflow");

		std::string result(reinterpret_cast<const char*>(&m_buffer[m_position]), static_cast<size_t>(length));
		m_position += length;
		return result;
	}

	Vector2f NetworkBinaryReader::ReadVector2f()
	{
		float x = ReadFloat();
		float y = ReadFloat();

		return Vector2f(x, y);
	}

	Vector2i NetworkBinaryReader::ReadVector2i()
	{
		int x = ReadInt32();
		int y = ReadInt32();

		return Vector2i(x, y);
	}

	Vector3f NetworkBinaryReader::ReadVector3f()
	{
		float x = ReadFloat();
		float y = ReadFloat();
		float z = ReadFloat();

		return Vector3f(x, y, z);
	}

	Vector3i NetworkBinaryReader::ReadVector3i()
	{
		int x = ReadInt32();
		int y = ReadInt32();
		int z = ReadInt32();

		return Vector3i(x, y, z);
	}

	Vector4f NetworkBinaryReader::ReadVector4f()
	{
		float x = ReadFloat();
		float y = ReadFloat();
		float z = ReadFloat();
		float w = ReadFloat();

		return Vector4f(x, y, z, w);
	}

	Vector4i NetworkBinaryReader::ReadVector4i()
	{
		int x = ReadInt32();
		int y = ReadInt32();
		int z = ReadInt32();
		int w = ReadInt32();

		return Vector4i(x, y, z, w);
	}

	void NetworkBinaryReader::Seek(size_t position)
	{
		if (position > m_buffer.size())
			throw std::runtime_error("NetworkBinaryReader::Seek - Position out of bounds");

		m_position = position;
	}
}