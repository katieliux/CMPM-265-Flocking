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
#include <array>
#include "Vehicle.h"

using namespace std;
using namespace sf;

class VehicleSystem: public Drawable, public Transformable
{
public:
	//float r = 10.0f;
	int gameWidth;
	int gameHeight;
	int count;

	VehicleSystem();
	~VehicleSystem();

	vector<Vehicle*> v;
	void update();
	void addVehicle(Vector2f location);
	void removeVehicle();
	//void draw(RenderWindow* window);
	//void flock(RenderWindow* window, Vehicle& vehicle, vector<Vehicle*>* other);

	static const int COLUMNS = 10;
	static const int ROWS = 10;
	int gridWidth;
	int gridHeight;
	vector<Vehicle*>grid[ROWS][COLUMNS];
	Vector2i getBucket(Vector2f pos);
	void addBucket(Vector2i bucket, Vehicle* vehicle);
	void removeBucket(Vector2i bucket, Vehicle* vehicle);

	//void Seek(RenderWindow* window, Vehicle& vehicle);
	//void Separation(Vehicle& vehicle, vector<Vehicle*>* other);
	//void Alignment(Vehicle& vehicle, vector<Vehicle*>* other);
	//void Cohision(Vehicle& vehicle, vector<Vehicle*>* other);
	
	float weight[3];
	void setWeight(float separate, float align, float cohision);
	virtual void draw(RenderTarget& target, RenderStates states) const;
};