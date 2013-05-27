//
//  vector.h
//  TrinityCell
//
//  Created by he qianjun on 13-5-27.
//
//

#ifndef __TrinityCell__vec__
#define __TrinityCell__vec__

#include <cstdint>
#include <cmath>


template<typename T> struct Vector2_T;
template<typename T> struct Vector3_T;
template<typename T> struct Vector4_T;


template <typename T>
struct Vector2_T
{
	union {
		struct { T x, y; };
		struct { T w, h; };
		struct { T u, v; };
		T raw[2];
	};
	
	Vector2_T():x(0),y(0) {}
	explicit Vector2_T(T v):x(v), y(v) {}
	explicit Vector2_T(T x, T y):x(x), y(y) {}
	template<typename U>
	explicit Vector2_T(const Vector2_T<U> & v): x(v.x), y(v.y) {}
    
	bool operator==(const Vector2_T<T> &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
    
	bool operator!=(const Vector2_T<T> & rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}
	
	Vector2_T<T> operator+(const Vector2_T<T> & v) const
	{
		return Vector2_T(x + v.x, y + v.y);
	}
    
	Vector2_T<T> operator-(const Vector2_T<T> & v) const
	{
		return Vector2_T(x - v.x, y - v.y);
	}
    
	Vector2_T<T> operator-() const
	{
		return Vector2_T(-x, -y);
	}
    
	Vector2_T<T> operator*(T s) const
	{
		return Vector2_T(x*s, y*s);
	}
    
	Vector2_T<T> operator/(T s) const
	{
		s = 1/s;
		return Vector2_T(x * s, y * s);
	}
    
	Vector2_T<T>& operator+=(const Vector2_T<T> &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
    
	Vector2_T<T>& operator-=(const Vector2_T<T> &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
    
	Vector2_T<T>& operator*=(T s)
	{
		x *= s;
		y *= s;
		return *this;
	}
    
	Vector2_T<T> & operator/=(T s)
	{
		x /= s;
		y /= s;
		return *this;
	}
    
	float length() const
	{
		return std::sqrtf(x * x + y * y);
	}
    
	void normalize()
	{
		T s = length();
		x /= s;
		y /= s;
	}
};
    
typedef Vector2_T<int> Vector2i;
typedef Vector2_T<float> Vector2f;
    
template <typename T>
struct Vector3_T
{
    union {
        struct { T x, y, z;};
        struct { T u, v, w;};
        struct { T r, g, b;};
        T raw[3];
    };
    
    Vector3_T() : x(0), y(0), z(0) { }
    
    Vector3_T(T x, T y, T z)
    : x(x), y(y), z(z) { }
    
    explicit Vector3_T(T v)
    : x(v), y(v), z(v) { }
    
    explicit Vector3_T(const Vector4_T<T> & v)
    : x(v.x), y(v.y), z(v.z)
    {
        
    }
    
    template<typename U>
    explicit Vector3_T(const Vector3_T<U> & v)
    : x(v.x), y(v.y), z(v.z)
    {
        
    }
    
    bool operator ==(const Vector3_T<T> &v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    
    bool operator !=(const Vector3_T<T> &v) const
    {
        return x != v.x || y != v.y || z != v.z;
    }
    
    Vector3_T<T> operator +(const Vector3_T<T> &v) const
    {
        return Vector3_T(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3_T<T> operator -(const Vector3_T<T> &v) const
    {
        return Vector3_T(x -v.x, y - v.y, z - v.z);
    }
    
    Vector3_T<T> operator -() const
    {
        return Vector3_T(-x, -y, -z);
    }
    
    Vector3_T<T> operator *(T s) const
    {
        return Vector3_T(x*s, y*s, z*s);
    }
    
    Vector3_T<T> operator /(T s) const
    {
        return Vector3_T(x / s, y / s, z / s);
    }
    
    Vector3_T<T>& operator +=(const Vector3_T<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    Vector3_T<T>& operator -=(const Vector3_T<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    
    Vector3_T<T>& operator *=(const T &v)
    {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }
    
    Vector3_T<T>& operator /=(const T &v)
    {
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }
    
    T dot( const Vector3_T<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    
    float length() const 
    {
        return std::sqrtf(x * x + y * y + z * z);
    }
    
    bool normalize() 
    {
        T s = length();
        if(s == 0) 
            return false;
        x /= s;
        y /= s;
        z /= s;
        return true;
    }
    
    Vector3_T<T> cross(const Vector3_T<T> & v) const
    {
        return Vector3_T( y * v.z - z * v.y, z*v.x - x * v.z, x * v.y - y * v.x);
    }
};
    
typedef Vector3_T<int> 		Vector3i;
typedef Vector3_T<float> 	Vector3f;

template <typename T>
struct Vector4_T
{
    union
    {
        struct { T x, y, z, w;};
        struct { T r, g, b, a;};
        T raw[4];
    };
    
    Vector4_T() : x(0), y(0), z(0), w(0) { }
    Vector4_T(T x, T y, T z, T w): x(x), y(y), z(z), w(w) { }
};

typedef Vector4_T<int> 		Vector4i;
typedef Vector4_T<float> 	Vector4f;
typedef Vector4_T<uint8_t> 	Color;// r, g, b, a

#endif /* defined(__TrinityCell__vec__) */
