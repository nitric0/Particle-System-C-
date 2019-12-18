#include <Math.h>
#include <assert.h>
#include "Vect4d.h"
#include "Matrix.h"


void Matrix::setIdentMatrix()
{ // initialize to the identity matrix
	m0 = m5 = m10 = m15 = 1.0f;
}

void Matrix::setTransMatrix(Vect4D *t)
{ // set the translation matrix (note: we are row major)
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;

	this->m12 = t->x;
	this->m13 = t->y;
	this->m14 = t->z;
	this->m15 = 1.0f;
}

void Matrix::set(MatrixRowEnum row, Vect4D *t)
{
	// initialize the rows of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		this->m0 = t->x;
		this->m1 = t->y;
		this->m2 = t->z;
		this->m3 = t->w;
		break;

	case MATRIX_ROW_1:
		this->m4 = t->x;
		this->m5 = t->y;
		this->m6 = t->z;
		this->m7 = t->w;
		break;

	case MATRIX_ROW_2:
		this->m8 = t->x;
		this->m9 = t->y;
		this->m10 = t->z;
		this->m11 = t->w;
		break;

	case MATRIX_ROW_3:
		this->m12 = t->x;
		this->m13 = t->y;
		this->m14 = t->z;
		this->m15 = t->w;
		break;

	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

//float &Matrix::operator[](INDEX_ENUM e)
//{
//	// get the individual elements
//	switch (e)
//	{
//	case 0:
//		return m0;
//		break;
//	case 1:
//		return m1;
//		break;
//	case 2:
//		return m2;
//		break;
//	case 3:
//		return m3;
//		break;
//	case 4:
//		return m4;
//		break;
//	case 5:
//		return m5;
//		break;
//	case 6:
//		return m6;
//		break;
//	case 7:
//		return m7;
//		break;
//	case 8:
//		return m8;
//		break;
//	case 9:
//		return m9;
//		break;
//	case 10:
//		return m10;
//		break;
//	case 11:
//		return m11;
//		break;
//	case 12:
//		return m12;
//		break;
//	case 13:
//		return m13;
//		break;
//	case 14:
//		return m14;
//		break;
//	case 15:
//		return m15;
//		break;
//	default:
//		assert(0);
//		return m0;
//		break;
//	}
//}


void Matrix::get(MatrixRowEnum row, Vect4D *t)
{ // get a row of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		t->x = this->m0;
		t->y = this->m1;
		t->z = this->m2;
		t->w = this->m3;
		break;

	case MATRIX_ROW_1:
		t->x = this->m4;
		t->y = this->m5;
		t->z = this->m6;
		t->w = this->m7;
		break;

	case MATRIX_ROW_2:
		t->x = this->m8;
		t->y = this->m9;
		t->z = this->m10;
		t->w = this->m11;
		break;

	case MATRIX_ROW_3:
		t->x = this->m12;
		t->y = this->m13;
		t->z = this->m14;
		t->w = this->m15;
		break;

	default:
		assert(0);
	}
}


//Matrix Matrix::operator*(Matrix& rhs)
//{ // matrix multiplications
//	Matrix tmp;
//
//	tmp.m0 = (m0*rhs.m0) + (m1*rhs.m4) + (m2*rhs.m8) + (m3*rhs.m12);
//	tmp.m1 = (m0*rhs.m1) + (m1*rhs.m5) + (m2*rhs.m9) + (m3*rhs.m13);
//	tmp.m2 = (m0*rhs.m2) + (m1*rhs.m6) + (m2*rhs.m10) + (m3*rhs.m14);
//	tmp.m3 = (m0*rhs.m3) + (m1*rhs.m7) + (m2*rhs.m11) + (m3*rhs.m15);
//
//	tmp.m4 = (m4*rhs.m0) + (m5*rhs.m4) + (m6*rhs.m8) + (m7*rhs.m12);
//	tmp.m5 = (m4*rhs.m1) + (m5*rhs.m5) + (m6*rhs.m9) + (m7*rhs.m13);
//	tmp.m6 = (m4*rhs.m2) + (m5*rhs.m6) + (m6*rhs.m10) + (m7*rhs.m14);
//	tmp.m7 = (m4*rhs.m3) + (m5*rhs.m7) + (m6*rhs.m11) + (m7*rhs.m15);
//
//	tmp.m8 = (m8*rhs.m0) + (m9*rhs.m4) + (m10*rhs.m8) + (m11*rhs.m12);
//	tmp.m9 = (m8*rhs.m1) + (m9*rhs.m5) + (m10*rhs.m9) + (m11*rhs.m13);
//	tmp.m10 = (m8*rhs.m2) + (m9*rhs.m6) + (m10*rhs.m10) + (m11*rhs.m14);
//	tmp.m11 = (m8*rhs.m3) + (m9*rhs.m7) + (m10*rhs.m11) + (m11*rhs.m15);
//
//	tmp.m12 = (m12*rhs.m0) + (m13*rhs.m4) + (m14*rhs.m8) + (m15*rhs.m12);
//	tmp.m13 = (m12*rhs.m1) + (m13*rhs.m5) + (m14*rhs.m9) + (m15*rhs.m13);
//	tmp.m14 = (m12*rhs.m2) + (m13*rhs.m6) + (m14*rhs.m10) + (m15*rhs.m14);
//	tmp.m15 = (m12*rhs.m3) + (m13*rhs.m7) + (m14 *rhs.m11) + (m15*rhs.m15);
//	return tmp;
//
//
//}

Matrix& Matrix::operator/=(float rhs)
{
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides

	m0 *= 1.0f / rhs;
	m1 *= 1.0f / rhs;
	m2 *= 1.0f / rhs;
	m3 *= 1.0f / rhs;
	m4 *= 1.0f / rhs;
	m5 *= 1.0f / rhs;
	m6 *= 1.0f / rhs;
	m7 *= 1.0f / rhs;
	m8 *= 1.0f / rhs;
	m9 *= 1.0f / rhs;
	m10 *= 1.0f / rhs;
	m11 *= 1.0f / rhs;
	m12 *= 1.0f / rhs;
	m13 *= 1.0f / rhs;
	m14 *= 1.0f / rhs;
	m15 *= 1.0f / rhs;

	return *this;
}

float Matrix::Determinant()
{
	return ((m0 * ((m5 * ((m10 * m15) - (m11 * m14))) - (m6 * ((m9 * m15) - (m11 * m13))) + (m7 * ((m9 * m14) - (m10 * m13)))))
		- (m1 * ((m4 * ((m10 * m15) - (m11 * m14))) - (m6 * ((m8 * m15) - (m11 * m12))) + (m7 * ((m8 * m14) - (m10 * m12)))))
		+ (m2 * ((m4 * ((m9 * m15) - (m11 * m13))) - (m5 * ((m8 * m15) - (m11 * m12))) + (m7 * ((m8 * m13) - (m9 *  m12)))))
		- (m3 * ((m4 * ((m9 * m14) - (m10 * m13))) - (m5 * ((m8 * m14) - (m10 * m12))) + (m6 * ((m8 * m13) - (m9 *  m12))))));

}

Matrix Matrix::GetAdjugate()
{


	Matrix tmp;

	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);

	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc))
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));

	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -((m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);

	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);

	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);

	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));

	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);

	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));

	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);

	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -((m0*t4) - (m1*t3) + (m3*t5));

	// unload	M		(4)		DL-FR
	// load		E		(5)		DLEFR
	t3 = (m5*m15) - (m7*m13);

	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);

	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);

	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);

	// d = -( b(tg) - c(th) + d(ti) )
	tmp.m3 = -((m1*t1) - (m2*t2) + (m3*t3));

	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);

	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);

	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);

	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));

	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);

	return tmp;
}

void Matrix::Inverse(Matrix &out)
{
	/*Matrix tmp;*/
	if (fabs(Determinant()) < 0.0001f)
	{
		// do nothing, Matrix is not invertable
	}
	else
	{
		out = GetAdjugate();
		out /= Determinant();
	}

	/*out = tmp;*/
}


void Matrix::setScaleMatrix(float scale)
{
	//	{	sx		0		0		0	}
	//	{	0		sy		0		0	}
	//	{	0		0		sz		0	}
	//	{	0		0		0		1	}

	this->m0 = scale;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = scale;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = scale;
	this->m11 = 0.0f;

	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 1.0f;
}

void Matrix::setRotZMatrix(float az)
{
	//	{	cos		-sin	0		0	}
	//	{	sin		cos		0		0	}
	//	{	0		0		1		0	}
	//	{	0		0		0		1	}

	/*Matrix tmp;*/
	this->m0 = cosf(az);
	this->m1 = -sinf(az);
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = sinf(az);
	this->m5 = cosf(az);
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;

	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 1.0f;

	/**this = tmp;*/
}

// End of file