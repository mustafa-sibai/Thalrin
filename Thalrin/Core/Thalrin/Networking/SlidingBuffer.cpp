#include "SlidingBuffer.h"
#include <Thalrin/Debug.h>

namespace Thalrin::Networking
{
	SlidingBuffer::SlidingBuffer(size_t size) :
		m_size(size * 2),
		m_writePosition(0),
		m_readPosition(0)
	{
		m_buffer = new uint8_t[m_size];
	}

	SlidingBuffer::~SlidingBuffer()
	{
		delete[] m_buffer;
	}

	void SlidingBuffer::Write(const uint8_t* data, size_t size)
	{
		if (size > Available())
		{
			return Debug::LogError("SlidingBuffer::Write - Not enough space in buffer");
		}

		Slide();
		std::copy(data, data + size, m_buffer + m_writePosition);
	}

	uint8_t* SlidingBuffer::Read(size_t size)
	{
		if (m_readPosition + size > m_writePosition)
		{
			Debug::LogError("SlidingBuffer::Read - Not enough data in buffer");
			return nullptr;
		}

		m_readPosition += size;
		return m_buffer + m_readPosition - size;
	}

	uint8_t* SlidingBuffer::Peek(size_t size) const
	{
		if (m_readPosition + size > m_writePosition)
		{
			Debug::LogError("SlidingBuffer::Peek - Not enough data in buffer");
			return nullptr;
		}
		return m_buffer + m_readPosition;
	}

	void SlidingBuffer::Slide()
	{
		if (m_readPosition > 0)
		{
			std::copy(m_buffer + m_readPosition, m_buffer + m_writePosition, m_buffer);
			m_writePosition -= m_readPosition;
			m_readPosition = 0;
		}
	}
}