#include "BasePacket.h"

namespace Thalrin::Networking::Packets
{
	BasePacket::BasePacket() :
		type(PacketType::Unknown), length(0)
	{}

	BasePacket::BasePacket(PacketType type) :
		type(type), length(0)
	{}

	void BasePacket::BeginSerialization()
	{
		writer.Clear();

		writer.WriteInt32(static_cast<int32_t>(type));
		writer.WriteInt32(length);
	}

	const NetworkBuffer& BasePacket::EndSerialization()
	{
		writer.Seek(sizeof(int32_t));
		writer.WriteInt32(static_cast<int32_t>(writer.GetBuffer().size()), NetworkBinaryWriter::OperationMode::Overwrite);
		return writer.GetBuffer();
	}

	BasePacket* BasePacket::Deserialize(const uint8_t* buffer)
	{
		reader = NetworkBinaryReader(NetworkBuffer(buffer, buffer + sizeof(BasePacket)));
		type = static_cast<PacketType>(reader.ReadInt32());
		length = reader.ReadInt32();
		return this;
	}

	BasePacket* BasePacket::Deserialize(const uint8_t* buffer, unsigned long long size)
	{
		reader = NetworkBinaryReader(NetworkBuffer(buffer, buffer + size));
		type = static_cast<PacketType>(reader.ReadInt32());
		length = reader.ReadInt32();
		return this;
	}
}