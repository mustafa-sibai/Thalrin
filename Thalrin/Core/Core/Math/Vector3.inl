#include <cmath>
#include <string>
#include "Core/Math/Mathf.h"

namespace Core::Math
{
	template<typename T>
	Vector3<T>::Vector3() :
		x(0), y(0), z(0)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(T value) :
		x(value), y(value), z(value)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(T x, T y, T z) :
		x(x), y(y), z(z)
	{
	}

	template<typename T>
	Vector3<T>::~Vector3()
	{
	}

	template<typename T>
	T Vector3<T>::Dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	template<typename T>
	T Vector3<T>::Distance(const Vector3& other) const
	{
		Vector3 d = Direction(other);
		return T(std::sqrt(d.x * d.x + d.y * d.y + d.z * d.z));
	}

	template<typename T>
	T Vector3<T>::Magnitude() const
	{
		return T(std::sqrt(Dot(*this)));
	}

	template<typename T>
	Vector3<T> Vector3<T>::Cross(const Vector3& other) const
	{
		return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	template<typename T>
	Vector3<T> Vector3<T>::Direction(const Vector3& other) const
	{
		return Vector3(std::abs(other.x - x), std::abs(other.y - y), std::abs(other.z - z));
	}

	template<typename T>
	Vector3<T> Vector3<T>::Normalize() const
	{
		T length = Magnitude();

		if (length > 0)
			return Vector3(x / length, y / length, z / length);
		else
			return Vector3(0);
	}

	template<typename T>
	Vector3<T> Vector3<T>::Center() const
	{
		return Vector3(x / 2, y / 2, z / 2);
	}

	template<typename T>
	Vector3<T> Vector3<T>::Min()
	{
		T min = Mathf::Min(x, y);
		return Vector3(Mathf::Min(min, z));
	}

	template<typename T>
	Vector3<T> Vector3<T>::Max()
	{
		T max = Mathf::Max(x, y);
		return Vector3(Mathf::Max(max, z));
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(const Vector3& other) const
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(const Vector3& right)
	{
		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(const Vector3& right)
	{
		x /= right.x;
		y /= right.y;
		z /= right.z;
		return *this;
	}

	template<typename T>
	bool Vector3<T>::operator>(const Vector3& right)
	{
		return Magnitude() > right.Magnitude();
	}

	template<typename T>
	bool Vector3<T>::operator>=(const Vector3& right)
	{
		return Magnitude() >= right.Magnitude();
	}

	template<typename T>
	bool Vector3<T>::operator<(const Vector3& right)
	{
		return Magnitude() < right.Magnitude();
	}

	template<typename T>
	bool Vector3<T>::operator<=(const Vector3& right)
	{
		return Magnitude() <= right.Magnitude();
	}

	template<typename T>
	bool Vector3<T>::operator==(const Vector3& right)
	{
		return x == right.x && y == right.y && z == right.z;
	}

	template<typename T>
	bool Vector3<T>::operator!=(const Vector3& right)
	{
		return !(*this == right);
	}

	template<typename T>
	std::string operator+(const std::string& left, const Vector3<T>& right)
	{
		return left + "{" + std::to_string(right.x) + ", " + std::to_string(right.y) + ", " + std::to_string(right.z) + "}";
	}

	template<typename T>
	std::string operator+(const Vector3<T>& left, const std::string& right)
	{
		return "{" + std::to_string(left.x) + ", " + std::to_string(left.y) + ", " + std::to_string(left.z) + "}" + right;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector)
	{
		return os << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";
	}
}