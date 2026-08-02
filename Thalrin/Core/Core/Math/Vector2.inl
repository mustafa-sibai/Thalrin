#include <cmath>
#include <string>
#include "Core/Math/Mathf.h"

namespace Core::Math
{
	template<typename T>
	Vector2<T>::Vector2() :
		x(0), y(0)
	{
	}

	template<typename T>
	Vector2<T>::Vector2(T value) :
		x(value), y(value)
	{
	}

	template<typename T>
	Vector2<T>::Vector2(T x, T y) :
		x(x), y(y)
	{
	}

	template<typename T>
	Vector2<T>::~Vector2()
	{
	}

	template<typename T>
	T Vector2<T>::Dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	template<typename T>
	T Vector2<T>::Distance(const Vector2& other) const
	{
		Vector2 d = Direction(other);
		return T(std::sqrt(d.x * d.x + d.y * d.y));
	}

	template<typename T>
	T Vector2<T>::Magnitude() const
	{
		return T(std::sqrt(Dot(*this)));
	}

	template<typename T>
	Vector2<T> Vector2<T>::Direction(const Vector2& other) const
	{
		return Vector2(std::abs(other.x - x), std::abs(other.y - y));
	}

	template<typename T>
	Vector2<T> Vector2<T>::Normalize() const
	{
		T length = Magnitude();

		if (length > 0)
			return Vector2(x / length, y / length);
		else
			return Vector2(0);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Center() const
	{
		return Vector2(x / 2, y / 2);
	}

	template<typename T>
	Vector2<T> Vector2<T>::Min()
	{
		return Vector2(Mathf::Min(x, y));
	}

	template<typename T>
	Vector2<T> Vector2<T>::Max()
	{
		return Vector2(Mathf::Max(x, y));
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2& right) const
	{
		return Vector2(x + right.x, y + right.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2& right) const
	{
		return Vector2(x - right.x, y - right.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(const Vector2& right) const
	{
		return Vector2(x * right.x, y * right.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(const Vector2& right) const
	{
		return Vector2(x / right.x, y / right.y);
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator*=(const Vector2& right)
	{
		x *= right.x;
		y *= right.y;
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator/=(const Vector2& right)
	{
		x /= right.x;
		y /= right.y;
		return *this;
	}

	template<class T>
	bool Vector2<T>::operator>(const Vector2& right) const
	{
		return Magnitude() > right.Magnitude();
	}

	template<class T>
	bool Vector2<T>::operator>=(const Vector2& right) const
	{
		return Magnitude() >= right.Magnitude();
	}

	template<typename T>
	bool Vector2<T>::operator<(const Vector2& right) const
	{
		return Magnitude() < right.Magnitude();
	}

	template<typename T>
	bool Vector2<T>::operator<=(const Vector2& right) const
	{
		return Magnitude() <= right.Magnitude();
	}

	template<typename T>
	bool Vector2<T>::operator==(const Vector2& right) const
	{
		return x == right.x && y == right.y;
	}

	template<typename T>
	bool Vector2<T>::operator!=(const Vector2& right) const
	{
		return !(*this == right);
	}

	template<typename T>
	std::string operator+(const std::string& left, const Vector2<T>& right)
	{
		return left + "{" + std::to_string(right.x) + ", " + std::to_string(right.y) + "}";
	}

	template<typename T>
	std::string operator+(const Vector2<T>& left, const std::string& right)
	{
		return "{" + std::to_string(left.x) + ", " + std::to_string(left.y) + "}" + right;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector2<T>& right)
	{
		os << "(" << right.x << ", " << right.y << ")";
		return os;
	}
}