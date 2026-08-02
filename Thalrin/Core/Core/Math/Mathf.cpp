#include "Mathf.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

namespace Core::Math
{
	float Mathf::ToRadians(float Degrees)
	{
		return Degrees * (float)(M_PI / 180.0f);
	}

	float Mathf::Normalize(float value, float min, float max)
	{
		return (value - min) / (max - min);
	}

	float Mathf::Lerp(float value1, float value2, float time)
	{
		return value1 + (value2 - value1) * time;
	}

	float Mathf::Infinity()
	{
		return std::numeric_limits<float>::infinity();
	}

	float Mathf::PI()
	{
		return 3.14159265358979323846f;
	}

	template CORE_API int Mathf::Min<int>(int a, int b);
	template CORE_API unsigned int Mathf::Min<unsigned int>(unsigned int a, unsigned int b);
	template CORE_API float Mathf::Min<float>(float a, float b);
	template CORE_API double Mathf::Min<double>(double a, double b);

	template CORE_API int Mathf::Max<int>(int a, int b);
	template CORE_API unsigned int Mathf::Max<unsigned int>(unsigned int a, unsigned int b);
	template CORE_API float Mathf::Max<float>(float a, float b);
	template CORE_API double Mathf::Max<double>(double a, double b);
}