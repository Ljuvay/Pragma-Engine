#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

namespace MATH
{
	template<typename T>
	struct vec2
	{
		T x, y;
		T& u = x;
		T& v = y;

		vec2() : x(T{}), y(T{}) {}
		vec2(T x, T y) : x(x), y(y) {}

		vec2<T> operator+(const vec2<T>& v) const {
			return vec2<T>(x + v.x, y + v.y); 
		}

		vec2<T> operator-(const vec2<T>& v) const {
			return vec2<T>(x - v.x, y - v.y);
		}

		vec2<T> operator*(const vec2<T>& v) const {
			return vec2<T>(x * v.x, y * v.y);
		}

		vec2<T> operator*(const T& v) const {
			return vec2<T>(x * v, y * v);
		}

		vec2<T> operator/(const vec2<T>& v) const {
			return vec2<T>(x / v.x, y / v.y);
		}

		vec2<T> operator/(const T& v) const {
			return vec2<T>(x / v, y / v);
		}
		
	};

	template<typename T>
	struct vec3
	{
		T x, y, z ;
		T& r = x;
		T& g = y;
		T& b = z;

		vec3() : x(T{}), y(T{}), z(T{}) {}
		vec3(T x, T y, T z) : x(x), y(y), z(z) {}

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

	};
}


#endif // !LINEARALGEBRA_H