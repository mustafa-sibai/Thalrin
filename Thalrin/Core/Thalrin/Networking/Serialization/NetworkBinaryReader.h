#pragma once
#include <Thalrin/API.h>
#include <Thalrin/Networking/Serialization/NetworkBuffer.h>
#include <Thalrin/Math/Math.h>
#include <vector>
#include <string>

namespace Thalrin::Networking::Serialization
{
	using namespace Thalrin::Math;

	class THALRIN_API NetworkBinaryReader
	{
	private:
		NetworkBuffer m_buffer;
		size_t m_position;

	public:
		NetworkBinaryReader();
		explicit NetworkBinaryReader(const NetworkBuffer& buffer);
		~NetworkBinaryReader();

		NetworkBinaryReader(const NetworkBinaryReader& other);
		NetworkBinaryReader(NetworkBinaryReader&& other) noexcept;

		NetworkBinaryReader& operator=(const NetworkBinaryReader& other);
		NetworkBinaryReader& operator=(NetworkBinaryReader&& other) noexcept;

		int16_t ReadInt16();
		uint16_t ReadUInt16();

		int32_t ReadInt32();
		uint32_t ReadUInt32();

		bool ReadBool();
		float ReadFloat();
		double ReadDouble();
		std::string ReadString();

		Vector2f ReadVector2f();
		Vector2i ReadVector2i();

		Vector3f ReadVector3f();
		Vector3i ReadVector3i();

		Vector4f ReadVector4f();
		Vector4i ReadVector4i();

		void Seek(size_t position);

		inline void SetBuffer(const NetworkBuffer& buffer) { m_buffer = buffer; }
	};
}