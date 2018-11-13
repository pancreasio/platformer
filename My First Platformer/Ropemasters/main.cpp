#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <STP\TMXLoader.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "STP Example");
	tmx::TileMap map("res/caveTM.tmx");
	sf::Vector2f center = { 400.0f,300.0f };
	sf::View stdView({ center.x,center.y, 800.0f, 600.0f });
	stdView.setCenter(center.x,center.y);
	sf::Keyboard stdInput;
	map.ShowObjects(); // Display all the layer objects.

	//map.GetLayer("World").visible = false; // Hide a Layer named World

										   // Start the game loop
	while (window.isOpen()) {
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (stdInput.isKeyPressed(stdInput.A)) {
			center.x -= 2;
		}
		if (stdInput.isKeyPressed(stdInput.D)) {
			center.x += 2;
		}
		if (stdInput.isKeyPressed(stdInput.W)) {
			center.y -= 2;
		}
		if (stdInput.isKeyPressed(stdInput.S)) {
			center.y += 2;
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