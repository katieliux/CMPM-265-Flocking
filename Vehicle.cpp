#include "Vehicle.h"

Vehicle::Vehicle(Vector2f location)
{
	//location = (Vector2f)Mouse::getPosition();
	//velocity = Vector2f(0, 0);
	//acceleration = Vector2f(0, 0);
	this->location = location;
	this->velocity = Vector2f((rand() % 200 - 100) * 0.01f, (rand() % 200 - 100) * 0.01f);
	this->acceleration = Vector2f(0.0, 0.0);
	this->r = 10;
	this->maxSpeed = 0.1f;
	this->maxForce = 0.1f;

	weight[0] = 1.0f;
	weight[1] = 1.0f;
	weight[2] = 1.0f;

	triangle.setPointCount(3);
	triangle.setPoint(0, Vector2f(r, 0));
	triangle.setPoint(1, Vector2f(r * 0.5, r * 1.866));
	triangle.setPoint(2, Vector2f(r * 1.5, r * 1.866));
	triangle.setFillColor(Color::White);
	triangle.setOrigin(r, r);
	triangle.setPosition(location);
}

Vehicle::~Vehicle()
{
}

void Vehicle::update()
{
	boundaries();
	velocity += acceleration;
	Math::limit(velocity, maxSpeed);
	location += velocity;
	acceleration = Vector2f(0, 0);
	triangle.setPosition(location);
	//triangle.setRotation(atan2(velocity.x, -velocity.y) * 180 / 3.14f);
	triangle.setRotation(Math::rotation(velocity));
}

void Vehicle::boundaries()
{
	//if (triangle.getPosition().x < 10)
	//{
	//	triangle.setPosition(gameWidth - 10, triangle.getPosition().y);
	//}
	//if (triangle.getPosition().x > gameWidth - 10)
	//{
	//	triangle.setPosition(10, triangle.getPosition().y);
	//}
	//if (triangle.getPosition().y < 10)
	//{
	//	triangle.setPosition(triangle.getPosition().x, gameHeight - 10);
	//}
	//if (triangle.getPosition().y > gameHeight - 10)
	//{
	//	triangle.setPosition(triangle.getPosition().x, 10);
	//}

	Vector2f desired = Vector2f(0, 0);

	if (location.x < 10.0f) 
	{
		desired = Vector2f(maxSpeed, velocity.y);
	}
	else if (location.x > gameWidth - 10.0f) 
	{
		desired = Vector2f(-maxSpeed, velocity.y);
	}
	if (location.y < 10.0f) 
	{
		desired = Vector2f(velocity.x, maxSpeed);
	}
	else if (location .y > gameHeight - 10.0f) 
	{
		desired = Vector2f(velocity.x, -maxSpeed);
	}

	if (desired != Vector2f(0, 0)) 
	{
		desired = Math::normalize(desired);
		desired *= maxSpeed;
		Vector2f steer = desired - velocity;
		Math::limit(steer, maxForce);
		applyForce(steer);
	}
}

void Vehicle::applyForce(Vector2f steer)
{
	acceleration += steer;
}


void Vehicle::flock(vector<Vehicle*>* const v)
{
	Vector2f separate = Separation(v);
	Vector2f align = Alignment(v);
	Vector2f cohision = Cohision(v);

	separate *= weight[0];
	align *= weight[1];
	cohision *= weight[2];

	applyForce(separate);
	applyForce(align);
	applyForce(cohision);
}

Vector2f Vehicle::Seek(Vector2f target)
{
	Vector2f desired = target - location;
	desired = Math::normalize(desired);
	desired *= maxSpeed;

	Vector2f steer = desired - velocity;
	Math::limit(steer, maxForce);
	return steer;
}

Vector2f Vehicle::Separation(vector<Vehicle*>* const v)
{
	float distance = 50.0f;
	Vector2f steer = Vector2f(0, 0);
	int count = 0;
	for (Vehicle *other : *v) 
	{
		float d = Math::magnitude(this->location - other->location);
		if (d > 0 && d < distance) 
		{
			Vector2f dif = this->location - other->location;
			dif = Math::normalize(dif);
			dif /= d;
			steer += dif;
			count++; 
		}
	}
	if (count > 0) 
	{
		steer /= count * 1.0f;
	}

	if (Math::magnitude(steer) > 0) 
	{
		steer = Math::normalize(steer);
		steer *= maxSpeed;
		steer -= velocity;
		Math::limit(steer, maxForce);
	}
	return steer;
}

Vector2f Vehicle::Alignment(vector<Vehicle*>* const v)
{
		float distance = 50.0f;
		Vector2f sum = Vector2f(0, 0);
		int count = 0;
		for (auto *other : *v)
		{
			float d = Math::magnitude(this->location - other->location);
			if (d > 0 && d < distance)
			{
				sum += other->velocity;
				count++;
			}
		}
		if (count > 0)
		{
			sum /= count * 1.0f;
			sum = Math::normalize(sum);
			sum *= maxSpeed;
			Vector2f steer = sum - velocity;
			Math::limit(steer, maxForce);
			return steer;
		}
		else
		{
			return Vector2f(0, 0);
		}
}

Vector2f Vehicle::Cohision(vector<Vehicle*>* const v)
{
	float distance = 50.0f;
	Vector2f sum = Vector2f(0, 0);
	int count = 0;
	for (auto *other : *v)
	{
		float d = Math::magnitude(this->location - other->location);
		if (d > 0 && d < distance)
		{
			sum += other->location;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= count * 1.0f;
		return Seek(sum);
		//seek(sum);
	}
	else
	{
		return Vector2f(0, 0);
	}
}

Vector2f Vehicle::getPosition()
{
	return location;
}

Vector2f Vehicle::getVelocity()
{
	return velocity;
}

float Vehicle::getmaxSpeed()
{
	return maxSpeed;
}

void Vehicle::setSpeed(float speed)
{
	maxSpeed = speed;
}

void Vehicle::setWeight(float separate, float align, float cohision)
{
	weight[0] = separate;
	weight[1] = align;
	weight[2] = cohision;
}

//void Vehicle::seek(Vector2f target)
//{
//	location = triangle.getPosition();
//
//	Vector2f desired = Vector2f(0, 0);
//	if (Math::magnitude(target - location) > r)
//	{
//		desired = Math::normalize(target - location) * maxSpeed;
//		Vector2f steer = desired - velocity;
//		applyForce(steer);
//	}
//	else
//	{
//		desired *= Math::map(Math::magnitude(target - location), Vector2f(0, 0), Vector2f(r * 10, maxSpeed));
//	}
//}

//void Vehicle::draw(RenderWindow* window)
//{
//	window->draw(triangle);
//}

void Vehicle::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(triangle, states);
}