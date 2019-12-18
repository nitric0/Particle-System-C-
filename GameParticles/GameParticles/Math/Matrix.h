#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"

// forward declare
class Vect4D;

// class
class __declspec(align(16)) Matrix
{
public:

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix()
		:m0(0.0f), m1(0.0f), m2(0.0f), m3(0.0f), m4(0.0f), m5(0.0f), m6(0.0f), m7(0.0f), m8(0.0f), m9(0.0f), m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f), m15(0.0f)
	{	// constructor for the matrix

	}

	//Matrix(float t0, float t1, float t2, float t3, float t4, float t5, float t6, float t7, float t8, float t9, float t10, float t11, float t12, float t13, float t14, float t15)
	//	: m0(t0), m1(t1), m2(t2), m3(t3), m4(t4), m5(t5), m6(t6), m7(t7), m8(t8), m9(t9), m10(t10), m11(t11), m12(t12), m13(t13), m14(t14), m15(t15)
	//{	// constructor for the matrix

	//}
	Matrix(Matrix& t)
		: m0(t.m0), m1(t.m1), m2(t.m2), m3(t.m3), m4(t.m4), m5(t.m5), m6(t.m6), m7(t.m7), m8(t.m8), m9(t.m9), m10(t.m10), m11(t.m11), m12(t.m12), m13(t.m13), m14(t.m14), m15(t.m15)
	{ // copy constructor

	}
	~Matrix()
	{

	}
	Matrix &operator=(const Matrix &tmp)
	{
		this->v0 = tmp.v0;
		this->v1 = tmp.v1;
		this->v2 = tmp.v2;
		this->v3 = tmp.v3;
		return *this;
	}

	Matrix(const Vect4D &tV0, const Vect4D &tV1, const Vect4D &tV2, const Vect4D &tV3)
		:v0(tV0), v1(tV1), v2(tV2), v3(tV3)
	{

	}


	//void *operator new(size_t size)
	//{
	//	void *p = _aligned_malloc(size, 16);
	//	return p;
	//}

	//void *operator new[](size_t size)
	//{
	//	void *p = _aligned_malloc(size, 16);
	//	return p;
	//}

	//	void operator delete(void *p)
	//{
	//	_aligned_free(p);
	//}

	//void operator delete[](void *p)
	//{
	//	_aligned_free(p);
	//} 

	void set(MatrixRowEnum row, Vect4D *t);
	void get(MatrixRowEnum row, Vect4D *vOut);

	void setIdentMatrix();
	void setTransMatrix(Vect4D *t);
	//void setScaleMatrix(Vect4D *s );
	void setScaleMatrix(float s);
	void setRotZMatrix(float Z_Radians);

	//float &operator[](INDEX_ENUM e);

	/*Matrix operator*(Matrix &t);*/

	float Determinant();

	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(float t);

	void Matrix::Inverse(Matrix &out);

public:

	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

struct M2M
{
	const Matrix &mat1;
	const Matrix &mat2;

	M2M(const Matrix &t1, const Matrix &t2)
		:mat1(t1), mat2(t2)
	{

	};

	operator Matrix()
	{
		Matrix Sum;
		__m128 tmp0;

		tmp0 = _mm_set1_ps(mat1.v0.x);
		Sum.v0._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v0.y);
		Sum.v0._m = _mm_add_ps(Sum.v0._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v0.z);
		Sum.v0._m = _mm_add_ps(Sum.v0._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v0.w);
		Sum.v0._m = _mm_add_ps(Sum.v0._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v1.x);
		Sum.v1._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v1.y);
		Sum.v1._m = _mm_add_ps(Sum.v1._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v1.z);
		Sum.v1._m = _mm_add_ps(Sum.v1._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v1.w);
		Sum.v1._m = _mm_add_ps(Sum.v1._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v2.x);
		Sum.v2._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v2.y);
		Sum.v2._m = _mm_add_ps(Sum.v2._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v2.z);
		Sum.v2._m = _mm_add_ps(Sum.v2._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v2.w);
		Sum.v2._m = _mm_add_ps(Sum.v2._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v3.x);
		Sum.v3._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v3.y);
		Sum.v3._m = _mm_add_ps(Sum.v3._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v3.z);
		Sum.v3._m = _mm_add_ps(Sum.v3._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v3.w);
		Sum.v3._m = _mm_add_ps(Sum.v3._m, _mm_mul_ps(tmp0, mat2.v3._m));

		return Sum;
	}

	const M2M & operator = (const M2M&) const = delete;
};

inline M2M operator * (const Matrix &a1, Matrix &a2)
{
	return M2M(a1, a2);
};

struct M2M2M
{
	const Matrix &mat1;
	const Matrix &mat2;
	Matrix &mat3;

	M2M2M(const M2M &t1, Matrix &t2)
		:mat1(t1.mat1), mat2(t1.mat2), mat3(t2)
	{

	};

	operator Matrix()
	{

	}

	const M2M2M & operator = (const M2M2M&) const = delete;
};

inline M2M2M operator * (const M2M &a1, Matrix &a2)
{
	return M2M2M(a1, a2);
};

struct M2M2M2M
{
	const Matrix &mat1;
	const Matrix &mat2;
	Matrix &mat3;
	Matrix &mat4;

	M2M2M2M(const M2M2M &t1, Matrix &t2)
		:mat1(t1.mat1), mat2(t1.mat2), mat3(t1.mat3), mat4(t2)
	{

	};

	operator Matrix()
	{

	}

	const M2M2M2M & operator = (const M2M2M2M&) const = delete;

};

inline M2M2M2M operator * (const M2M2M &a1, Matrix &a2)
{
	return M2M2M2M(a1, a2);
};


struct M2M2M2M2M
{
	const Matrix &mat1;
	const Matrix &mat2;
	Matrix &mat3;
	Matrix &mat4;
	Matrix &mat5;

	M2M2M2M2M(const M2M2M2M &t1, Matrix &t2)
		:mat1(t1.mat1), mat2(t1.mat2), mat3(t1.mat3), mat4(t1.mat4), mat5(t2)
	{

	};

	operator Matrix()
	{
		Matrix Sum1;
		__m128 tmp0;

		tmp0 = _mm_set1_ps(mat1.v0.x);
		Sum1.v0._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v0.y);
		Sum1.v0._m = _mm_add_ps(Sum1.v0._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v0.z);
		Sum1.v0._m = _mm_add_ps(Sum1.v0._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v0.w);
		Sum1.v0._m = _mm_add_ps(Sum1.v0._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v1.x);
		Sum1.v1._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v1.y);
		Sum1.v1._m = _mm_add_ps(Sum1.v1._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v1.z);
		Sum1.v1._m = _mm_add_ps(Sum1.v1._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v1.w);
		Sum1.v1._m = _mm_add_ps(Sum1.v1._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v2.x);
		Sum1.v2._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v2.y);
		Sum1.v2._m = _mm_add_ps(Sum1.v2._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v2.z);
		Sum1.v2._m = _mm_add_ps(Sum1.v2._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v2.w);
		Sum1.v2._m = _mm_add_ps(Sum1.v2._m, _mm_mul_ps(tmp0, mat2.v3._m));


		tmp0 = _mm_set1_ps(mat1.v3.x);
		Sum1.v3._m = _mm_mul_ps(tmp0, mat2.v0._m);

		tmp0 = _mm_set1_ps(mat1.v3.y);
		Sum1.v3._m = _mm_add_ps(Sum1.v3._m, _mm_mul_ps(tmp0, mat2.v1._m));

		tmp0 = _mm_set1_ps(mat1.v3.z);
		Sum1.v3._m = _mm_add_ps(Sum1.v3._m, _mm_mul_ps(tmp0, mat2.v2._m));

		tmp0 = _mm_set1_ps(mat1.v3.w);
		Sum1.v3._m = _mm_add_ps(Sum1.v3._m, _mm_mul_ps(tmp0, mat2.v3._m));

		Matrix Sum2;

		tmp0 = _mm_set1_ps(Sum1.v0.x);
		Sum2.v0._m = _mm_mul_ps(tmp0, mat3.v0._m);

		tmp0 = _mm_set1_ps(Sum1.v0.y);
		Sum2.v0._m = _mm_add_ps(Sum2.v0._m, _mm_mul_ps(tmp0, mat3.v1._m));

		tmp0 = _mm_set1_ps(Sum1.v0.z);
		Sum2.v0._m = _mm_add_ps(Sum2.v0._m, _mm_mul_ps(tmp0, mat3.v2._m));

		tmp0 = _mm_set1_ps(Sum1.v0.w);
		Sum2.v0._m = _mm_add_ps(Sum2.v0._m, _mm_mul_ps(tmp0, mat3.v3._m));


		tmp0 = _mm_set1_ps(Sum1.v1.x);
		Sum2.v1._m = _mm_mul_ps(tmp0, mat3.v0._m);

		tmp0 = _mm_set1_ps(Sum1.v1.y);
		Sum2.v1._m = _mm_add_ps(Sum2.v1._m, _mm_mul_ps(tmp0, mat3.v1._m));

		tmp0 = _mm_set1_ps(Sum1.v1.z);
		Sum2.v1._m = _mm_add_ps(Sum2.v1._m, _mm_mul_ps(tmp0, mat3.v2._m));

		tmp0 = _mm_set1_ps(Sum1.v1.w);
		Sum2.v1._m = _mm_add_ps(Sum2.v1._m, _mm_mul_ps(tmp0, mat3.v3._m));


		tmp0 = _mm_set1_ps(Sum1.v2.x);
		Sum2.v2._m = _mm_mul_ps(tmp0, mat3.v0._m);

		tmp0 = _mm_set1_ps(Sum1.v2.y);
		Sum2.v2._m = _mm_add_ps(Sum2.v2._m, _mm_mul_ps(tmp0, mat3.v1._m));

		tmp0 = _mm_set1_ps(Sum1.v2.z);
		Sum2.v2._m = _mm_add_ps(Sum2.v2._m, _mm_mul_ps(tmp0, mat3.v2._m));

		tmp0 = _mm_set1_ps(Sum1.v2.w);
		Sum2.v2._m = _mm_add_ps(Sum2.v2._m, _mm_mul_ps(tmp0, mat3.v3._m));


		tmp0 = _mm_set1_ps(Sum1.v3.x);
		Sum2.v3._m = _mm_mul_ps(tmp0, mat3.v0._m);

		tmp0 = _mm_set1_ps(Sum1.v3.y);
		Sum2.v3._m = _mm_add_ps(Sum2.v3._m, _mm_mul_ps(tmp0, mat3.v1._m));

		tmp0 = _mm_set1_ps(Sum1.v3.z);
		Sum2.v3._m = _mm_add_ps(Sum2.v3._m, _mm_mul_ps(tmp0, mat3.v2._m));

		tmp0 = _mm_set1_ps(Sum1.v3.w);
		Sum2.v3._m = _mm_add_ps(Sum2.v3._m, _mm_mul_ps(tmp0, mat3.v3._m));

		Matrix Sum3;

		tmp0 = _mm_set1_ps(Sum2.v0.x);
		Sum3.v0._m = _mm_mul_ps(tmp0, mat4.v0._m);

		tmp0 = _mm_set1_ps(Sum2.v0.y);
		Sum3.v0._m = _mm_add_ps(Sum3.v0._m, _mm_mul_ps(tmp0, mat4.v1._m));

		tmp0 = _mm_set1_ps(Sum2.v0.z);
		Sum3.v0._m = _mm_add_ps(Sum3.v0._m, _mm_mul_ps(tmp0, mat4.v2._m));

		tmp0 = _mm_set1_ps(Sum2.v0.w);
		Sum3.v0._m = _mm_add_ps(Sum3.v0._m, _mm_mul_ps(tmp0, mat4.v3._m));


		tmp0 = _mm_set1_ps(Sum2.v1.x);
		Sum3.v1._m = _mm_mul_ps(tmp0, mat4.v0._m);

		tmp0 = _mm_set1_ps(Sum2.v1.y);
		Sum3.v1._m = _mm_add_ps(Sum3.v1._m, _mm_mul_ps(tmp0, mat4.v1._m));

		tmp0 = _mm_set1_ps(Sum2.v1.z);
		Sum3.v1._m = _mm_add_ps(Sum3.v1._m, _mm_mul_ps(tmp0, mat4.v2._m));

		tmp0 = _mm_set1_ps(Sum2.v1.w);
		Sum3.v1._m = _mm_add_ps(Sum3.v1._m, _mm_mul_ps(tmp0, mat4.v3._m));


		tmp0 = _mm_set1_ps(Sum2.v2.x);
		Sum3.v2._m = _mm_mul_ps(tmp0, mat4.v0._m);

		tmp0 = _mm_set1_ps(Sum2.v2.y);
		Sum3.v2._m = _mm_add_ps(Sum3.v2._m, _mm_mul_ps(tmp0, mat4.v1._m));

		tmp0 = _mm_set1_ps(Sum2.v2.z);
		Sum3.v2._m = _mm_add_ps(Sum3.v2._m, _mm_mul_ps(tmp0, mat4.v2._m));

		tmp0 = _mm_set1_ps(Sum2.v2.w);
		Sum3.v2._m = _mm_add_ps(Sum3.v2._m, _mm_mul_ps(tmp0, mat4.v3._m));


		tmp0 = _mm_set1_ps(Sum2.v3.x);
		Sum3.v3._m = _mm_mul_ps(tmp0, mat4.v0._m);

		tmp0 = _mm_set1_ps(Sum2.v3.y);
		Sum3.v3._m = _mm_add_ps(Sum3.v3._m, _mm_mul_ps(tmp0, mat4.v1._m));

		tmp0 = _mm_set1_ps(Sum2.v3.z);
		Sum3.v3._m = _mm_add_ps(Sum3.v3._m, _mm_mul_ps(tmp0, mat4.v2._m));

		tmp0 = _mm_set1_ps(Sum2.v3.w);
		Sum3.v3._m = _mm_add_ps(Sum3.v3._m, _mm_mul_ps(tmp0, mat4.v3._m));

		Matrix Sum4;

		tmp0 = _mm_set1_ps(Sum3.v0.x);
		Sum4.v0._m = _mm_mul_ps(tmp0, mat5.v0._m);

		tmp0 = _mm_set1_ps(Sum3.v0.y);
		Sum4.v0._m = _mm_add_ps(Sum4.v0._m, _mm_mul_ps(tmp0, mat5.v1._m));

		tmp0 = _mm_set1_ps(Sum3.v0.z);
		Sum4.v0._m = _mm_add_ps(Sum4.v0._m, _mm_mul_ps(tmp0, mat5.v2._m));

		tmp0 = _mm_set1_ps(Sum3.v0.w);
		Sum4.v0._m = _mm_add_ps(Sum4.v0._m, _mm_mul_ps(tmp0, mat5.v3._m));


		tmp0 = _mm_set1_ps(Sum3.v1.x);
		Sum4.v1._m = _mm_mul_ps(tmp0, mat5.v0._m);

		tmp0 = _mm_set1_ps(Sum3.v1.y);
		Sum4.v1._m = _mm_add_ps(Sum4.v1._m, _mm_mul_ps(tmp0, mat5.v1._m));

		tmp0 = _mm_set1_ps(Sum3.v1.z);
		Sum4.v1._m = _mm_add_ps(Sum4.v1._m, _mm_mul_ps(tmp0, mat5.v2._m));

		tmp0 = _mm_set1_ps(Sum3.v1.w);
		Sum4.v1._m = _mm_add_ps(Sum4.v1._m, _mm_mul_ps(tmp0, mat5.v3._m));


		tmp0 = _mm_set1_ps(Sum3.v2.x);
		Sum4.v2._m = _mm_mul_ps(tmp0, mat5.v0._m);

		tmp0 = _mm_set1_ps(Sum3.v2.y);
		Sum4.v2._m = _mm_add_ps(Sum4.v2._m, _mm_mul_ps(tmp0, mat5.v1._m));

		tmp0 = _mm_set1_ps(Sum3.v2.z);
		Sum4.v2._m = _mm_add_ps(Sum4.v2._m, _mm_mul_ps(tmp0, mat5.v2._m));

		tmp0 = _mm_set1_ps(Sum3.v2.w);
		Sum4.v2._m = _mm_add_ps(Sum4.v2._m, _mm_mul_ps(tmp0, mat5.v3._m));


		tmp0 = _mm_set1_ps(Sum3.v3.x);
		Sum4.v3._m = _mm_mul_ps(tmp0, mat5.v0._m);

		tmp0 = _mm_set1_ps(Sum3.v3.y);
		Sum4.v3._m = _mm_add_ps(Sum4.v3._m, _mm_mul_ps(tmp0, mat5.v1._m));

		tmp0 = _mm_set1_ps(Sum3.v3.z);
		Sum4.v3._m = _mm_add_ps(Sum4.v3._m, _mm_mul_ps(tmp0, mat5.v2._m));

		tmp0 = _mm_set1_ps(Sum3.v3.w);
		Sum4.v3._m = _mm_add_ps(Sum4.v3._m, _mm_mul_ps(tmp0, mat5.v3._m));

		return Sum4;
	}

	const M2M2M2M2M & operator = (const M2M2M2M2M&) const = delete;
};

inline M2M2M2M2M operator * (const M2M2M2M &a1, Matrix &a2)
{
	return M2M2M2M2M(a1, a2);
};

#endif  // Matrix.h
