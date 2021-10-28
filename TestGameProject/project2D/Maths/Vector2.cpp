#include "Vector2.h"
#include <cmath>
#include <cassert>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{

}

Vector2::Vector2(float fX, float fY)
{
	x = fX;
	y = fY;
}

float Vector2::magnitude()
{
	//Pythag
	return sqrtf((x*x) + (y*y));
}
float Vector2::magnitudeSq()
{
	//Pythag without the square root
	return((x*x) + (y*y));
}

void Vector2::normalise()
{
	float mag = magnitude();
	//Prevent divide by zero error
	_STL_ASSERT(mag != 0.0f, "Normalise: Divide by Zero");
	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
	}
}

float Vector2::dot(const Vector2& rhs)
{
	return ( (x * rhs.x) + (y * rhs.y)  );
}

Vector2 Vector2::right()
{
	return Vector2(-y, x);
}

Vector2 Vector2::left()
{
	return Vector2(y,-x);
}

void Vector2::Truncate(float max)
{
	float sqrMag = magnitudeSq();
	if (sqrMag > (max * max))
	{
		//Calculate value to multiply x and y by
		float mult = max / sqrtf(sqrMag);
		
		x *= mult;
		y *= mult;
	}
}

float Vector2::Distance(Vector2 &vec2)
{
	//Return the distance between this vector and vec2
	return sqrt(((x - vec2.x) * (x - vec2.x)) + ((y - vec2.y) * (y - vec2.y)));
}

Vector2 Vector2::GetReflection()
{
	Vector2 v(-x, -y);
	return v;
}

bool Vector2::isZero()
{
	return((x == 0) && (y == 0));
}

Vector2 Vector2::Lerp(Vector2 v2Start, Vector2 v2End, float fT)
{
	return v2Start + (fT * (v2End - v2Start));
}

float Vector2::Lerp(float fStart, float fEnd, float fT)
{
	return fStart + (fT * (fEnd - fStart));
}


Vector2::operator float*()
{
	return &x;
}

Vector2 Vector2::Normalised()
{
	Vector2 vec = Vector2(x,y);
	vec.normalise();

	return vec;
}

float & Vector2::operator[](int index)
{
	if (index)
	{
		return y;
	}
	return x;

}

 Vector2 Vector2::operator+(const Vector2& vec)
{
	return (Vector2(x + vec.x, y + vec.y));
}

 Vector2 Vector2::operator-(const Vector2 &vec)
{
	return (Vector2(x - vec.x, y - vec.y));
}
 Vector2 Vector2::operator*(const Vector2 &vec)
{
	return (Vector2((x * vec.x), (y * vec.y)));
}
 Vector2 Vector2::operator/(const Vector2 &vec)
{
	return (Vector2(x / vec.x, y / vec.y));
}
 Vector2& Vector2::operator+=(const Vector2 &vec)
{
	x += vec.x; y += vec.y; return *this;
}
 Vector2& Vector2::operator-=(const Vector2 &vec)
{
	x -= vec.x; y -= vec.y; return *this;
}
 Vector2& Vector2::operator*=(const Vector2 &vec)
{
	x *= vec.x; y *= vec.y; return *this;
}
 Vector2& Vector2::operator/=(const Vector2 &vec)
{
	x /= vec.x; y /= vec.y; return *this;
}

 


bool Vector2::operator==(const Vector2 &vec)const
{
	if ((x == vec.x) && (y == vec.y))
		return true;
	else
		return false;
}
bool Vector2::operator!=(const Vector2 &vec)const
{
	if ((x == vec.x) && (y == vec.y))
		return false;
	else
		return true;
}

 Vector2 Vector2::operator+(const float f)
{
	return (Vector2((float)(x + f), (float)(y + f)));
}
 Vector2 Vector2::operator-(const float f)
{
	return (Vector2((float)(x - f), (float)(y - f)));
}
 Vector2 Vector2::operator*(const float f)
{
	return (Vector2((float)(x * f), (float)(y * f)));
}
 Vector2 Vector2::operator/(const float f)
{
	return (Vector2((float)(x / f), (float)(y / f)));
}
 Vector2 Vector2::operator+=(const float f)
{
	return (Vector2((float)(x += f), (float)(y += f)));
}
 Vector2 Vector2::operator-=(const float f)
{
	return (Vector2((float)(x -= f), (float)(y -= f)));
}
 Vector2 Vector2::operator*=(const float f)
{
	return (Vector2((float)(x *= f), (float)(y *= f)));
}
 Vector2 Vector2::operator/=(const float f)
{
	return (Vector2((float)(x /= f), (float)(y /= f)));
}


Vector2 operator+(float lhs, Vector2 rhs)
{
	return (Vector2((float)(rhs.x + lhs), (float)(rhs.y +lhs)));
}
Vector2 operator-(float lhs, Vector2 rhs)
{
	return (Vector2((float)(rhs.x - lhs), (float)(rhs.y -lhs)));
}
Vector2 operator/(float lhs, Vector2 rhs)
{
	return (Vector2((float)(rhs.x / lhs), (float)(rhs.y /lhs)));
}
Vector2 operator*(float lhs, Vector2 rhs)
{
	return (Vector2((float)(rhs.x * lhs), (float)(rhs.y *lhs)));
}