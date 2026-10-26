#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include <cstddef>
#include <cmath>
#include <iostream>

namespace MATH
{
	inline constexpr double PI = 3.14159265358979;

	template<typename T = float>
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

		friend std::ostream& operator<<(std::ostream& os, const vec2<T>& vec)
		{
			os << "x: " << vec.x << " y: " << vec.y << std::endl;
			return os;
		}
	};

	using dvec2 = MATH::vec2<double>;
	using ivec2 = MATH::vec2<int>;

	static_assert(sizeof(vec2<int>) == 2 * sizeof(int));
	static_assert(sizeof(vec2<float>) == 2 * sizeof(float));
	static_assert(sizeof(vec2<double>) == 2 * sizeof(double));

	template<typename T = float>
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

		friend std::ostream& operator<<(std::ostream& os, const vec3<T>& vec)
		{
			os << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
			return os;
		}
	};

	using dvec3 = MATH::vec3<double>;
	using ivec3 = MATH::vec3<int>;

	static_assert(sizeof(vec3<int>) == 3 * sizeof(int));
	static_assert(sizeof(vec3<float>) == 3 * sizeof(float));
	static_assert(sizeof(vec3<double>) == 3 * sizeof(double));

	template<typename T = float>
	struct vec4
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };
		union { T w; T a; };

		constexpr vec4() : x(T{}), y(T{}), z(T{}), w(T{}) {}
		constexpr vec4(T x,T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		vec4<T> operator+(const vec4<T>& v) const {
			return vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		vec4<T> operator-(const vec4<T>& v) const {
			return vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		vec4<T> operator*(const vec4<T>& v) const {
			return vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		vec4<T> operator*(const T& v) const {
			return vec4<T>(x * v, y * v, z * v, w * v);
		}

		vec4<T> operator/(const vec4<T>& v) const {
			return vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
		}

		vec4<T> operator/(const T& v) const {
			return vec4<T>(x / v, y / v, z / v, w / v);
		}

		T& operator[](const size_t i)
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: return w;
			}
		}

		const T& operator[](const size_t i) const
		{
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: return w;
			}
		}

		friend std::ostream& operator<<(std::ostream& os, const vec4<T>& vec)
		{
			os << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << " w: " << vec.w << std::endl;
			return os;
		}
	};

	using dvec4 = MATH::vec4<double>;
	using ivec4 = MATH::vec4<int>;

	static_assert(sizeof(vec4<int>) == 4 * sizeof(int));
	static_assert(sizeof(vec4<float>) == 4 * sizeof(float));
	static_assert(sizeof(vec4<double>) == 4 * sizeof(double));

	template<typename T>
	inline constexpr T dot(const vec2<T>& v1, const vec2<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	template<typename T>
	inline constexpr T dot(const vec3<T>& v1, const vec3<T>& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}

	template<typename T>
	inline constexpr vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2)
	{
		return vec3<T>(((v1.y * v2.z) - (v1.z * v2.y)), ((v1.z * v2.x) - (v1.x * v2.z)), ((v1.x * v2.y) - (v1.y * v2.x)));
	}

	template<typename T>
	inline constexpr T length(const vec2<T>& vec)
	{
		return std::sqrtl((vec.x * vec.x) + (vec.y * vec.y));
	}

	template<typename T>
	inline constexpr T length(const vec3<T>& vec)
	{
		return std::sqrtl((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}

	template<typename T>
	inline constexpr MATH::vec3<T> unitVector(const vec3<T>& vec)
	{
		return vec / length(vec);
	}

	template<typename T>
	MATH::vec3<T> normalize(const vec3<T>& vec)
	{
		T len = length(vec);
		return MATH::vec3<T>(vec.x / len, vec.y / len, vec.z / len);
	}
}

#endif // !LINEARALGEBRA_H