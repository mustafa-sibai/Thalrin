#pragma once
#include <string>
#include <ostream>
#include "Core/API.h"

namespace Core::Math
{
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2();
		Vector2(T value);
		Vector2(T x, T y);
		~Vector2();

		T Dot(const Vector2& other) const;
		T Distance(const Vector2& other) const;
		T Magnitude() const;
		Vector2 Direction(const Vector2& other) const;
		Vector2 Normalize() const;
		Vector2 Center() const;
		Vector2 Min();
		Vector2 Max();

		Vector2 operator+(const Vector2& right) const;
		Vector2 operator-(const Vector2& right) const;
		Vector2 operator*(const Vector2& right) const;
		Vector2 operator/(const Vector2& right) const;

		Vector2& operator+=(const Vector2& right);
		Vector2& operator-=(const Vector2& right);
		Vector2& operator*=(const Vector2& right);
		Vector2& operator/=(const Vector2& right);

		bool operator>(const Vector2& right) const;
		bool operator>=(const Vector2& right) const;
		bool operator<(const Vector2& right) const;
		bool operator<=(const Vector2& right) const;

		bool operator==(const Vector2& right) const;
		bool operator!=(const Vector2& right) const;

		static inline Vector2 Zero() { return Vector2(0); }
		static inline Vector2 One() { return Vector2(1); }

		static inline Vector2 Up() { return Vector2(0, -1); }
		static inline Vector2 Down() { return Vector2(0, 1); }

		static inline Vector2 Right() { return Vector2(1, 0); }
		static inline Vector2 Left() { return Vector2(-1, 0); }
	};

	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}

#include "Vector2.inl"