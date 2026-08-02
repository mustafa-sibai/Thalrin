#pragma once
#include "Core/API.h"

namespace Core::Math
{
	class Mathf
	{
	public:
		static CORE_API float ToRadians(float Degrees);
		static CORE_API float Normalize(float value, float min, float max);
		static CORE_API float Lerp(float value1, float value2, float time);

		static CORE_API float Infinity();
		static CORE_API float PI();

		template <typename T>
		static T Min(T a, T b);

		template <typename T>
		static T Max(T a, T b);

		template <typename T>
		static T Clamp(T value, T lower, T upper);
	};
}

#include "Mathf.inl"