#pragma once

class Ingredients
{
private:
	sf::Texture _textureIngredients;
	sf::RectangleShape _ingredients[13];
	std::vector <sf::Texture> _vecteurIngredients;

public:
	Ingredients();
	~Ingredients();
	void ingredients();
	void drawIngredients();
	int ingredientAleatoire();
};