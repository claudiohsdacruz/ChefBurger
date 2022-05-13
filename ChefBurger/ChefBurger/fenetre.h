#pragma once

class Fenetre
{
private:
	int _width;
	int _height;
	std::string _name;
	std::string _color;
	sf::Texture _textureFenetre;
	sf::IntRect _rectSprite;
	
public:
	Fenetre();
	Fenetre(int w, int h);
	~Fenetre();

	int getWidth() const;
	int getHeight() const;
	std::string getName() const;
	std::string getColor() const;

	void setWidth(int w);
	void setHeight(int h);
	void setName(std::string newName);
	void setColor(std::string newColor);
};
