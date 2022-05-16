
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ingredient.h"


using namespace sf;
using namespace std;

Ingredient::Ingredient()
{
	_texture.loadFromFile("ressources/Ingredients/Blanc.png");
	_posX = 0;
	_posY = 0;
	_width = 200;
	_height = 150;
	_name = "Bun_bas";
	
	/*
	_textureIngredients.loadFromFile("ressources/Ingredients/2 Bun.png");

	for (int i = 0; i < 13; i++)
	{
		_ingredients[i].setPosition(200, 150);
		_ingredients[i].setSize(Vector2f(100, 100));
		_ingredients[i].setFillColor(Color::White);
	}

	_vecteurIngredients.push_back(_textureIngredients);
	*/
}


Ingredient::~Ingredient()
{
	_texture.loadFromFile("ressources/Ingredients/blanc.png");
	_posX = 0;
	_posY = 0;
	_width = 0;
	_height = 0;
	_name = "";

	/*
	_textureIngredients.loadFromFile("");

	for (int i = 0; i < 13; i++)
	{
		_ingredients[i].setPosition(0, 0);
		_ingredients[i].setSize(Vector2f(0, 0));
		_ingredients[i].setTexture(&_textureIngredients);
	}
	*/
}

int Ingredient::getPosX() const
{
	return _posX;
}

int Ingredient::getPosY() const
{
	return _posY;
}

int Ingredient::getWidth() const
{
	return _width;
}

int Ingredient::getHeight() const
{
	return _height;
}

std::string Ingredient::getName() const
{
	return _name;
}

sf::Texture Ingredient::getTexture() const
{
	return _texture;
}

sf::RectangleShape Ingredient::getRetangle()
{
	return _retangle;
}

void Ingredient::setPosX(int x)
{
	_posX = x;
}

void Ingredient::setPosY(int y)
{
	_posY = y;
}

void Ingredient::setWidth(int w)
{
	_width = w;
}

void Ingredient::setHeight(int h)
{
	_height = h;
}

void Ingredient::setName(std::string newName)
{
	_name = newName;
}

void Ingredient::setTexture(sf::Texture newTexture)
{
	_texture = newTexture;
}

void Ingredient::setRetangle(sf::RectangleShape newRetangle)
{
	_retangle = newRetangle;
}

void Ingredient::drawIngredient()
{
	_retangle.setTexture(&_texture);
	_retangle.setPosition(_posX, _posY);		//défini sa comptoir
	_retangle.setSize(Vector2f(_width, _height));	//défini ses dimensions
	//retangle.setFillColor(Color::White);
}

/*
void Ingredients::ingredients()
{
	//insertion des ingredients dans le sprite
	_textureIngredients.loadFromFile("ressources/Ingredients/2 Bun.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Avocat.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Bacon.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Boeuf.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Cornichon.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Laitue.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Oeuf.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Oignon.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Poivron.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Tomate.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Viande.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/1 Bun.png");
	_vecteurIngredients.push_back(_textureIngredients);
}
*/

/*
void Ingredients::drawIngredients()
{
	int index = 0;
	int index1 = 0;
	int index2 = 0;

	Texture textureLocale;
	RenderWindow window(VideoMode(1280, 800), "Chef Ingredients");
	window.setFramerateLimit(60);

	RectangleShape arrierePlan;
	arrierePlan.setPosition(0, 0);		//défini sa comptoir
	arrierePlan.setSize(Vector2f(1280, 800));	//défini ses dimensions
	arrierePlan.setFillColor(Color::White);
	ingredients();

	do
	{
		index = ingredientAleatoire();
		index1 = ingredientAleatoire();
		index2 = ingredientAleatoire();
	} while (index == index1 || index == index2 || index2 == index1 || index2 == index || index1 == index2 || index1 == index);

	_ingredients[0].setPosition(0, 140);
	_ingredients[0].setSize(Vector2f(100, 100));
	_ingredients[0].setTexture(&_vecteurIngredients.at(0));

	_ingredients[12].setPosition(0, 0);
	_ingredients[12].setSize(Vector2f(100, 100));
	_ingredients[12].setTexture(&_vecteurIngredients.at(12));

	_ingredients[index].setTexture(&_vecteurIngredients.at(index));
	_ingredients[index].setPosition(0, 35);
	_ingredients[index].setSize(Vector2f(100, 100));

	_ingredients[index1].setTexture(&_vecteurIngredients.at(index1));
	_ingredients[index1].setPosition(0, 70);
	_ingredients[index1].setSize(Vector2f(100, 100));

	_ingredients[index2].setTexture(&_vecteurIngredients.at(index2));
	_ingredients[index2].setPosition(0, 105);
	_ingredients[index2].setSize(Vector2f(100, 100));


	while (window.isOpen())
	{
		Event Event; // inspecte les évenements

		while (window.pollEvent(Event))
		{
			if (Event.type == Event::Closed) // evenement : Fermeture demandée donc on ferme la fenêtre 
			{
				window.close();
			}
		}

		window.clear();
		window.draw(arrierePlan);
		window.draw(_ingredients[12]);
		window.draw(_ingredients[index]);
		window.draw(_ingredients[index1]);
		window.draw(_ingredients[index2]);
		window.draw(_ingredients[0]);
		window.display();
	}
	
}
*/

/*
int Ingredient::ingredientAleatoire()
{
	int index = 0;
	index = rand() % 10 + 2;
	return index;
}
*/