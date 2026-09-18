#pragma once
#include <Thalrin/API.h>
#include <Thalrin/Networking/Serialization/NetworkBinaryWriter.h>
#include <Thalrin/Networking/Serialization/NetworkBinaryReader.h>
#include <Thalrin/Math/Vector2.h>

namespace Thalrin::Networking::Packets
{
	using namespace Thalrin::Networking::Serialization;

	class THALRIN_API BasePacket
	{
	protected:
		NetworkBinaryWriter writer;
		NetworkBinaryReader reader;

	public:
		enum class PacketType
		{
			Unknown = -1,
			Position = 5,
		};

		PacketType type;
		uint32_t length;

		BasePacket();
		BasePacket(PacketType type);
		virtual ~BasePacket() = default;

	protected:
		void BeginSerialization();
		const NetworkBuffer& EndSerialization();

	public:
		BasePacket* Deserialize(const uint8_t* buffer);
		BasePacket* Deserialize(const uint8_t* buffer, unsigned long long size);

		PacketType GetType() const { return type; }
		size_t GetSize() const { return length; }
	};
}