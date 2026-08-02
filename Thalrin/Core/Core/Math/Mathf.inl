namespace Core::Math
{
	template<typename T>
	T Mathf::Min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	T Mathf::Max(T a, T b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	T Mathf::Clamp(T value, T lower, T upper)
	{
		return Max(lower, Min(value, upper));
	}
}