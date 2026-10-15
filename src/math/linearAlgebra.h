#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include <cstddef>
#include <cmath>

namespace MATH
{
	template<typename T>
	struct vec2
	{
		union { T x; T u; };
		union { T y; T v; };

		constexpr vec2() : x(T{}), y(T{}) {}
		constexpr vec2(T x, T y) : x(x), y(y) {}

		vec2<T> operator+(const vec2<T>& rhs) const {
			return vec2<T>(x + rhs.x, y + rhs.y);
		}

		vec2<T> operator-(const vec2<T>& rhs) const {
			return vec2<T>(x - rhs.x, y - rhs.y);
		}

		vec2<T> operator*(const vec2<T>& rhs) const {
			return vec2<T>(x * rhs.x, y * rhs.y);
		}

		vec2<T> operator*(const T& rhs) const {
			return vec2<T>(x * rhs, y * rhs);
		}

		vec2<T> operator/(const vec2<T>& rhs) const {
			return vec2<T>(x / rhs.x, y / rhs.y);
		}

		vec2<T> operator/(const T& rhs) const {
			return vec2<T>(x / rhs, y / rhs);
		}

		T& operator[](const size_t i)
		{
			return i == 0 ? x : y;
		}

		const T& operator[](const size_t i) const
		{
			return i == 0 ? x : y;
		}
	};

	using vec2f = MATH::vec2<float>;
	using vec2d = MATH::vec2<double>;
	using vec2i = MATH::vec2<int>;

	static_assert(sizeof(vec2<int>) == 2 * sizeof(int));
	static_assert(sizeof(vec2<float>) == 2 * sizeof(float));
	static_assert(sizeof(vec2<double>) == 2 * sizeof(double));

	template<typename T>
	struct vec3
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };

		constexpr vec3() : x(T{}), y(T{}), z(T{}) {}
		constexpr vec3(T x, T y, T z) : x(x), y(y), z(z) {}

		vec3<T> operator+(const vec3<T>& v) const {
			return vec3<T>(x + v.x, y + v.y, z + v.z);
		}

		vec3<T> operator-(const vec3<T>& v) const {
			return vec3<T>(x - v.x, y - v.y, z - v.z);
		}

		vec3<T> operator*(const vec3<T>& v) const {
			return vec3<T>(x * v.x, y * v.y, z * v.z);
		}

		vec3<T> operator*(const T& v) const {
			return vec3<T>(x * v, y * v, z * v);
		}

		vec3<T> operator/(const vec3<T>& v) const {
			return vec3<T>(x / v.x, y / v.y, z / v.z);
		}

		vec3<T> operator/(const T& v) const {
			return vec3<T>(x / v, y / v, z / v);
		}

		T& operator[](const size_t i)
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			default: return z;
			}
		}

		const T& operator[](const size_t i) const
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			default: return z;
			}
		}
	};

	using vec3f = MATH::vec3<float>;
	using vec3d = MATH::vec3<double>;
	using vec3i = MATH::vec3<int>;

	static_assert(sizeof(vec3<int>) == 3 * sizeof(int));
	static_assert(sizeof(vec3<float>) == 3 * sizeof(float));
	static_assert(sizeof(vec3<double>) == 3 * sizeof(double));

	template<typename T>
	struct vec4
	{
		union { T w; T r; };
		union { T x; T g; };
		union { T y; T b; };
		union { T z; T a; };

		constexpr vec4() : w(T{}), x(T{}), y(T{}), z(T{}) {}
		constexpr vec4(T, w,T x, T y, T z) : w(w), x(x), y(y), z(z) {}

		vec4<T> operator+(const vec4<T>& v) const {
			return vec4<T>(w + v.w, x + v.x, y + v.y, z + v.z);
		}

		vec4<T> operator-(const vec4<T>& v) const {
			return vec3<T>(w - v.w, x - v.x, y - v.y, z - v.z);
		}

		vec4<T> operator*(const vec4<T>& v) const {
			return vec3<T>(w * v.w, x * v.x, y * v.y, z * v.z);
		}

		vec4<T> operator*(const T& v) const {
			return vec4<T>(w * v, x * v, y * v, z * v);
		}

		vec4<T> operator/(const vec4<T>& v) const {
			return vec4<T>(w / v.w, x / v.x, y / v.y, z / v.z);
		}

		vec4<T> operator/(const T& v) const {
			return vec4<T>(w / v, x / v, y / v, z / v);
		}

		T& operator[](const size_t i)
		{
			switch (i)
			{
			case 0: return w;
			case 1: return x;
			case 2: return y;
			default: return z;
			}
		}

		const T& operator[](const size_t i) const
		{
			switch (i)
			{
			case 0: return w;
			case 1: return x;
			case 2: return y;
			default: return z;
			}
		}
	};

	using vec4f = MATH::vec4<float>;
	using vec4d = MATH::vec4<double>;
	using vec4i = MATH::vec4<int>;

	static_assert(sizeof(vec4<int>) == 4 * sizeof(int));
	static_assert(sizeof(vec4<float>) == 4 * sizeof(float));
	static_assert(sizeof(vec4<double>) == 4 * sizeof(double));

	template<typename T>
	inline constexpr T dot(const vec2<T>& v1, const vec2<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	template<typename T>
	inline constexpr vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2)
	{
		return vec3(((v1.y * v2.z) - (v1.z * v2.y)), ((v1.z * v2.x) - (v1.x * v2.z)), ((v1.x * v2.y) - (v1.y * v2.x)));
	}

	template<typename T>
	inline constexpr float length(const vec2<T>& vec)
	{
		return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
	}

	template<typename T>
	inline constexpr float length(const vec3<T>& vec)
	{
		return std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}
}


#endif // !LINEARALGEBRA_H