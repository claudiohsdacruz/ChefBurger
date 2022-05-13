#include <iostream>
#include <SFML/Graphics.hpp>

#include "client.h"
#include "burger.h"
#include "ingredient.h"
#include "fenetre.h"
#include "game.h"

using namespace sf;
using namespace std;

Game::Game()
{
	_score = 0;
	_time = 10000;
	_life = 3;
	_lose = false;
	_nomJoueur = "NomInconnu";
	//_ingredients = {};
	//_demande = {};
	_client = Client();
	_fenetre = Fenetre();
}

Game::~Game()
{
	_score = 0;
	_time = 0;
	_life = 0;
	_lose = true;
	_nomJoueur = "NomInconnu";
	//_ingredients = {};
	//_demande = {};
	_client.~Client();
	_fenetre.~Fenetre();
}

int Game::getScore() const
{
	return _score;
}

int Game::getTime() const
{
	return _time / 1000;
}

int Game::getLife() const
{
	return _life;
}

bool Game::getLose() const
{
	return _lose;
}

std::string Game::getNomJoueur() const
{
	return _nomJoueur;
}

Client Game::getClient() const
{
	return _client;
}

Fenetre Game::getFenetre() const
{
	return _fenetre;
}

void Game::setScore(int newScore)
{
	_score = newScore;
}

void Game::setTime(int newTime)
{
	_time = newTime * 1000;
}

void Game::setLife(int newLife)
{
	_life = newLife;
}

void Game::setLose(bool lose)
{
	_lose = lose;
}

void Game::setNomJoueur(std::string newNomJoueur)
{
	_nomJoueur = newNomJoueur;
}

void Game::setClient(Client newClient)
{
	_client = newClient;
}

void Game::setText(sf::Text& text)
{
	text.setCharacterSize(48);
	text.setString("Nom du jouer : ");
	text.setFillColor(sf::Color::Black);
}

void Game::initialiseWindow()
{
	sf::Font font;
	sf::Text text;
	
	RenderWindow window(VideoMode(1280, 800), "Chef Burger", Style::Close);
	Event event;
	bool affiche = false;
	
	RectangleShape fondEcran;
	vector<RectangleShape> ingredients;

	window.setVerticalSyncEnabled(true); // active la synchronisation verticale
	fondEcran.setSize(Vector2f(1280, 800));

	IntRect rectSprite(0, 0, 1280, 800);
	fondEcran.setTextureRect(rectSprite);
	Texture texture;

	if (!texture.loadFromFile("ressources/Menu.jpg"))
	{
		window.close();
	}
	fondEcran.setTexture(&texture);

	if (!font.loadFromFile("ressources/Lobster.ttf"))
	{
		window.close();
	}
	text.setFont(font);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					//std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (event.mouseButton.x > 235 && event.mouseButton.x < 445 && event.mouseButton.y > 510 && event.mouseButton.y < 725) {
						fondEcran.setTextureRect(rectSprite);
						if (!texture.loadFromFile("ressources/EnConstruction.jpg"))
						{
							window.close();
						}
						fondEcran.setTexture(&texture);
					}

					if (event.mouseButton.x > 505 && event.mouseButton.x < 775 && event.mouseButton.y > 510 && event.mouseButton.y < 775) {
						initialiseJeu();
						setText(text);
						if (!texture.loadFromFile("ressources/RestoInt.jpg"))
						{
							window.close();
						}
						fondEcran.setTexture(&texture);
					}

					if (event.mouseButton.x > 835 && event.mouseButton.x < 1045 && event.mouseButton.y > 510 && event.mouseButton.y < 725) {
						window.close();
					}
				}
			}
			
		}
		window.clear();
		window.draw(fondEcran);
		window.draw(text);
		window.display();
	}
}

void Game::initialiseJeu()
{
	_lose = false;
	_score = 0;
	_time = 0;
	_nomJoueur = demanderNomJoueur();

	//this->createDemande();
	//_demande.draw(cout);
	//this->createClient();
	//_client.draw(cout);

	//this->printScore(cout);
	//this->printTime(cout);
}

std::string Game::demanderNomJoueur()
{

	string joueur;
	cout << "Quel est le nom du joueur ? " << endl;
	cin >> joueur;

	return joueur;
}

void Game::play()
{
	initialiseWindow();
	
	//srand(time(NULL));
	//this->initialize(); //Initialise la Game(initialise le booléen, le score, le burger et le client)
	/*
	while (!_lose)
	{
		Burger burger = _burger.; //Prend la position de la tete du serpent
		Point a = _apple.getPoint(); //Prend la position de la pomme
		Point newPosition;

		do
		{
			this->inputKey(); //Saisit la touche
			newPosition = _snake.newPosition(_dir);
		} while (!this->canMove(newPosition));

		if (_dir != 0)
		{
			cout << _snake; //Initialise la prochaine position du Snake selon la direction

			if (_snake.ifCollision(p) || _snake.getHeadPosition().getX() == 39 || _snake.getHeadPosition().getX() == 0 ||
				_snake.getHeadPosition().getY() == 19 || _snake.getHeadPosition().getY() == 0)
			{
				_snake.deleteSnake();	//Efface le serpent
				_cptLive--;				//Diminue le nb de vie
				_snake.initialize(20, 10); //Inicialize une nouvelle serpent
				_plateau.draw(cout);	//Affiche le plateau du jeu
				_dir = 2;				//Initialise une direction
				this->printLive(cout); //Affiche le nb de vie
				if (_cptLive == 0)
				{
					this->endGame();	//finalise le jeu
				}
			}
			else if (p.getX() == a.getX() && p.getY() == a.getY())
			{
				_snake.eat(_dir); //Le snake mange une pomme(avance et allonge)
				_score++; //Augmente le score
				this->printScore(cout); //Affiche le score
				this->createApple(); //Génère une nouvelle pomme
			}
			else
			{
				_snake.move(_dir); //Le Snake avance à cette nouvelle position
			}

		}
	}
	*/

	this->printEndGame(cout); //Affiche la message de fin du jeu
}
/*
Burger Game::randIngredient() const
{
	return Burger();
}
*/
Client Game::randClient() const
{
	return Client();
}

void Game::endGame()
{
	_lose = true;
}

void Game::printScore(std::ostream& sortie) const
{
	/*
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 21);
	sortie << "Score : " << _score;
	*/
}

void Game::printLive(std::ostream& sortie) const
{
	/*
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 21);
	sortie << "Score : " << _score;
	*/
}

void Game::printTime(std::ostream& sortie) const
{
}

void Game::printEndGame(std::ostream& sortie) const
{
	/*
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 23);
	sortie << "GAME OVER!";
	*/
}
