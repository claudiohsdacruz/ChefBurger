#pragma once

class Burger
{
private:
	sf::RectangleShape _burger;
	sf::Texture _textureBurger;
	sf::IntRect _rectSprite;
public:
	Burger();
	~Burger();
};
