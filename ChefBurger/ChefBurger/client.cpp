/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: client.cpp															*
* Date		: 22 mai 2022															*
* Description : La classe Ingredient est responsable pour créer l´élement			*
*				ingredient du jeu. 													*
************************************************************************************/

#include <iostream>
#include "client.h"

using namespace std;


Client::Client()
{
	_posX = 0;
	_posY = 0;
	_width = 200;
	_height = 263;
}

Client::~Client()
{
	_posX = 0;
	_posY = 0;
	_width = 0;
	_height = 0;
}

int Client::getPosX() const
{
	return _posX;
}

int Client::getPosY() const
{
	return _posY;
}

int Client::getWidth() const
{
	return _width;
}

int Client::getHeight() const
{
	return _height;
}

void Client::setPosX(int x)
{
	_posX = x;
}

void Client::setPosY(int y)
{
	_posY = y;
}

void Client::setWidth(int w)
{
	_width = w;
}

void Client::setHeight(int h)
{
	_height = h;
}