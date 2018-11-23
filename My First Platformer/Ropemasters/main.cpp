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
	sf::Vector2f velocity = { 0.0f,0.0f };
	float gravity = 1900.0f, platformLimit = 150.0f;
	sf::View stdView({ center.x,center.y, 1200, 800 });
	stdView.setCenter(center.x,center.y);
	sf::Keyboard stdInput;
	sf::Clock clock;
	sf::Texture pjtex;
	sf::Sprite pj, tile;
	sf::Texture tile0;
	bool canJump = false, canLeft = false, canRight = false;
	map.ShowObjects(); // Display all the layer objects.

	//map.GetLayer("World").visible = false; // Hide a Layer named World
	pjtex.loadFromFile("res/pj.png");
	pj.setTexture(pjtex);
	pj.setPosition({center.x, center.y - 500});
	pj.scale(2, 2);
	tile0.loadFromFile("res/tile0.png");
	tile.setTexture(tile0);
	tile.setPosition({center.x +70,center.y});
	tile.scale(2, 2);

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
		
		   
		canRight = false;
		canLeft = true;

		if (stdInput.isKeyPressed(stdInput.A)&&center.x - stdView.getSize().x / 2 >0) {
			center.x -= 400* elapsed.asSeconds();
		}
		if (stdInput.isKeyPressed(stdInput.D)&& center.x + stdView.getSize().x /2 < map.GetWidth()*70) {
			center.x += 400* elapsed.asSeconds();
		}
		if (stdInput.isKeyPressed(stdInput.W)&& center.y - stdView.getSize().y /2 > 0) {
			center.y -= 400* elapsed.asSeconds();
		}
		if (stdInput.isKeyPressed(stdInput.S)&& center.y + stdView.getSize().y / 2 < map.GetHeight()*70) {
			center.y += 400 * elapsed.asSeconds();
		}
		stdView.setCenter(center.x, center.y);

		if (stdInput.isKeyPressed(stdInput.Right)) {
			velocity.x = 300;
		}
		if (stdInput.isKeyPressed(stdInput.Left)) {
			velocity.x = -300;
		}

		if (pj.getPosition().y + pj.getTexture()->getSize().y * pj.getScale().y < 665.0f) {
			velocity.y += gravity * elapsed.asSeconds();
		}
		else {
			velocity.y = 0.0f;
			canJump = true;
		}
		if (stdInput.isKeyPressed(stdInput.Up) && canJump) {
			velocity.y = -700;
			canJump = false;
		}

		if (pj.getGlobalBounds().intersects(tile.getGlobalBounds())) {
			if (pj.getPosition().y + pj.getTexture()->getSize().y * (pj.getScale().y- 0.02f) < tile.getPosition().y && tile.getPosition().x-platformLimit<pj.getPosition().x<tile.getPosition().x + tile.getScale().x * tile.getTexture()->getSize().x + platformLimit) {
				velocity.y = 0;
				pj.move({0.0f,-0.5f});
				canJump = true;
			}
			if (pj.getPosition().x < tile.getPosition().x) {
				velocity.x = 0;
				//pj.move({-0.5f,0.0f});
				
			}
		}
		
		pj.move({velocity.x * elapsed.asSeconds(),velocity.y * elapsed.asSeconds()});
		velocity.x = 0;

		// Clear screen
		window.clear();
		// Draw the map
		window.draw(map);
		window.draw(pj);
		window.draw(tile);
		// Update the window
		window.display();
		window.setView(stdView);
	}

	return EXIT_SUCCESS;
}