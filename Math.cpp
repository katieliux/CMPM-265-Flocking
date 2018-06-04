#include "Math.h"

Vector2f Math::normalize(Vector2f vector)
{
	if (vector.x * vector.x + vector.y * vector.y == 0)
		return vector;
	else
	{
		vector.x = vector.x / sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.y = vector.y / sqrtf(vector.x * vector.x + vector.y * vector.y);
		return vector;
	}
}

float Math::magnitude(Vector2f vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float Math::dotproduct(Vector2f v1, Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Math::map(float val, Vector2f min, Vector2f max)
{
	return min.y + ((max.y - min.y)*(val - min.x)) / (max.x - min.x);
}

void Math::limit(Vector2f &vector, float limit)
{
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector .y);

	if (magnitude > limit)
	{
		vector = vector / magnitude * limit;
	}
}