
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ingredient.h"


using namespace sf;
using namespace std;


Ingredient::Ingredient()
{
	_textureIngredients.loadFromFile("ressources/Ingredients/2Bun.png");

	_posX = 0;
	_posY = 0;
	_width = 200;
	_height = 150;

	for (int i = 0; i < 5; i++)
	{
		_ingredients[i].setPosition(_posX, _posY);
		_ingredients[i].setSize(Vector2f(_width, _height));
		_ingredients[i].setFillColor(Color::White);
	}
	_vecteurIngredients.push_back(_textureIngredients);
}


Ingredient::~Ingredient()
{
	_posX = 0;
	_posY = 0;
	_width = 0;
	_height = 0;
	_textureIngredients.loadFromFile("ressources/Ingredients/Blanc.png");

	for (int i = 0; i < 5; i++)
	{
		_ingredients[i].setPosition(_posX, _posY);
		_ingredients[i].setSize(Vector2f(_width, _width));
		_ingredients[i].setTexture(&_textureIngredients);
	}
}

void Ingredient::destructeurIngredientChoisi(int i, int width, int height)
{
	_ingredientsChoisi[i].setSize(Vector2f(width, height));
}

RectangleShape Ingredient::getIngredients2(int i)const
{
	return _ingredients2[i];
}

RectangleShape Ingredient::getIngredientsChoisis(int i)const
{
	return _ingredientsChoisi[i];
}

RectangleShape Ingredient::getIngredients(int i)const
{
	return _ingredients[i];
}

int Ingredient::getPos(int i)const
{
	return _pos.at(i);
}

int Ingredient::getPosSize()const
{
	return _pos.size();
}

int Ingredient::getPosX() const
{
	return _posX;
}

int Ingredient::getPosY() const
{
	return _posY;
}

void Ingredient::setPosX(int x)
{
	_posX = x;
}

void Ingredient::setPosY(int y)
{
	_posY = y;
}

void Ingredient::setIngredientChoisi(int x, int y, int i)
{
	_ingredientsChoisi[i].setPosition(x, y);
}


void Ingredient::ingredients()
{
	//insertion des ingredients dans le sprite
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
	_textureIngredients.loadFromFile("ressources/Ingredients/Fromage.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/1Bun.png");
	_vecteurIngredients.push_back(_textureIngredients);
	_textureIngredients.loadFromFile("ressources/Ingredients/Effacer.png");
	_vecteurIngredients.push_back(_textureIngredients);
}

void Ingredient::drawIngredients()
{
	ingredients();
	for (int i = 0; i < 14; i++)
	{
		_ingredientsChoisi[i].setSize(Vector2f(120, 90));
		_ingredientsChoisi[i].setTexture(&_vecteurIngredients.at(i));
	}
	dispositionIngredient();
}

void Ingredient::ingredientsAleatoires(int& index, int& index1, int& index2)
{
	do
	{
		index = indexAleatoire();
		index1 = indexAleatoire();
		index2 = indexAleatoire();
	} while (index == index1 || index == index2 || index2 == index1 || index2 == index || index1 == index2 || index1 == index);

	_ingredients[0].setPosition(1000, 390);
	_ingredients[0].setSize(Vector2f(120, 90));
	_ingredients[0].setTexture(&_vecteurIngredients.at(0));

	_ingredients[4].setPosition(1000, 185);
	_ingredients[4].setSize(Vector2f(120, 90));
	_ingredients[4].setTexture(&_vecteurIngredients.at(12));

	_ingredients[1].setTexture(&_vecteurIngredients.at(index));
	_ingredients[1].setPosition(1000, 245);
	_ingredients[1].setSize(Vector2f(120, 90));

	_ingredients[2].setTexture(&_vecteurIngredients.at(index1));
	_ingredients[2].setPosition(1000, 295);
	_ingredients[2].setSize(Vector2f(120, 90));

	_ingredients[3].setTexture(&_vecteurIngredients.at(index2));
	_ingredients[3].setPosition(1000, 345);
	_ingredients[3].setSize(Vector2f(120, 90));

}


int Ingredient::indexAleatoire()
{
	int index = 0;
	index = rand() % 10 + 2;
	return index;
}

void Ingredient::dispositionIngredient()
{
	float j = 100;
	float k = 100;
	for (int i = 0; i < 14; i++)
	{
		_ingredients2[i].setSize(Vector2f(120, 90));
		_ingredients2[i].setTexture(&_vecteurIngredients.at(i));
	}

	for (int i = 0; i < 14; i++)
	{
		_ingredients2[i].setPosition(j, 500);
		if (i >= 7)
		{
			_ingredients2[i].setPosition(k, 600);
			k += 160;

		}
		j += 160;
	}

}
