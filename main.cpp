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
	int gameWidth = 1280;
	int gameHeight = 960;
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Flocking");
	Clock clock;
	VehicleSystem vs;
	float separate = 0;
	float align = 0;
	float cohision = 0;

	while (window.isOpen())
	{
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
				//else if (event.mouseButton.button == Mouse::Right)
				//{
				//	//separate += 10.0f;
				//	align++;
				//}
			}
			else if (event.type == Event::TextEntered)
			{
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					separate += 10.0f;
					//separate++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::S))
				{
					separate -= 10.0f;
					//separate--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::D))
				{
					align += 10.0f;
					//align++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::A))
				{
					align -= 10.0f;
					//align--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::C))
				{
					cohision += 10.0f;
					//cohision++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Z))
				{
					cohision -= 10.0f;
					//cohision--;
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