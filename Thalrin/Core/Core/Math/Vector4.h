#pragma once
#include <string>
#include <ostream>
#include "Core/API.h"

namespace Core::Math
{
	template<typename T>
	class CORE_API Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4();
		Vector4(T value);
		Vector4(T x, T y, T z, T w);
		~Vector4();

		T Dot(const Vector4& other) const;
		T Distance(const Vector4& other) const;
		T Magnitude() const;
		Vector4 Direction(const Vector4& other) const;
		Vector4 Normalize() const;
		Vector4 Center() const;
		Vector4 Min();
		Vector4 Max();

		Vector4 operator+(const Vector4& right) const;
		Vector4 operator-(const Vector4& right) const;
		Vector4 operator*(const Vector4& right) const;
		Vector4 operator/(const Vector4& right) const;

		Vector4& operator+=(const Vector4& right);
		Vector4& operator-=(const Vector4& right);
		Vector4& operator*=(const Vector4& right);
		Vector4& operator/=(const Vector4& right);

		bool operator>(const Vector4& right);
		bool operator>=(const Vector4& right);
		bool operator<(const Vector4& right);
		bool operator<=(const Vector4& right);

		bool operator==(const Vector4& right);
		bool operator!=(const Vector4& right);

		static inline Vector4 Zero() { return Vector4(0); }
		static inline Vector4 One() { return Vector4(1); }
	};

	using Vector4i = Vector4<int>;
	using Vector4u = Vector4<unsigned int>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
}

#include "Vector4.inl"