#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <STP\TMXLoader.hpp>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "STP Example");
	tmx::TileMap map("res/caveTM.tmx");
	sf::Vector2f center = { 800.0f,600.0f };
	sf::View stdView({ center.x,center.y, 1200, 800 });
	stdView.setCenter(center.x,center.y);
	sf::Keyboard stdInput;
	sf::Clock clock;
	sf::RectangleShape p1;
	map.ShowObjects(); // Display all the layer objects.

	//map.GetLayer("World").visible = false; // Hide a Layer named World

										   // Start the game loop
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		   
		

		if (stdInput.isKeyPressed(stdInput.A)&&center.x - stdView.getSize().x / 2 >0) {
			center.x -= 10 * elapsed.asMilliseconds();
		}
		if (stdInput.isKeyPressed(stdInput.D)&& center.x + stdView.getSize().x /2 < map.GetWidth()*70) {
			center.x += 10 * elapsed.asMilliseconds();
		}
		if (stdInput.isKeyPressed(stdInput.W)&& center.y - stdView.getSize().y /2 > 0) {
			center.y -= 10 * elapsed.asMilliseconds();
		}
		if (stdInput.isKeyPressed(stdInput.S)&& center.y + stdView.getSize().y / 2 < map.GetHeight()*70) {
			center.y += 10 * elapsed.asMilliseconds();
		}
		stdView.setCenter(center.x, center.y);



		// Clear screen
		window.clear();
		// Draw the map
		window.draw(map);
		
		// Update the window
		window.display();
		window.setView(stdView);
	}

	return EXIT_SUCCESS;
}