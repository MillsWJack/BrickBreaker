#pragma once
#include <stdlib.h>
#include <time.h>

const float m_PI = 3.14159;

class Maths
{
public:
	Maths();
	~Maths();

	static float Map(float value, float min1, float max1, float min2, float max2);
	static float DegreesToRadians(float degrees);
	static float Rand(float num1, float num2);
};

