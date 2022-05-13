#include <SFML/Graphics.hpp>
#include <iostream>
#include "client.h"

using namespace std;
using namespace sf;


Client::Client()
{
}

Client::~Client()
{
}

int Client::afficherClient()
{
	RenderWindow window(VideoMode(800, 600), "Lost");
	Event event;
	RectangleShape fondEcran;

	window.setFramerateLimit(60);

	fondEcran.setSize(Vector2f(800, 600));
	fondEcran.setFillColor(Color::White);

	int j = 0;
	Clock clock;


	textureclient.loadFromFile("client/client1_souriant.png");
	Sprite client1Souriant;
	client1Souriant.setTexture(textureclient);
	client1Souriant.setPosition(0, 0);

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		Time elapsed = clock.getElapsedTime();
		elapsed.asSeconds();

		if (elapsed.asSeconds() >= 10)
		{
			cout << "allo";
			client1Souriant.setTexture(textureclient);
			client1Souriant.setPosition(j, 0);
			elapsed = clock.restart();

			textureclient.loadFromFile("client/client1_colerique.png");
			Sprite client1Colerique;
			client1Colerique.setTexture(textureclient);
			client1Colerique.setPosition(j, 0);
			j += 800;
			elapsed = clock.restart();
		}

		/*textureclient.loadFromFile("client/client2_souriant.png");
		Sprite client2Souriant;
		client2Souriant.setTexture(textureclient);
		client2Souriant.setPosition(0, 0);


		elapsed = clock.getElapsedTime();
		elapsed.asSeconds();

		if (elapsed.asSeconds() >= 15)
		{
			//cout << "allo";
			client2Souriant.setTexture(textureclient);
			client2Souriant.setPosition(j, 0);
			elapsed = clock.restart();

			textureclient.loadFromFile("client/client2_colerique.png");
			Sprite client2colerique;
			client2colerique.setTexture(textureclient);
			client2colerique.setPosition(j, 0);
			j += 800;
			elapsed = clock.restart();
		}*/



		window.clear();
		window.draw(fondEcran);
		window.draw(client1Souriant);
		//window.draw(client2Souriant);
		window.display();
	}
	return 0;

}