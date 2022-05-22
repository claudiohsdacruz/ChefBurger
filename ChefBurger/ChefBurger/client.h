/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: client.h																*
* Date		: 22 mai 2022															*
* Description : La classe Client est responsable pour créer l´élement				*
*				client du jeu. 														*
************************************************************************************/
#pragma once

class Client
{
private:
	int _posX;
	int _posY;
	int _width;
	int _height;

public:
	Client();
	~Client();

	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;


	void setPosX(int x);
	void setPosY(int y);
	void setWidth(int w);
	void setHeight(int h);

};
