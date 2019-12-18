#include <math.h>
#include "Vect4D.h"


void Vect4D::norm(Vect4D& out)
{
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);

	if (0.0f < mag)
	{
		out.x = this->x / mag;
		out.y = this->y / mag;
		out.z = this->z / mag;
		out.w = 1.0f;
	}
}

//Vect4D Vect4D::operator + (Vect4D t)
//{
//	return Vect4D(this->x + t.x, this->y + t.y, this->z + t.z);
//}
//
//Vect4D Vect4D::operator - (Vect4D t)
//{
//	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
//}
//
//Vect4D Vect4D::operator *(float scale)
//{
//
//	return Vect4D(this->x * scale, this->y * scale, this->z * scale);
//}

float& Vect4D::operator[](VECT_ENUM e)
{
	switch (e)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		//assert(0);
		return x;
	}
}

void Vect4D::Cross(Vect4D& vin, Vect4D& vout)
{
	vout.x = (y*vin.z - z * vin.y);
	vout.y = (z*vin.x - x * vin.z);
	vout.z = (x*vin.y - y * vin.x);
	vout.w = 1.0f;
}


// End of file