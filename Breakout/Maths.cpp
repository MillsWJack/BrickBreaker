#include "Maths.h"

Maths::Maths()
{
}

Maths::~Maths()
{
}

//Takes a value and its scale and maps it to a new scale
float Maths::Map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (max2 - min2) * ((value - min1) / (max1 - min1));
}

//Converts degrees to radians
float Maths::DegreesToRadians(float degrees)
{
	return (m_PI / 180) * degrees;
}

//Gets random number between two limits
float Maths::Rand(float num1, float num2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = num2 - num1;
	float r = random * diff;
	return num1 + r;
}
