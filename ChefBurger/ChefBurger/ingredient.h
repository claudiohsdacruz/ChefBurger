#pragma once

class Ingredients
{
private:
	sf::Texture _textureIngredients;
	sf::RectangleShape _ingredients[12];//Pour les ingredients aléatoires
	sf::RectangleShape _ingredients2[12];//Pour afficher les ingrédients sur lesquelles cliqués
	sf::RectangleShape _ingredientsChoisi[12];//Pour afficher les ingrédients cliqués par le joueur
	std::vector <sf::Texture> _vecteurIngredients;

public:
	Ingredients();
	~Ingredients();
	void ingredients();
	void drawIngredients();
	int ingredientAleatoire();
	void dispositionIngredient();
};