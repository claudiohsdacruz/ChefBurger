// ChefBurger.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>

#include "client.h"
#include "burger.h"
#include "game.h"


using namespace sf;	//en mettant ce namespace, ça évite des sf::
using namespace std; //en mettant ce namespace, ça évite des std::

int main() {
	RenderWindow window(VideoMode(800, 600), "Lost");
	Event event;
	RectangleShape fondEcran;

	window.setFramerateLimit(60);

	fondEcran.setSize(Vector2f(800, 600));
	fondEcran.setFillColor(Color::White);

	

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(fondEcran);
		window.display();
	}

	return 0;
}
