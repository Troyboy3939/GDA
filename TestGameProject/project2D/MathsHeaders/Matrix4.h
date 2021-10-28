#pragma once
#include "Vector4.h"
#include "Vector3.h"
class Matrix4
{
public:

	//--------------------------
	//Default Constructor
	//Sets the matrix to an identity matrix
	//--------------------------
	Matrix4();

	//--------------------------
	//Custom Constructor
	//Implement a custom matrix
	//--------------------------
	Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);

	//Operators
	Matrix4 operator*(const Matrix4& rhs);
	Vector4 operator*(const Vector4& rhs);
	Vector4& operator[](int index);
	operator float*();

	//Set Functions

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void setPosition(float x, float y,float z);
	void setPosition(Vector3 pos);
	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);

	//Get Functions

	//------------------------------------------
	//Get Position
	//returns the position that the matrix stores
	//------------------------------------------
	Vector3 getPosition();

	//------------------------------------------
	//Get Rotation-X
	//returns the Rotation-X that the matrix stores
	//------------------------------------------
	float getRotationX();


	//------------------------------------------
	//Get Rotation-Y
	//returns the Rotation-Y that the matrix stores
	//------------------------------------------
	float getRotationY();


	//------------------------------------------
	//Get Rotation-Z
	//returns the Rotation-Z that the matrix stores
	//------------------------------------------
	float getRotationZ();

	//------------------------------------------
	//Get Rotation
	//returns the Rotation that the matrix stores
	//------------------------------------------
	Vector3 getRotation();

	//------------------------------------------
	//Get Scale
	//returns the Scale that the matrix stores
	//------------------------------------------
	Vector3 getScale();


	//Variables


	//--------------------------
	//0, 4, 8, 12,
	//1, 5, 9, 13,
	//2, 6, 10, 14,
	//3, 7, 11, 15
	//--------------------------
	float m[16];
	Vector3 m_rotation;
};

