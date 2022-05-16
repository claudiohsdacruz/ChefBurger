#pragma once

class Client
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;
	std::string _name;
	sf::Texture _texture;
	sf::RectangleShape _retangle;

	sf::Texture textureclient;

public:
	Client();
	~Client();

	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;
	std::string getName() const;
	sf::Texture getTexture() const;
	sf::RectangleShape getRetangle();

	void setPosX(int x);
	void setPosY(int y);
	void setWidth(int w);
	void setHeight(int h);
	void setName(std::string newName);
	void setTexture(sf::Texture newTexture);
	void setRetangle(sf::RectangleShape newRetangle);

	void drawClient();

	int afficherClient();
};
