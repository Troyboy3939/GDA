#pragma once
class Vector4
{
	//Variables
public: 
	float x;
	float y;
	float z;
	float w;

	//functions

	//~Vector4();
	//Vector4();

	//---------------------------------
	//cross function
	//returns the cross product of vector and rhs
	//---------------------------------
	Vector4 cross(Vector4 rhs);

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
	//Lerp Function
	//Interpolation function for a Vector4
	//---------------------------------
	static Vector4 Lerp(Vector4 v2Start, Vector4 v2End, float fT);


	//---------------------------------
	//Normalised Function
	//Normalises vector without changing it
	//---------------------------------
	Vector4 Normalised();


	//---------------------------------
	//Truncate
	//Clamps magnitude to fMax, returns a copy that is truncated to fMax
	//---------------------------------
	Vector4 Truncate(float fMax);


	//---------------------------------
	//dot function
	//returns the dot product of of this vector and rhs
	//---------------------------------
	float dot(const Vector4& rhs);

public:
	Vector4(float X, float Y, float Z, float W);
	Vector4();
	~Vector4();

	//Operator Overloads
	//Other
	float& operator[](int index);
	operator float*();
	//Vectors
	const Vector4 operator+(const Vector4 &vec);
	const Vector4 operator-(const Vector4 &vec);
	const Vector4 operator*(const Vector4 &vec);
	const Vector4 operator/(const Vector4 &vec);

	const Vector4& operator+=(const Vector4 &vec);
	const Vector4& operator-=(const Vector4 &vec);
	const Vector4& operator*=(const Vector4 &vec);
	const Vector4& operator/=(const Vector4 &vec);

	//Floats
	const Vector4& operator+(const float &f);
	const Vector4& operator-(const float &f);
	const Vector4& operator*(const float &f);
	const Vector4& operator/(const float &f);
	const Vector4& operator+=(const float &f);
	const Vector4& operator-=(const float &f);
	const Vector4& operator*=(const float &f);
	const Vector4& operator/=(const float &f);

	//Comparison
	bool operator==(const Vector4 &vec)const;
	bool operator!=(const Vector4 &vec)const;

	//Assignment
	const Vector4& operator = (const float &f);

};
Vector4 operator*(float lhs, Vector4 rhs);

