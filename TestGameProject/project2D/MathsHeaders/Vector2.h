#pragma once
class Vector2
{
public:
	//Variables

	float x;
	float y;

	//Functions

	Vector2(float x, float y);
	Vector2();
	~Vector2();


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
	float dot(const Vector2& rhs);

	//---------------------------------
	//right function
	//returns right perp vector
	//---------------------------------
	Vector2 right();

	//---------------------------------
	//left function
	//returns left perp vector
	//---------------------------------
	Vector2 left();

	//---------------------------------
	// Truncate function
	//If the magnitude is greater than the max, changes x and y, so that it has magnitude of max
	//---------------------------------
	void Truncate(float max);

	//---------------------------------
	//Distance function
	//returns the distance between vector and vec2
	//---------------------------------
	float Distance(Vector2 &vec2);
	
	//---------------------------------
	//Reflection function
	//returns a vector that is a reflection of the vector used on
	//---------------------------------
	Vector2 GetReflection();

	//---------------------------------
	//isZero Function
	//returns whether the function is zero or not
	//---------------------------------
	bool isZero();


	//---------------------------------
	//Lerp Function
	//Interpolation function for a Vector2
	//---------------------------------
	static Vector2 Lerp(Vector2 v2Start, Vector2 v2End, float fT);
	

	//---------------------------------
	//Lerp Function
	//Interpolation function for a float
	//---------------------------------
	static float Lerp(float fStart, float fEnd, float fT);
	
	//---------------------------------
	//Normalised Function
	//Normalises vector without changing it
	//---------------------------------
	Vector2 Normalised();
	

	//Operator Overloads
	//Other
	float& operator[](int index);
	operator float*();
	//Vectors
	 Vector2 operator+(const Vector2 &vec);
	 Vector2 operator-(const Vector2 &vec);
	 Vector2 operator*(const Vector2 &vec);
	 Vector2 operator/(const Vector2 &vec);

	 Vector2& operator+=(const Vector2 &vec);
	 Vector2& operator-=(const Vector2 &vec);
	 Vector2& operator*=(const Vector2 &vec);
	 Vector2& operator/=(const Vector2 &vec);

	//Floats
	 Vector2 operator+(const float f);
	 Vector2 operator-(const float f);
	 Vector2 operator*(const float f);
	 Vector2 operator/(const float f);
	 Vector2 operator+=(const float f);
	 Vector2 operator-=(const float f);
	 Vector2 operator*=(const float f);
	 Vector2 operator/=(const float f);
	
	//Comparison
	bool operator==(const Vector2 &vec)const;
	bool operator!=(const Vector2 &vec)const;



	
};
Vector2 operator+(float lhs, Vector2 rhs);
Vector2 operator-(float lhs, Vector2 rhs);
Vector2 operator/(float lhs, Vector2 rhs);
Vector2 operator*(float lhs, Vector2 rhs);

