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

//Converts radians to degrees
float Maths::RadiansToDegrees(float radians)
{
	return (180 / m_PI) * radians;
}
