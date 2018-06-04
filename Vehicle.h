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
#include "Math.h"

using namespace std;
using namespace sf;

class Vehicle: public Drawable, public Transformable
{
public:
	ConvexShape triangle;
	Vector2f location;
	Vector2f velocity;
	Vector2f acceleration;
	float maxSpeed;
	float maxForce;
	float r;
	float weight[3];
	int gameWidth;
	int gameHeight;

	Vehicle(Vector2f location);
	~Vehicle();

	void update();
	void applyForce(Vector2f steer);
	//void seek(Vector2f target);
	//void draw(RenderWindow* window);
	void boundaries();
	void flock(vector<Vehicle*>* const v);
	Vector2f Seek(Vector2f target);
	Vector2f Separation(vector<Vehicle*>* const v);
	Vector2f Alignment(vector<Vehicle*>* const v);
	Vector2f Cohision(vector<Vehicle*>* const v);
	void setWeight(float separate, float align, float cohision);
	virtual void draw(RenderTarget& target, RenderStates states) const;
};