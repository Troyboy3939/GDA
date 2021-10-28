#pragma once
class Binary
{

public:
	//Convert binary to decimal integer
	static int binToDec(const char* binaryString);

	//Convert Decimal integer to binary
	static void decToBin(char* binaryString, int length, int value);


	static void setBit(char& bitfield, int bit, bool value);


	static bool checkBit(char& bitfield, int bit);

};