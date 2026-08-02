#pragma once
#include <string>
#include <ostream>
#include "Core/API.h"

namespace Core::Math
{
	template<typename T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;

		Vector3();
		Vector3(T value);
		Vector3(T x, T y, T z);
		~Vector3();

		T Dot(const Vector3& other) const;
		T Distance(const Vector3& other) const;
		T Magnitude() const;
		Vector3 Cross(const Vector3& other) const;
		Vector3 Direction(const Vector3& other) const;
		Vector3 Normalize() const;
		Vector3 Center() const;
		Vector3 Min();
		Vector3 Max();

		Vector3 operator+(const Vector3& right) const;
		Vector3 operator-(const Vector3& right) const;
		Vector3 operator*(const Vector3& right) const;
		Vector3 operator/(const Vector3& right) const;

		Vector3& operator+=(const Vector3& right);
		Vector3& operator-=(const Vector3& right);
		Vector3& operator*=(const Vector3& right);
		Vector3& operator/=(const Vector3& right);

		bool operator>(const Vector3& right);
		bool operator>=(const Vector3& right);
		bool operator<(const Vector3& right);
		bool operator<=(const Vector3& right);

		bool operator==(const Vector3& right);
		bool operator!=(const Vector3& right);

		static inline Vector3 Zero() { return Vector3(0); }
		static inline Vector3 One() { return Vector3(1); }

		static inline Vector3 Up() { return Vector3(0, 1, 0); }
		static inline Vector3 Down() { return Vector3(0, -1, 0); }

		static inline Vector3 Right() { return Vector3(1, 0, 0); }
		static inline Vector3 Left() { return Vector3(-1, 0, 0); }

		static inline Vector3 Forward() { return Vector3(0, 0, 1); }
		static inline Vector3 Back() { return Vector3(0, 0, -1); }
	};

	using Vector3i = Vector3<int>;
	using Vector3u = Vector3<unsigned int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
}

#include "Vector3.inl"