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
#include "Vehicle.h"
#include "VehicleSystem.h"
#include "Math.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1280, 960), "Flocking");
	Clock clock;

	float separate;
	float align;
	float cohision;

	VehicleSystem vs;

	while (window.isOpen())
	{
		separate = 0;
		align = 0;
		cohision = 0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					vs.addVehicle(Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					vs.removeVehicle();
				}
			}
			else if (event.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					separate += 10.0f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::S))
				{
					separate -= 10.0f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::D))
				{
					align += 10.0f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::A))
				{
					align -= 10.0f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::C))
				{
					cohision += 10.0f;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Z))
				{
					cohision -= 10.0f;
				}
			}
		}

		vs.setWeight(separate, align, cohision);
		vs.update();
		window.clear();
		window.draw(vs);
		window.display();
	}

	return 0;

}