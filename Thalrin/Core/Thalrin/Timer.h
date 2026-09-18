#pragma once
#include <chrono>
#include <Thalrin/API.h>

class THALRIN_API Timer
{
public:
	Timer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;

private:
	std::chrono::steady_clock::time_point last;
};