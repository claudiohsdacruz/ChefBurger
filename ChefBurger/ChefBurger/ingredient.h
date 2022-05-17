#pragma once

class Ingredients
{
private:
	sf::Texture _textureIngredients;
	sf::RectangleShape _ingredients[12];//Pour les ingredients al�atoires
	sf::RectangleShape _ingredients2[12];//Pour afficher les ingr�dients sur lesquelles cliqu�s
	sf::RectangleShape _ingredientsChoisi[12];//Pour afficher les ingr�dients cliqu�s par le joueur
	std::vector <sf::Texture> _vecteurIngredients;

public:
	Ingredients();
	~Ingredients();
	void ingredients();
	void drawIngredients();
	int ingredientAleatoire();
	void dispositionIngredient();
};