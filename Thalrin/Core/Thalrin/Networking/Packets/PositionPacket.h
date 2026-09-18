#pragma once
#include <Thalrin/API.h>
#include <Thalrin/Math/Vector2.h>
#include <Thalrin/Networking/Packets/BasePacket.h>

namespace Thalrin::Networking::Packets
{
	class THALRIN_API PositionPacket : public BasePacket
	{
	private:
		Vector2f position;

	public:
		PositionPacket();
		PositionPacket(const Vector2f& position);
		~PositionPacket();

		const NetworkBuffer& Serialize();
		PositionPacket* Deserialize(const uint8_t* buffer);

		inline const Vector2f& GetPosition() const { return position; }
	};
}