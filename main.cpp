#include <iostream>
#include <SFML/Graphics.hpp>

#define PI 3.14
#define initAccel 0.9
#define damping 0.2
#define decSpeed 0.1

int main(){
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Car_Project", sf::Style::Default, settings);

	sf::RectangleShape rectangle(sf::Vector2f(25.f, 30.f));
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setOrigin(sf::Vector2f(12.5f, 15.f));
	rectangle.setPosition(sf::Vector2f(400, 300));

	sf::Vector2f Position;
	float Angle;
	float Speed = 0;
	float Acceleration = 0;

	// run the program as long as the window is open
	while (window.isOpen()){
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)){
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		Position = rectangle.getPosition();
		Angle = rectangle.getRotation();

		printf("Speed : %.2f\n", Speed);
		printf("Accel : %.2f\n", Acceleration);
		printf("Coordinate{x: %.2f  y: %.2f}\n", Position.x, Position.y);

		if (Speed > 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				Angle -= 1.0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				Angle += 1.0;
			}
		}
		else if (Speed < 0){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				Angle += 1.0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				Angle -= 1.0;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if (Speed > 0) {
				Acceleration = initAccel - (Speed * damping);
			}
			else {
				Acceleration = initAccel;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if (Speed < 0) {
				Acceleration = 0 - (initAccel + (Speed * damping));
			}
			else {
				Acceleration = 0 - initAccel;
			}
		}
		else {
			Acceleration = 0;
		}

		Speed += Acceleration;
		if (Speed > 0) {
			Speed -= decSpeed;
			if (Speed < 0) {
				Speed = 0;
			}
		}
		else if (Speed < 0) {
			Speed += decSpeed;
			if (Speed > 0) {
				Speed = 0;
			}
		}
		
		Position.x += Speed * sin(Angle * PI / 180.0);
		Position.y -= Speed * cos(Angle * PI / 180.0);

		if (Position.x > 800) {
			Position.x = 0;
		}
		else if (Position.x < 0){
			Position.x = 800;
		}

		if (Position.y > 600) {
			Position.y = 0;
		}
		else if (Position.y < 0) {
			Position.y = 600;
		}

		rectangle.setPosition(Position);
		rectangle.setRotation(Angle);
		
		window.draw(rectangle);
		window.display();
	}

	return 0;
}