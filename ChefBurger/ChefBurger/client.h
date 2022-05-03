#pragma once

class Client
{
private:
	sf::RectangleShape _client;
	sf::Texture _textureClient;
	sf::IntRect _rectSprite;
public:
	Client();
	~Client();
};
