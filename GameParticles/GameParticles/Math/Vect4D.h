// Vect4D.h
//
// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h> 

// Foward Declarations
class Matrix;

// class
class __declspec(align(16)) Vect4D
{
public:
	friend class Matrix;

	Vect4D()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	};
	Vect4D(const Vect4D &t)
		:x(t.x), y(t.y), z(t.z), w(t.w)
	{

	}
	Vect4D &operator = (const Vect4D &tmp)
	{
		this->x = tmp.x;
		this->y = tmp.y;
		this->z = tmp.z;
		this->w = tmp.w;
		return *this;
	}
	~Vect4D()
	{
	}

	Vect4D(const __m128 &m)
		:_m(m)
	{
	}


	Vect4D(const float tx, const float ty, const float tz, const float tw = 1.0f)
		/*:x(tx), y(ty), z(tz), w(tw)*/
	{
		this->_m = _mm_set_ps(tw, tz, ty, tx);
	}


	void set(const float xVal, const float yVal, const float zVal, const float wVal = 1.0f)
	{
		/*this->x = xVal;
		this->y = yVal;
		this->z = zVal;
		this->w = wVal;*/
		this->_m = _mm_set_ps(wVal, zVal, yVal, xVal);
	}

	/*void *operator new(size_t size)
	{
		void *p = _aligned_malloc(size, 16);
		return p;
	}

	void *operator new[](size_t size)
	{
		void *p = _aligned_malloc(size, 16);
		return p;
	}

		void operator delete(void *p)
	{
		_aligned_free(p);
	}

	void operator delete[](void *p)
	{
		_aligned_free(p);
	}*/

	//Vect4D operator + (Vect4D t);
	//Vect4D & operator += (const Vect4D &t)
	//{
	//	this->x += t.x;
	//	this->y += t.y;
	//	this->z += t.z;
	//	this->w += t.w;
	//	return *this;
	//}
	//Vect4D operator - (Vect4D t);
	//Vect4D & operator -= (const Vect4D &t)
	//{
	//	this->x -= t.x;
	//	this->y -= t.y;
	//	this->z -= t.z;
	//	this->w -= t.w;
	//	return *this;
	//}

	Vect4D operator + (const Vect4D &tmp) const
	{
		return Vect4D(_mm_add_ps(this->_m, tmp._m));
	}

	Vect4D & operator += (const Vect4D &tmp)
	{

		this->_m = (_mm_add_ps(this->_m, tmp._m));
		return *this;
	}

	//Vect4D operator - (const Vect4D &tmp) const
	//{
	//	return Vect4D(_mm_sub_ps(this->_m, tmp._m));
	//}

	//Vect4D & operator -= (const Vect4D &tmp)
	//{
	//	this->_m = (_mm_sub_ps(this->_m, tmp._m));
	//	return *this;
	//}


	//Vect4D operator * (const Vect4D &tmp) const
	//{
	//	return Vect4D(_mm_mul_ps(this->_m, tmp._m));

	//}

	//Vect4D & operator *= (const Vect4D &tmp)
	//{
	//	this->_m = (_mm_mul_ps(this->_m, tmp._m));
	//	return *this;

	//}

	Vect4D operator * (const float scale) const
	{
		return Vect4D(_mm_mul_ps(this->_m, _mm_set1_ps(scale)));
	};

	void operator *= (const float scale)
	{
		this->_m = _mm_mul_ps(this->_m, _mm_set1_ps(scale));
	};

	//Vect4D operator * (float scale);
	//Vect4D &operator *= (const float scale)
	//{
	//	this->x *= scale;
	//	this->y *= scale;
	//	this->z *= scale;
	//	this->w *= scale;
	//	return *this;
	//}


	void Cross(Vect4D &vin, Vect4D &vout);
	float &operator[](VECT_ENUM e);
	void norm(Vect4D &out);


public:

	// anonymous union
	union
	{
		__declspec(align(16)) __m128	_m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};


#endif  //Vect4D.h
