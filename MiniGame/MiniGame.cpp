// MiniGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

unsigned SCREEN_WIDTH = 800;
unsigned SCREEN_HEIGHT = 600;

struct Car
{
	sf::Texture image;
	sf::Sprite car_sprite;
};

void HandleIvents(sf::RenderWindow &window)
{
	// Handle events
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Window closed: exit
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

int main()
{
	Car car;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Mini Game", sf::Style::Close, settings);
	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	if (!car.image.loadFromFile("resources/car-image.jpg"))
	{
		std::cout << "Car image not found";
		return 1;
	}

	car.car_sprite.setTexture(car.image);
	car.car_sprite.setOrigin(car.car_sprite.getTextureRect().left + car.car_sprite.getTextureRect().width / 2.0f,
	car.car_sprite.getTextureRect().top + car.car_sprite.getTextureRect().height);
	car.car_sprite.setPosition(windowCenter.x, windowCenter.y * 2 - 150);

	while (window.isOpen())
	{
		HandleIvents(window);
		window.clear();
		window.draw(car.car_sprite);
		window.display();
	}
    return 0;
}

