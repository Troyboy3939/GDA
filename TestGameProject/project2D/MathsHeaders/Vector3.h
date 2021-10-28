#pragma once
class Vector3
{
public:
	//Variables

	float x;
	float y;
	float z;

	//functions

	Vector3();
	~Vector3();
	Vector3(float fX, float fY, float fZ);

	//---------------------------------
	//cross function
	//returns the cross product of vector and rhs
	//---------------------------------
	Vector3 cross(Vector3 rhs);

	//---------------------------------
	//Magnitude function
	//returns the length of the vector
	//---------------------------------
	float magnitude();

	//---------------------------------
	//magnitudeSq function
	//returns the square of the magnitude
	//---------------------------------
	float magnitudeSq();

	//---------------------------------
	//Normalise Function
	//normalises the vector
	//---------------------------------
	void normalise();

	//---------------------------------
	//dot function
	//returns the dot product of of this vector and rhs
	//---------------------------------
	float dot(const Vector3& rhs);


	//---------------------------------
	//Lerp Function
	//Interpolation function for a Vector3
	//---------------------------------
	static Vector3 Lerp(Vector3 v2Start, Vector3 v2End, float fT);


	//---------------------------------
	//Normalised Function
	//Normalises vector without changing it
	//---------------------------------
	Vector3 Normalised();

	//---------------------------------
	//Truncate
	//Clamps magnitude to fMax, returns a copy that is truncated to fMax
	//---------------------------------
	Vector3 Truncate(float fMax);


	//Operator Overloads
	//Other
	float& operator[](int index);
	operator float*();
	//Vectors
	const Vector3 operator+(const Vector3 &vec);
	const Vector3 operator-(const Vector3 &vec);
	const Vector3 operator*(const Vector3 &vec);
	const Vector3 operator/(const Vector3 &vec);

	const Vector3& operator+=(const Vector3 &vec);
	const Vector3& operator-=(const Vector3 &vec);
	const Vector3& operator*=(const Vector3 &vec);
	const Vector3& operator/=(const Vector3 &vec);

	//Floats
	const Vector3& operator+(const float &f);
	const Vector3& operator-(const float &f);
	const Vector3& operator*(const float &f);
	const Vector3& operator/(const float &f);
	const Vector3& operator+=(const float &f);
	const Vector3& operator-=(const float &f);
	const Vector3& operator*=(const float &f);
	const Vector3& operator/=(const float &f);

	//Comparison
	bool operator==(const Vector3 &vec)const;
	bool operator!=(const Vector3 &vec)const;

	//Assignment
	const Vector3& operator = (const float &f);

};
Vector3 operator*(float lhs, Vector3 rhs);

