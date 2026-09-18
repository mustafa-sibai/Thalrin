#pragma once
#include <Thalrin/API.h>

namespace Thalrin::Math
{
	class Mathf
	{
	public:
		static THALRIN_API float ToRadians(float Degrees);
		static THALRIN_API float Normalize(float value, float min, float max);
		static THALRIN_API float Lerp(float value1, float value2, float time);

		static THALRIN_API float Infinity();
		static THALRIN_API float PI();

		template <typename T>
		static T Min(T a, T b);

		template <typename T>
		static T Max(T a, T b);

		template <typename T>
		static T Clamp(T value, T lower, T upper);
	};
}

#include "Mathf.inl"