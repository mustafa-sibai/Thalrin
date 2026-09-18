#pragma once
#include <Thalrin/API.h>
#include <Thalrin/Networking/Serialization/NetworkBuffer.h>
#include <Thalrin/Math/Math.h>
#include <vector>
#include <string>

namespace Thalrin::Networking::Serialization
{
	using namespace Thalrin::Math;

	class THALRIN_API NetworkBinaryWriter
	{
	private:
		NetworkBuffer m_buffer;
		size_t position;

	public:
		enum class OperationMode
		{
			None,
			Append,
			Overwrite,
		};

	public:
		NetworkBinaryWriter();
		~NetworkBinaryWriter();

		NetworkBinaryWriter(const NetworkBinaryWriter& other);
		NetworkBinaryWriter(NetworkBinaryWriter&& other) noexcept;

		NetworkBinaryWriter& operator=(const NetworkBinaryWriter& other);
		NetworkBinaryWriter& operator=(NetworkBinaryWriter&& other) noexcept;

		void WriteInt16(int16_t value, OperationMode operationMode = OperationMode::Append);
		void WriteUInt16(uint16_t value, OperationMode operationMode = OperationMode::Append);

		void WriteInt32(int32_t value, OperationMode operationMode = OperationMode::Append);
		void WriteUInt32(uint32_t value, OperationMode operationMode = OperationMode::Append);

		void WriteBool(bool value, OperationMode operationMode = OperationMode::Append);
		void WriteFloat(float value, OperationMode operationMode = OperationMode::Append);
		void WriteDouble(double value, OperationMode operationMode = OperationMode::Append);
		void WriteString(const std::string& value, OperationMode operationMode = OperationMode::Append);

		void WriteVector2f(const Vector2f& value, OperationMode operationMode = OperationMode::Append);
		void WriteVector2i(const Vector2i& value, OperationMode operationMode = OperationMode::Append);

		void WriteVector3f(const Vector3f& value, OperationMode operationMode = OperationMode::Append);
		void WriteVector3i(const Vector3i& value, OperationMode operationMode = OperationMode::Append);

		void WriteVector4f(const Vector4f& value, OperationMode operationMode = OperationMode::Append);
		void WriteVector4i(const Vector4i& value, OperationMode operationMode = OperationMode::Append);

		void Clear();

		inline void Seek(size_t position) { this->position = position; }
		inline const NetworkBuffer& GetBuffer() { return m_buffer; }

	private:
		void Write(const void* data, size_t size, OperationMode operationMode);
		void Overwrite(const void* data, size_t size);
		void Append(const void* data, size_t size);
	};
}