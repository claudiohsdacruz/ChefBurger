#include <iostream>
#include <fstream>
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
	_ingredient = Ingredient();
	_clients = {};
	_client = Client();
	//_fenetre = Fenetre();
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
	//_fenetre.~Fenetre();
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
/*
Fenetre Game::getFenetre() const
{
	return _fenetre;
}
*/
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
/*
void ouvrirFichier(std::ifstream& monFlux, std::string fichier)
{
	monFlux.open(fichier);

	if (!monFlux.is_open())
	{
		cout << "Le fichier " << fichier << " est introuvable." << endl;
		system("pause");
		monFlux.close();
		exit(0);
	}
	//pour verifier si le fichier est vide
	if (monFlux.peek() == EOF) { 
		cout << "Le fichier " << fichier << "est vide." << endl;
		exit(0);
	}
}
*/

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



	RenderWindow window(VideoMode(1280, 800), "Chef Burger", Style::Close);
	Event event;
	
	RectangleShape fondEcran;
	RectangleShape demande;
	Sprite client;

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
						initialiseJeu();
						//setText(text);
						if (!texture.loadFromFile("ressources/Images/RestoInt.jpg"))
						{
							window.close();
						}
						backgroundMusic.stop();
						gameplayMusic.play();
						fondEcran.setTexture(&texture);


						demande.setSize(Vector2f(200, 400));
						IntRect rectDemande(1000, 60, 200, 400);
						demande.setPosition(1000, 60);
						demande.setFillColor(Color::White);
						trouverIngredient();
						trouverClient();
						Texture textureClient;
						textureClient.loadFromFile("ressources/Clients/client1_souriant_red.png");
						client.setTexture(textureClient);
						client.setPosition(600, 197);

					}

					if (event.mouseButton.x > 835 && event.mouseButton.x < 1045 && event.mouseButton.y > 510 && event.mouseButton.y < 725) {
						window.close();
					}
				}
			}
			
		}
		window.clear();
		window.draw(fondEcran);
		window.draw(demande);
		window.draw(client);
		window.draw(text);
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
	//_nomJoueur = demanderNomJoueur();

	

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
int Game::numAleatoire(int min, int max)
{
	return rand() % (max - min + 1) + min;
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
	int index = numAleatoire(0, 4);
	string chemin = _clients.at(index);
	cout << index << " - " << chemin << endl;
	Texture textureClient;
	textureClient.loadFromFile(chemin);
	_client.setTexture(textureClient);
	_client.setPosX(600);
	_client.setPosY(197);
}

void Game::trouverIngredient()
{
	int index = numAleatoire(2, 13);
	string chemin = _ingredients.at(index);
	cout << index << " - " << chemin << endl;
	Texture texture;
	texture.loadFromFile(chemin);
	_client.setTexture(texture);
	_client.setPosX(1000);
	_client.setPosY(60);
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

