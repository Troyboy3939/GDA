#include "Vector3.h"
#include <cmath>



																  
Vector3::Vector3()												  
{																  
	x = 0;														  
	y = 0;														  
	z = 0;														  
}																  
																  
Vector3::Vector3(float X, float Y, float Z)						  
{
	x = X;
	y = Y;
	z = Z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::cross(Vector3 rhs)
{
	return Vector3((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x));
}

float Vector3::magnitude()
{
	return sqrtf((x*x) + (y*y) + (z * z));
}
float Vector3::magnitudeSq()
{
	return((x*x) + (y*y) + (z*z));
}

void Vector3::normalise()
{
	float mag = magnitude();
	_STL_ASSERT(mag != 0.0f, "Normalise: Divide by Zero");
	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

float Vector3::dot(const Vector3& rhs)
{
	return ( (x * rhs.x) + (y * rhs.y) + (z * rhs.z));
}

Vector3 Vector3::Lerp(Vector3 v2Start, Vector3 v2End, float fT)
{
	return v2Start + (fT * (v2End - v2Start));
}
Vector3 Vector3::Normalised()
{
	Vector3 vec = Vector3(x,y,z);
	vec.normalise();

	return vec;
}

Vector3 Vector3::Truncate(float fMax)
{
	float sqrMag = magnitudeSq();
	if (sqrMag > (fMax * fMax))
	{
		Vector3 vec = Vector3(x, y, z);
		//Calculate value to multiply x and y by
		float mult = fMax / sqrtf(sqrMag);

		vec.x *= mult;
		vec.y *= mult;
		vec.z *= mult;
		return vec;
	}

	return *this;
}


Vector3::operator float*()
{
	return &x;
}

float & Vector3::operator[](int index)
{
	if (index)
	{
		return y;
	}
	else if (index == 2)
	{
		return z;
	}
	return x;

}

const Vector3 Vector3::operator+(const Vector3 &vec)
{
	return (Vector3(x + vec.x, y + vec.y, (z + vec.z)));
}

const Vector3 Vector3::operator-(const Vector3 &vec)
{
	return (Vector3(x - vec.x, y - vec.y, (z - vec.z)));
}
const Vector3 Vector3::operator*(const Vector3 &vec)
{
	return (Vector3((x * vec.x), (y * vec.y), (z * vec.z)));
}
const Vector3 Vector3::operator/(const Vector3 &vec)
{
	return (Vector3(x / vec.x, y / vec.y, z / vec.z));
}
const Vector3& Vector3::operator+=(const Vector3 &vec)
{
	x += vec.x; y += vec.y; z += vec.z; return *this;
}
const Vector3& Vector3::operator-=(const Vector3 &vec)
{
	x -= vec.x; y -= vec.y;  z -= vec.z; return *this;
}
const Vector3& Vector3::operator*=(const Vector3 &vec)
{
	x *= vec.x; y *= vec.y;  z *= vec.z; return *this;
}
const Vector3& Vector3::operator/=(const Vector3 &vec)
{
	x /= vec.x; y /= vec.y;  z /= vec.z; return *this;
}



bool Vector3::operator==(const Vector3 &vec)const
{
	if ((x == vec.x) && (y == vec.y) && (z == vec.z))
		return true;
	else
		return false;
}
bool Vector3::operator!=(const Vector3 &vec)const
{
	if ((x == vec.x) && (y == vec.y))
		return false;
	else
		return true;
}

const Vector3& Vector3::operator+(const float &f)
{
	return (Vector3((float)(x + f), (float)(y + f), (float)(z + f)));
}
const Vector3& Vector3::operator-(const float &f)
{
	return (Vector3((float)(x - f), (float)(y - f), (float)(z - f)));
}
const Vector3& Vector3::operator*(const float &f)
{
	return (Vector3((float)(x * f), (float)(y * f), (float)(z * f)));
}
const Vector3& Vector3::operator/(const float &f)
{
	return (Vector3((float)(x / f), (float)(y / f), (float)(z / f)));
}
const Vector3& Vector3::operator+=(const float &f)
{
	return (Vector3((float)(x += f), (float)(y += f), (float)(z += f)));
}
const Vector3& Vector3::operator-=(const float &f)
{
	return (Vector3((float)(x -= f), (float)(y -= f), (float)(z -= f)));
}
const Vector3& Vector3::operator*=(const float &f)
{
	return (Vector3((float)(x *= f), (float)(y *= f), (float)(z *= f)));
}
const Vector3& Vector3::operator/=(const float &f)
{
	return (Vector3((float)(x /= f), (float)(y /= f), (float)(z /= f)));
}
const Vector3& Vector3::operator= (const float &f)
{
	return Vector3(f, f, f);
}

Vector3 operator+(float lhs, Vector3 rhs)
{
	return (Vector3((float)(rhs.x + lhs), (float)(rhs.y + lhs), (float)(rhs.z + lhs)));
}
Vector3 operator-(float lhs, Vector3 rhs)
{
	return (Vector3((float)(rhs.x - lhs), (float)(rhs.y - lhs), (float)(rhs.z - lhs)));
}
Vector3 operator/(float lhs, Vector3 rhs)
{
	return (Vector3((float)(rhs.x / lhs), (float)(rhs.y / lhs), (float)(rhs.z / lhs)));
}
Vector3 operator*(float lhs, Vector3 rhs)
{
	return (Vector3((float)(rhs.x * lhs), (float)(rhs.y * lhs), (float)(rhs.z * lhs)));
}

