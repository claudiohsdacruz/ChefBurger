#include <iostream>
#include <SFML/Graphics.hpp>

#include "ingredient.h"
#include "fenetre.h"
using namespace std;


Fenetre::Fenetre()
{
	_width = 40;
	_height = 40;
	_name = "Inconnu";
	_color = "White"; 
}

Fenetre::Fenetre(int w, int h)
{
	_width = 0;
	_height = 0;
	_name = "";
	_color = "White";
}

Fenetre::~Fenetre()
{
	_width = 0;
	_height = 0;
	_name = "Inconnu";
	_color = "Black";
}

int Fenetre::getWidth() const
{
	return _width;
}

int Fenetre::getHeight() const
{
	return _height;
}

std::string Fenetre::getName() const
{
	return _name;
}

std::string Fenetre::getColor() const
{
	return _color;
}

void Fenetre::setWidth(int w)
{
	_width = w;
}

void Fenetre::setHeight(int h)
{
	_height = h;
}

void Fenetre::setName(std::string newName)
{
	_name = newName;
}

void Fenetre::setColor(std::string newColor)
{
	_color = newColor;
}
