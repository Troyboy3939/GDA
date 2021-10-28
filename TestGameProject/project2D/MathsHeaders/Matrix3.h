#pragma once
#include "Vector3.h"
#include "Vector2.h"
class Matrix3
{
public:
	

	//--------------------------
	//Default Constructor
	//Sets the matrix to an identity matrix
	//--------------------------
	Matrix3();

	//--------------------------
	//Custom Constructor
	//Implement a custom matrix
	//--------------------------
	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

	//Operators
	Matrix3 operator*(const Matrix3& rhs);
	Vector3 operator*(const Vector3& rhs);
	Vector3& operator[](int index);
	operator float*();

	//Set Functions
	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void setPosition(float x, float y);
	void setPosition(Vector2 pos);
	void setScale(float x, float y);
	void setScale(Vector2 scale);

	//Get Functions

	//------------------------------------------
	//Get Position
	//returns the position that the matrix stores
	//------------------------------------------
	Vector2 getPosition();

	//------------------------------------------
	//Get Rotation
	//returns the Z-Rotation that the matrix stores
	//------------------------------------------
	float getRotationZ(); 

	//------------------------------------------
	//Get Scale
	//returns the scale that the matrix stores
	//------------------------------------------
	Vector2 getScale();

	//Variables



	//--------------------------
	// 0, 3, 6
	// 1, 4, 7
	// 2, 5, 8
	//--------------------------
	float m[9];
	float m_fRotation;
	Vector2 m_vScale;

};

