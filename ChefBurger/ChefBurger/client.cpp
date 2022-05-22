//#include <SFML/Graphics.hpp>
#include <iostream>
#include "client.h"

using namespace std;
//using namespace sf;


Client::Client()
{
	//_texture.loadFromFile("ressources/Clients/client1_souriant.png");
	_posX = 0;
	_posY = 0;
	_width = 200;
	_height = 263;
	//_name = "client1";
}

Client::~Client()
{
	//_texture.loadFromFile("ressources/Clients/blanc.png");
	_posX = 0;
	_posY = 0;
	_width = 0;
	_height = 0;
	//_name = "";
}

int Client::getPosX() const
{
	return _posX;
}

int Client::getPosY() const
{
	return _posY;
}

int Client::getWidth() const
{
	return _width;
}

int Client::getHeight() const
{
	return _height;
}
/*
std::string Client::getName() const
{
	return _name;
}*/
/*
sf::Texture Client::getTexture() const
{
	return _texture;
}

sf::RectangleShape Client::getRetangle()
{
	return _retangle;
}
*/
void Client::setPosX(int x)
{
	_posX = x;
}

void Client::setPosY(int y)
{
	_posY = y;
}

void Client::setWidth(int w)
{
	_width = w;
}

void Client::setHeight(int h)
{
	_height = h;
}
/*
void Client::setName(std::string newName)
{
	_name = newName;
}*/
/*
void Client::setTexture(sf::Texture newTexture)
{
	_texture = newTexture;
}

void Client::setRetangle(sf::RectangleShape newRetangle)
{
	_retangle = newRetangle;
}
*/
/*
void Client::drawClient()
{


	_retangle.setTexture(&_texture);
	_retangle.setPosition(_posX, _posY);		//défini sa comptoir
	_retangle.setSize(Vector2f(_width, _height));	//défini ses dimensions
	//retangle.setFillColor(Color::White);
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


	textureclient.loadFromFile("ressources/Clients/client1_souriant.png");
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

			textureclient.loadFromFile("ressources/Clients/client1_colerique.png");
			Sprite client1Colerique;
			client1Colerique.setTexture(textureclient);
			client1Colerique.setPosition(j, 0);
			j += 800;
			elapsed = clock.restart();
		}

		

		window.clear();
		window.draw(fondEcran);
		window.draw(client1Souriant);
		//window.draw(client2Souriant);
		window.display();
	}
	return 0;

}
*/