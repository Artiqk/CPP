#include "Snake.h"
#include "Fruit.h"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Snake Remastered", sf::Style::Close);
	window.setFramerateLimit(20);
	bool isEaten = false;
	Snake snake(&window);
	Fruit fruit(&window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}
		window.clear(sf::Color::White);
		snake.update(&isEaten);
		fruit.update(isEaten);
		window.display();
	}

	return 0;
}