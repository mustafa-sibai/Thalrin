#include "PositionPacket.h"

namespace Thalrin::Networking::Packets
{
	PositionPacket::PositionPacket() :
		BasePacket(BasePacket::PacketType::Position),
		position(Vector2f(0, 0))
	{
	}

	PositionPacket::PositionPacket(const Vector2f& position) :
		BasePacket(BasePacket::PacketType::Position),
		position(position)
	{
	}

	PositionPacket::~PositionPacket()
	{
	}

	const NetworkBuffer& PositionPacket::Serialize()
	{
		BasePacket::BeginSerialization();
		writer.WriteVector2f(position);
		return BasePacket::EndSerialization();
	}

	PositionPacket* PositionPacket::Deserialize(const uint8_t* buffer)
	{
		BasePacket::Deserialize(buffer);
		position = reader.ReadVector2f();
		return this;
	}
}