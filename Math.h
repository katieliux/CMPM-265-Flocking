#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <algorithm>
#include <vector>
#include<iostream>

using namespace std;
using namespace sf;

static class Math
{
public:
	Vector2f static normalize(Vector2f vector);
	float static magnitude(Vector2f vector);
	float static dotproduct(Vector2f v1, Vector2f v2);
	float static map(float val, Vector2f min, Vector2f max);
	void static limit(Vector2f &vector, float limit);
};