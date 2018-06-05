#include "VehicleSystem.h"

VehicleSystem::VehicleSystem()
{
	gameWidth = 1280;
	gameHeight = 960;
	weight[0] = 1.0f;
	weight[1] = 1.0f;
	weight[2] = 1.0f;
	this->count = 0;

	gridWidth = gameWidth / COLUMNS;
	gridHeight = gameHeight / ROWS;
}

VehicleSystem::~VehicleSystem()
{
	v.clear();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			grid[i][j].clear();
		}
	}
}

void VehicleSystem::update()
{
	for (auto vehicle : v)
	{
		Vector2i curBucket = getBucket(vehicle->getPosition());
		vehicle->update();
		Vector2i newBucket = getBucket(vehicle->getPosition());
		if (curBucket != newBucket)
		{
			removeBucket(curBucket, vehicle);
			addBucket(newBucket, vehicle);
		}
		//if (&grid[newBucket.x][newBucket.y] != nullptr)
		//{
		//	flock(window, vehicle, &grid[newBucket.x][newBucket.y]);
		//}
		vehicle->flock(&grid[newBucket.x][newBucket.y]);
	}
}

//void VehicleSystem::flock(RenderWindow* window, Vehicle& vehicle, vector<Vehicle*>* other)
//{

//}
//
//void VehicleSystem::draw(RenderWindow* window)
//{
//	for (auto vehicle: v)
//	{
//		window->draw(vehicle.triangle);
//	}
//}

void VehicleSystem::addVehicle(Vector2f location)
{
	Vehicle *vehicle = new Vehicle(location);
	v.push_back(vehicle);
	count++;
}

void VehicleSystem::removeVehicle()
{
	//if (v.size() >= 1)
	//{
	//	v.pop_back();
	//}
	if (count <= 0)
	{
		return;
	}
	else
	{
		v.pop_back();
		count--;
	}
}

//void VehicleSystem::Separation(Vehicle& vehicle, vector<Vehicle*>* other_v)
//{
//	float desiredSeparation = r * 5;
//	Vector2f sum;
//	int count = 0;
//	for (auto *other : *other_v)
//	{
//		float d = Math::magnitude(vehicle.location - other->location);
//		if (d > 0 && d < desiredSeparation)
//		{
//			Vector2f dif = Math::normalize(vehicle.location - other->location) / d;
//			sum += dif;
//			count++;
//		}
//	}
//	if (count > 0)
//	{
//		sum.x / count;
//		sum.y / count;
//		vehicle.applyForce(Math::normalize(sum) * vehicle.maxSpeed - vehicle.velocity);
//	}
//}
//
//void VehicleSystem::Alignment(Vehicle& vehicle, vector<Vehicle*>* other_v)
//{
//	float neighbor = 100.0f;
//	Vector2f sum;
//	int count = 0;
//	for (auto *other : *other_v)
//	{
//		float d = Math::magnitude(vehicle.location - other->location);
//		if (d > 0 && d < neighbor)
//		{
//			sum += other->velocity;
//			count++;
//		}
//	}
//	if (count > 0)
//	{
//		sum.x / count;
//		sum.y / count;
//		vehicle.applyForce(Math::normalize(sum)*vehicle.maxSpeed - vehicle.velocity);
//	}
//	else
//	{
//		vehicle.applyForce(Vector2f(0, 0));
//	}
//}
//
//void VehicleSystem::Cohision(Vehicle& vehicle, vector<Vehicle*>* other_v)
//{
//	float neighbor = 100.0f;
//	Vector2f sum;
//	int count = 0;
//	for (auto *other : *other_v)
//	{
//		float d = Math::magnitude(vehicle.location - other->location);
//		if (d > 0 && d < neighbor)
//		{
//			sum += other->location;
//			count++;
//		}
//	}
//	if (count > 0)
//	{
//		sum.x / count;
//		sum.y / count;
//		vehicle.seek(sum);
//	}
//	else
//	{
//		vehicle.applyForce(Vector2f(0, 0));
//	}
//}

Vector2i VehicleSystem::getBucket(Vector2f pos)
{
	return Vector2i(pos.x / gridWidth, pos.y / gridHeight);
}

void VehicleSystem::addBucket(Vector2i bucket, Vehicle* vehicle)
{
	grid[bucket.x][bucket.y].push_back(vehicle);
}

void VehicleSystem::removeBucket(Vector2i bucket, Vehicle* vehicle)
{
	auto i = find(grid[bucket.x][bucket.y].begin(), grid[bucket.x][bucket.y].end(), vehicle);
	if (i != grid[bucket.x][bucket.y].end())
	{
		grid[bucket.x][bucket.y].erase(i);
	}
}

void VehicleSystem::setWeight(float separate, float align, float cohision)
{
	weight[0] += separate;
	weight[1] += align;
	weight[2] += cohision;

	for (auto vehicle : v)
	{
		vehicle->setWeight(weight[0], weight[1], weight[2]);
	}
}

void VehicleSystem::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	for (auto vehicle: v)
	{
		target.draw(*vehicle, states);
	}
}