////////////////////////////////////////////////////////////
// Headers:
// ctime for getting system time and
// cmath for sin and cos functions
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <iostream>
////////////////////////////////////////////////////////////
//Constants
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;
const float PI = 3.1415927f;
const float CLOCK_CIRCLE_SIZE = 250;
const float CENTER_CLOCK_CIRCLE_SIZE = 10;
const float CLOCK_CIRCLE_THICKNESS = 2;
const unsigned DOTS_NUMBER = 60;
const unsigned NUMBER_OF_DIGITS = 12;
////////////////////////////////////////////////////////////

/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
struct Clocks
{
	struct View
	{
		sf::Texture image;
		sf::Music sound;
		//sf::Texture brand;
		//sf::Sprite brandSprite;
		sf::Font font;
	} View;
	struct Mechanics
	{
		sf::Text number[NUMBER_OF_DIGITS];
		sf::CircleShape dot[DOTS_NUMBER];
		sf::CircleShape clockCircle;
		sf::CircleShape centerCircle;
	} Mechanics;
	struct Hands
	{
		sf::RectangleShape hourHand;
		sf::RectangleShape minuteHand;
		sf::RectangleShape secondsHand;
	} Hands;
};

sf::Vector2f GetPosition(float angle, int offset)
{
	return sf::Vector2f((CLOCK_CIRCLE_SIZE - offset) * cos(angle), (CLOCK_CIRCLE_SIZE - offset) * sin(angle));
}


void CreateDot(int i, sf::CircleShape dot[DOTS_NUMBER], const sf::Vector2f &windowCenter, sf::Vector2f &coordinates, float angle)
{
	sf::Vector2f dotPosition = GetPosition(angle, 10);
	dot[i].setFillColor(sf::Color::Green);
	dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
	dot[i].setPosition(coordinates.x + windowCenter.x, coordinates.y + windowCenter.y);
}

void CreateDigit(int i, Clocks &clock, float angle, const sf::Vector2f &windowCenter)
{
	int digit = i / 5;
	clock.Mechanics.number[digit].setFont(clock.View.font);
	clock.Mechanics.number[digit].setFillColor(sf::Color::Green);
	clock.Mechanics.number[digit].setStyle(sf::Text::Bold);
	clock.Mechanics.number[digit].setString(std::to_string(digit + 1));
	clock.Mechanics.number[digit].setCharacterSize(38);
	sf::Vector2f digitPosition = GetPosition(angle, 50);
	sf::Vector2f positionText(digitPosition + windowCenter);
	clock.Mechanics.number[digit].setPosition(positionText.x, positionText.y - clock.Mechanics.number[digit].getGlobalBounds().height / 2.0f);

	clock.Mechanics.number[digit].setOrigin(clock.Mechanics.number[digit].getGlobalBounds().width / 1.7f,
		clock.Mechanics.number[digit].getGlobalBounds().height / 5.0f);
}


void CreateClocksForeground(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	float angle = -1.047f;
	float x = 0;
	float y = 0;
	const float RADIUS_BIG_DOT = 7;
	for (int i = 0; i < DOTS_NUMBER; i++)
	{
		x = (CLOCK_CIRCLE_SIZE - 10) * cos(angle);
		y = (CLOCK_CIRCLE_SIZE - 10) * sin(angle);

		if (i % 5 == 0)
		{
			clocks.Mechanics.dot[i] = sf::CircleShape(3);
			CreateDigit(i, clocks, angle, windowCenter);
		}
		else
		{
			clocks.Mechanics.dot[i] = sf::CircleShape(1);
		}
		CreateDot(i, clocks.Mechanics.dot, windowCenter, sf::Vector2f(x,y), angle);
		angle = angle + ((2 * PI) / DOTS_NUMBER);
	}
}

bool LoadResources(Clocks &clock)
{
	if (!clock.View.image.loadFromFile("resources/clock-image3.jpg"))
	{
		std::cout << "Clock image not found";
		return false;
	}
	if (!clock.View.font.loadFromFile("resources/Oswald-Regular.ttf"))
	{
		std::cout << "Clock font not found";
		return false;
	}
	if (!clock.View.sound.openFromFile("resources/clock-1.wav"))
	{
		std::cout << "Clock sound not found";
		return false;
	}
	/*if (!clock.View.brand.loadFromFile("resources/clock-brand.png")))
	{
		std::cout << "Clock brand not found";
		return false;
	}*/
	return true;
}

void CreateOutline(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	clocks.Mechanics.clockCircle.setPointCount(100);
	clocks.Mechanics.clockCircle.setRadius(CLOCK_CIRCLE_SIZE);
	clocks.Mechanics.clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	clocks.Mechanics.clockCircle.setOutlineColor(sf::Color::Black);
	clocks.Mechanics.clockCircle.setOrigin(clocks.Mechanics.clockCircle.getGlobalBounds().width / 2, clocks.Mechanics.clockCircle.getGlobalBounds().height / 2);
	clocks.Mechanics.clockCircle.setPosition(windowCenter.x + CLOCK_CIRCLE_THICKNESS, windowCenter.y + CLOCK_CIRCLE_THICKNESS);
}

void CreateHands(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	clocks.Hands.hourHand.setSize(sf::Vector2f(7, 180));
	clocks.Hands.minuteHand.setSize(sf::Vector2f(5, 230));
	clocks.Hands.secondsHand.setSize(sf::Vector2f(2, 270));

	clocks.Hands.hourHand.setFillColor(sf::Color::Black);
	clocks.Hands.minuteHand.setFillColor(sf::Color::Black);
	clocks.Hands.secondsHand.setFillColor(sf::Color::Red);

	clocks.Hands.hourHand.setOrigin(clocks.Hands.hourHand.getGlobalBounds().width / 2, clocks.Hands.hourHand.getGlobalBounds().height - 25);
	clocks.Hands.minuteHand.setOrigin(clocks.Hands.minuteHand.getGlobalBounds().width / 2, clocks.Hands.minuteHand.getGlobalBounds().height - 25);
	clocks.Hands.secondsHand.setOrigin(clocks.Hands.secondsHand.getGlobalBounds().width / 2, clocks.Hands.secondsHand.getGlobalBounds().height - 25);

	clocks.Hands.hourHand.setPosition(windowCenter);
	clocks.Hands.minuteHand.setPosition(windowCenter);
	clocks.Hands.secondsHand.setPosition(windowCenter);
}

void CreateCenterCircle(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	clocks.Mechanics.centerCircle.setPointCount(100);
	clocks.Mechanics.centerCircle.setRadius(CENTER_CLOCK_CIRCLE_SIZE);
	clocks.Mechanics.centerCircle.setFillColor(sf::Color::Red);
	clocks.Mechanics.centerCircle.setOrigin(clocks.Mechanics.centerCircle.getGlobalBounds().width / 2, clocks.Mechanics.centerCircle.getGlobalBounds().height / 2);
	clocks.Mechanics.centerCircle.setPosition(windowCenter);
}

/*void Createbrand(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	clocks.View.brandSprite.setTexture(clocks.View.brand);
	clocks.View.brandSprite.setOrigin(clocks.View.brandSprite.getTextureRect().left + clocks.View.brandSprite.getTextureRect().width / 2.0f,
	clocks.View.brandSprite.getTextureRect().top + clocks.View.brandSprite.getTextureRect().height);
	clocks.View.brandSprite.setPosition(windowCenter.x, windowCenter.y * 2 - 150);
}*/

void PlaySound(Clocks &clocks)
{

	clocks.View.sound.setLoop(true);
	clocks.View.sound.play();
}

void Initiateimage(Clocks &clocks)
{
	clocks.Mechanics.clockCircle.setTexture(&clocks.View.image);
	clocks.Mechanics.clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));
}

void Preparation(Clocks &clocks, const sf::Vector2f &windowCenter)
{
	// Create a list for clock's dots
	// Create dots and place them to very right positions
	CreateClocksForeground(clocks, windowCenter);
	// Create outline of the clock
	CreateOutline(clocks, windowCenter);
	// Create clock background
	Initiateimage(clocks);
	// Play clock sound
	PlaySound(clocks);
	// Crate another circle for center
	CreateCenterCircle(clocks, windowCenter);
	// Create hour, minute, and seconds hands
	CreateHands(clocks, windowCenter);
	// Create Clock Brand 
	//Createbrand(clocks, windowCenter);
}

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

void SetRotation(Clocks &clocks, tm *ptm)
{
	clocks.Hands.hourHand.setRotation(ptm->tm_hour * 30.0f + (ptm->tm_min / 2.0f));
	clocks.Hands.minuteHand.setRotation(ptm->tm_min * 6.0f + (ptm->tm_sec / 12.0f));
	clocks.Hands.secondsHand.setRotation(ptm->tm_sec * 6.0f);
}

void DrawAllParts(Clocks &clocks, sf::RenderWindow &window)
{
	// Draw all parts of clock
	window.draw(clocks.Mechanics.clockCircle);
	std::cout << clocks.Mechanics.clockCircle.getPosition().x << "\n";

	for (int i = 0; i < DOTS_NUMBER; i++)
	{
		window.draw(clocks.Mechanics.number[i / 5]);
		window.draw(clocks.Mechanics.dot[i]);
	}

	//window.draw(clocks.View.brandSprite);
	window.draw(clocks.Hands.hourHand);
	window.draw(clocks.Hands.minuteHand);
	window.draw(clocks.Hands.secondsHand);
	window.draw(clocks.Mechanics.centerCircle);
}

void MainLoop(Clocks &clocks, sf::RenderWindow &window)
{
	while (window.isOpen())
	{

		HandleIvents(window);
		// Get system time
		std::time_t currentTime = std::time(NULL);

		struct tm * ptm = localtime(&currentTime);

		SetRotation(clocks, ptm);
		// Clear the window
		window.clear(sf::Color::White);

		DrawAllParts(clocks, window);
		// Display things on screen
		window.display();
	}
}

int main()
{
	// Define some variables
	float angle = 0.0;
	Clocks clocks;
	// Set multisampling level
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", sf::Style::Close, settings);

	// Define windowCenter which gets the center of the window here, right after creating window
	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	// Do initiate stuff
	if (LoadResources(clocks))
	{
		Preparation(clocks, windowCenter);
		// Do main loop
		MainLoop(clocks, window);
	}
	else
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}