/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: ingredient.h															*
* Date		: 22 mai 2022															*
* Description : La classe Ingredient est responsable pour créer l´élement			*
*				ingredient du jeu. 													*
************************************************************************************/

#pragma once
class Ingredient
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;
	std::string _name;
	sf::Texture _textureIngredients;
	sf::RectangleShape _ingredients[5];//Pour les ingredients aléatoires
	sf::RectangleShape _ingredients2[14];//Pour afficher les ingrédients sur lesquelles cliqués
	sf::RectangleShape _ingredientsChoisi[14];//Pour afficher les ingrédients cliqués par le joueur
	std::vector <sf::Texture> _vecteurIngredients;
	std::vector <int> _pos;


public:
	Ingredient();
	~Ingredient();

	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;
	int getPos(int i)const;
	int getPosSize()const;
	void setIngredientChoisi(int x, int y, int i);
	sf::RectangleShape getIngredients2(int i)const;
	sf::RectangleShape getIngredientsChoisis(int i)const;
	sf::RectangleShape getIngredients(int i)const;

	void setPosX(int x);
	void setPosY(int y);
	void setWidth(int w);
	void setHeight(int h);

	void ingredients();
	void drawIngredients();
	int indexAleatoire();
	void ingredientsAleatoires(int& index, int& index1, int& index2);
	void dispositionIngredient();
	void setSizeIngredientChoisi(int i, int x, int y);

};

