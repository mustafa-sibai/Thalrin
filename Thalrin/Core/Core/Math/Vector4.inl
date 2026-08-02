#include <cmath>
#include <string>
#include "Core/Math/Mathf.h"

namespace Core::Math
{
	template<typename T>
	inline Vector4<T>::Vector4() :
		x(0), y(0), z(0), w(0)
	{
	}

	template<typename T>
	inline Vector4<T>::Vector4(T value) :
		x(value), y(value), z(value), w(value)
	{
	}

	template<typename T>
	inline Vector4<T>::Vector4(T x, T y, T z, T w) :
		x(x), y(y), z(z), w(w)
	{
	}

	template<typename T>
	inline Vector4<T>::~Vector4()
	{
	}

	template<typename T>
	inline T Vector4<T>::Dot(const Vector4& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	template<typename T>
	inline T Vector4<T>::Distance(const Vector4& other) const
	{
		Vector4 d = Direction(other);
		return T(std::sqrt(d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w));
	}

	template<typename T>
	inline T Vector4<T>::Magnitude() const
	{
		return T(std::sqrt(Dot(*this)));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Direction(const Vector4& other) const
	{
		return Vector4(std::abs(other.x - x), std::abs(other.y - y), std::abs(other.z - z), std::abs(other.w - w));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Normalize() const
	{
		T length = Magnitude();

		if (length > 0)
			return Vector4(x / length, y / length, z / length, w / length);
		else
			return Vector4(0);
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Center() const
	{
		return Vector4(x / 2, y / 2, z / 2, w / 2);
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Min()
	{
		T min = Mathf::Min(x, y);
		T min2 = Mathf::Min(z, w);
		return Vector4(Mathf::Min(min, min2));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Max()
	{
		T max = Mathf::Max(x, y);
		T max2 = Mathf::Max(z, w);
		return Vector4(Mathf::Max(max, max2));
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator*(const Vector4& other) const
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator/(const Vector4& other) const
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator+=(const Vector4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator-=(const Vector4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator*=(const Vector4& right)
	{
		x *= right.x;
		y *= right.y;
		z *= right.z;
		w *= right.w;
		return *this;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator/=(const Vector4& right)
	{
		x /= right.x;
		y /= right.y;
		z /= right.z;
		w /= right.w;
		return *this;
	}

	template<typename T>
	inline bool Vector4<T>::operator>(const Vector4& right)
	{
		return Magnitude() > right.Magnitude();
	}

	template<typename T>
	inline bool Vector4<T>::operator>=(const Vector4& right)
	{
		return Magnitude() >= right.Magnitude();
	}

	template<typename T>
	inline bool Vector4<T>::operator<(const Vector4& right)
	{
		return Magnitude() < right.Magnitude();
	}

	template<typename T>
	inline bool Vector4<T>::operator<=(const Vector4& right)
	{
		return Magnitude() <= right.Magnitude();
	}

	template<typename T>
	inline bool Vector4<T>::operator==(const Vector4& right)
	{
		return x == right.x && y == right.y && z == right.z && w == right.w;
	}

	template<typename T>
	inline bool Vector4<T>::operator!=(const Vector4& right)
	{
		return !(*this == right);
	}

	template<typename T>
	std::string operator+(const std::string& left, const Vector4<T>& right)
	{
		return left + "{" + std::to_string(right.x) + ", " + std::to_string(right.y) + ", " + std::to_string(right.z) + ", " + std::to_string(right.w) + "}";
	}

	template<typename T>
	std::string operator+(const Vector4<T>& left, const std::string& right)
	{
		return "{" + std::to_string(left.x) + ", " + std::to_string(left.y) + ", " + std::to_string(left.z) + ", " + std::to_string(left.w) + "}" + right;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector4<T>& vector)
	{
		return os << "{" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "}";
	}
}