#pragma once
#include <cstdint>
#include <Thalrin/API.h>

namespace Thalrin::Networking
{
	class THALRIN_API SlidingBuffer
	{
	private:
		uint8_t* m_buffer;
		int m_size;

		int m_writePosition;
		int m_readPosition;

	public:
		SlidingBuffer(size_t size);
		~SlidingBuffer();

		void Write(const uint8_t* data, size_t size);
		uint8_t* Read(size_t size);
		uint8_t* Peek(size_t size) const;

		int32_t Available() const { return m_size - m_writePosition; }
		uint8_t* GetBuffer() const { return m_buffer; }

	private:
		void Slide();
	};
}