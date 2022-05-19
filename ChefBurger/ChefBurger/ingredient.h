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
	sf::RectangleShape _ingredients2[12];//Pour afficher les ingrédients sur lesquelles cliqués
	sf::RectangleShape _ingredientsChoisi[12];//Pour afficher les ingrédients cliqués par le joueur
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
	sf::RectangleShape getIngredients2(int i)const;
	sf::RectangleShape getIngredientsChoisis(int i)const;
	sf::RectangleShape getIngredients(int i)const;
	//std::string getName() const;
	//sf::Texture getTexture() const;
	//sf::RectangleShape getRetangle();

	void setPosX(int x);
	void setPosY(int y);
	void setWidth(int w);
	void setHeight(int h);
	//void setName(std::string newName);
	//void setTexture(sf::Texture newTexture);
	//void setRetangle(sf::RectangleShape newRetangle);

	//void drawIngredient();

	
	void ingredients();
	void drawIngredients(sf::RenderWindow &window);
	int indexAleatoire();
	void ingredientsAleatoires();
	void dispositionIngredient();
	
};