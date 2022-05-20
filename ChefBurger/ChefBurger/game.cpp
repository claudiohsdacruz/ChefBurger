#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "client.h"
#include "burger.h"
#include "ingredient.h"
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
	_ligneScore = "";
	_ingredient = Ingredient();
	_clients = {};
	_client = Client();
}

Game::~Game()
{
	_score = 0;
	_time = 0;
	_life = 0;
	_lose = true;
	_nomJoueur = "";
	_ingredient.~Ingredient();
	//_demande = {};
	_client.~Client();
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

	sf::Music backgroundMusic;
	sf::Music gameplayMusic;

	sf::SoundBuffer buffer;
	buffer.loadFromFile("ressources/Audios/Click.ogg");

	sf::Sound clickSound;
	clickSound.setBuffer(buffer);

	Clock clock;
	Time elapsed;

	RenderWindow window(VideoMode(1280, 800), "Chef Burger", Style::Close);
	Event event;
	
	RectangleShape fondEcran;
	//RectangleShape demande;
	Sprite client;

	Texture textureClient;

	vector <int> _pos;
	int i = 0;
	bool toucher = false;
	float x = 450;
	float y = 400;

	window.setVerticalSyncEnabled(true); // active la synchronisation verticale
	fondEcran.setSize(Vector2f(1280, 800));
	IntRect rectFond(0, 0, 1208, 800);


	Texture texture;
	if (!texture.loadFromFile("ressources/Images/Menu.jpg"))
	{
		window.close();
	}
	fondEcran.setTexture(&texture);

	if (!font.loadFromFile("ressources/Polices/LuckiestGuy.ttf"))
	{
		window.close();
	}
	text.setFont(font);

	if (!backgroundMusic.openFromFile("ressources/Audios/MenuMusic.ogg"))
	{
		cout << "Erreur";
	}

	if (!gameplayMusic.openFromFile("ressources/Audios/gameMusic.ogg"))
	{
		cout << "Erreur";
	}


	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			
			elapsed = clock.getElapsedTime();
			elapsed.asSeconds();
			
			if (event.type == sf::Event::MouseButtonPressed)
			{
				clickSound.play();
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (event.mouseButton.x > 235 && event.mouseButton.x < 445 && event.mouseButton.y > 510 && event.mouseButton.y < 725) {
						fondEcran.setTextureRect(rectFond);
						if (!texture.loadFromFile("ressources/Images/EnConstruction.jpg"))
						{
							window.close();
						}
						fondEcran.setTexture(&texture);
						backgroundMusic.stop();
						
					}
					
					
					if (event.mouseButton.x > 505 && event.mouseButton.x < 775 && event.mouseButton.y > 510 && event.mouseButton.y < 775) {
						
						//setText(text);
						if (!texture.loadFromFile("ressources/Images/RestoInt.jpg"))
						{
							window.close();
						}
						backgroundMusic.stop();
						gameplayMusic.play();
						fondEcran.setTexture(&texture);
						initialiseJeu();

						//demande.setSize(Vector2f(200, 400));
						//IntRect rectDemande(1000, 60, 200, 400);
						//demande.setPosition(1000, 60);
						//demande.setFillColor(Color::White);
						
						trouverClient();
						
						textureClient.loadFromFile(_textureClient1);
						client.setTexture(textureClient);
						client.setScale(0.45, 0.45);
						client.setPosition(600, 197);
						elapsed = clock.restart();
					}

					if (event.mouseButton.x > 835 && event.mouseButton.x < 1045 && event.mouseButton.y > 510 && event.mouseButton.y < 725) {
						window.close();
					}
				}
				
				_ingredient.drawIngredients();
				_ingredient.ingredientsAleatoires();
			}
			

			
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					if (event.mouseButton.x > 109 && event.mouseButton.x < 178 && event.mouseButton.y > 520 && event.mouseButton.y < 569)
					{
						//premier pain
						_pos.push_back(0);
						_ingredient.setIngredientChoisi(x, y, 0);
						toucher = true;
					}

					if (event.mouseButton.x > 270 && event.mouseButton.x < 340 && event.mouseButton.y > 522 && event.mouseButton.y < 561)
					{
						//Avocat
						_pos.push_back(1);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 1);
						toucher = true;
					}

					if (event.mouseButton.x > 430 && event.mouseButton.x < 495 && event.mouseButton.y > 530 && event.mouseButton.y < 558)
					{
						//Bacon
						_pos.push_back(2);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 2);
						toucher = true;
					}

					if (event.mouseButton.x > 614 && event.mouseButton.x < 668 && event.mouseButton.y > 525 && event.mouseButton.y < 556)
					{
						//boeuf
						_pos.push_back(3);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 3);
						toucher = true;
					}

					if (event.mouseButton.x > 758 && event.mouseButton.x < 810 && event.mouseButton.y > 525 && event.mouseButton.y < 563)
					{
						//cornichon
						_pos.push_back(4);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 4);
						toucher = true;
					}

					if (event.mouseButton.x > 0 && event.mouseButton.x < 0 && event.mouseButton.y > 0 && event.mouseButton.y < 0)
					{
						//pas affichable, position déjà occupée
						//Salade
						_pos.push_back(5);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 5);
						toucher = true;
					}

					if (event.mouseButton.x > 1075 && event.mouseButton.x < 1134 && event.mouseButton.y > 527 && event.mouseButton.y < 660)
					{
						//Oeuf
						_pos.push_back(6);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 6);
						toucher = true;
					}

					if (event.mouseButton.x > 112 && event.mouseButton.x < 176 && event.mouseButton.y > 620 && event.mouseButton.y < 666)
					{
						//Oignon
						_pos.push_back(7);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 7);
						toucher = true;
					}

					if (event.mouseButton.x > 269 && event.mouseButton.x < 341 && event.mouseButton.y > 621 && event.mouseButton.y < 663)
					{
						//Poivron
						_pos.push_back(8);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 8);
						toucher = true;
					}

					if (event.mouseButton.x > 435 && event.mouseButton.x < 498 && event.mouseButton.y > 621 && event.mouseButton.y < 660)
					{
						//tomate
						_pos.push_back(9);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 9);
						toucher = true;
					}

					if (event.mouseButton.x > 597 && event.mouseButton.x < 655 && event.mouseButton.y > 627 && event.mouseButton.y < 662)
					{
						//Jambon
						_pos.push_back(10);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 10);
						toucher = true;
					}

					if (event.mouseButton.x > 759 && event.mouseButton.x < 813 && event.mouseButton.y > 623 && event.mouseButton.y < 651)
					{
						//Fromage
						_pos.push_back(11);

						if (toucher)
						{
							y -= 15;
						}
						_ingredient.setIngredientChoisi(x, y, 11);
						toucher = true;
					}

					if (event.mouseButton.x > 1113 && event.mouseButton.x < 1178 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
					{
						//pas affichable, position déjà occupée
						//deuxième pain
						_pos.push_back(12);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 12);
						toucher = true;
					}
				}
			}
		
			if (elapsed.asSeconds() >= 10)
			{
				cout << "allo" << endl;
				textureClient.loadFromFile(_textureClient2);
				client.setTexture(textureClient);
				client.setPosition(600, 197);
				client.setScale(0.45, 0.45);
				elapsed = clock.restart();
				
			}
		}
		window.clear();
		window.draw(fondEcran);
		//window.draw(demande);
		window.draw(client);

		for (int i = 0; i < 5; i++)
		{
			window.draw(_ingredient.getIngredients(i));
		}

		window.draw(text);
		
		for (int i = 0; i < 13; i++)
		{
			window.draw(_ingredient.getIngredients2(i));
		}

		for (int i = 0; i < _pos.size(); i++)
		{                  
			window.draw(_ingredient.getIngredientsChoisis(_pos.at(i)));
		}
		window.display();
	}
}

void Game::initialiseJeu()
{
	_lose = false;
	_score = 0;
	_time = 0;
	remplirClients();
	remplirIngredients();
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
int Game::numAleatoire(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

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

void Game::remplirClients()
{
	ifstream fluxClients;
	std::string image;
	
	fluxClients.open("ressources/clients.txt");

	if (!fluxClients.is_open())
	{
		cout << "Le fichier clients.txt est introuvable." << endl;
		system("pause");
		fluxClients.close();
		exit(0);
	}
	//pour verifier si le fichier est vide
	if (fluxClients.peek() == EOF) {
		cout << "Le fichier clients.txt est vide." << endl;
		exit(0);
	}
	while (!fluxClients.eof())
	{
		fluxClients >> image;
		_clients.push_back(image);
	}
}

void Game::remplirIngredients()
{
	ifstream fluxIngredients;
	std::string image;
	fluxIngredients.open("ressources/ingredients.txt");

	if (!fluxIngredients.is_open())
	{
		cout << "Le fichier ingredients.txt est introuvable." << endl;
		system("pause");
		fluxIngredients.close();
		exit(0);
	}
	//pour verifier si le fichier est vide
	if (fluxIngredients.peek() == EOF) {
		cout << "Le fichier ingredients.txt est vide." << endl;
		exit(0);
	}

	while (!fluxIngredients.eof())
	{
		fluxIngredients >> image;
		_ingredients.push_back(image);
	}
}

void Game::trouverClient()
{
	int index = numAleatoire(0, 3);
	_textureClient1 = _clients.at(index);
	_textureClient2 = _clients.at(index + 4);
	cout << index + 1 << " - " << _textureClient1 << endl;
	cout << index + 1 << " - " << _textureClient2 << endl;
}


void Game::creerLigneScore(std::string mot)
{
	_ligneScore += mot + " ";
}

void Game::enregistrerLigneScore()
{
	ofstream monFlux("ressources/score.txt", ios::app);

	if (!monFlux)
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier" << endl;
		exit(1);
	}
	monFlux << _ligneScore << endl;

	monFlux.close();
}

void Game::ordonerScores(std::ifstream& monFlux, std::vector<std::string> scores[2])
{
	string jouer, score;

	while (!monFlux.eof()) {
		monFlux >> jouer >> score;
		scores[0].push_back(score);
		scores[1].push_back(jouer);
	}
	for (int i = 0; i < 2; i++)
	{
		sort(scores[i].begin(), scores[i].end());
	}
	
}

void Game::afficherScores()
{
	int position = 0;
	ifstream monFlux("ressources/score.txt");
	vector<string> scores[2];

	if (!monFlux)
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier" << endl;
		exit(1);
	}

	ordonerScores(monFlux, scores);

	cout << "  Class  Joueur  Score  " << endl;
	cout << "  --------------------  " << endl;
	while (!monFlux.eof()) {
		cout.width(10);
		cout << position + 1 << "º" << scores[1].at(position) << scores[0].at(position);
		position++;
	}

	system("pause");
	monFlux.close();
}



/*
void viderBuffer()
{
	cin.clear();			//on reset le flux pour que la suite parte d’un flux valide
	cin.seekg(0, ios::end);	//se place à la fin, si ça marche, le flux est non vide

	if (!cin.fail()) //Le flux est valide, donc le buffer est non vide
	{
		cin.ignore(numeric_limits<streamsize>::max());
	}
	else //Le flux est invalide, donc le buffer est vide
	{
		cin.clear(); 		// Le flux est dans un état invalide donc on le remet en état valide
	}
}
*/

