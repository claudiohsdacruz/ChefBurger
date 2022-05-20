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
	sf::RectangleShape _ingredients[5];//Pour les ingredients al�atoires
	sf::RectangleShape _ingredients2[13];//Pour afficher les ingr�dients sur lesquelles cliqu�s
	sf::RectangleShape _ingredientsChoisi[13];//Pour afficher les ingr�dients cliqu�s par le joueur
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
	void ingredientsAleatoires();
	void dispositionIngredient();

};