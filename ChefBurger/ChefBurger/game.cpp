#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
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

void Game::setText(sf::Text& text, const char* message, sf::Font& font, int posX, int posY, int taille, const sf::Color& color)
{
	_text.setCharacterSize(taille);
	_text.setString(message);
	_text.setFillColor(color);
	_text.setPosition(posX, posY);
}

void Game::setIngredientChoisi(int x, int y, int i)
{
	_ingredient.getIngredientsChoisis(i).setPosition(x,y);

}

void Game::initialiseWindow()
{
	sf::Font font;
	//sf::Text text;
	bool affiche = true;

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
	Sprite ingredientChoisi;

	Texture textureClient;
	Texture textureIngredient;

	char lettre = 20;

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
	_text.setFont(font);

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
		if (affiche) {
			setText(_text, "Touche <Espace> pour jouer", font, 350, 700, 42, Color::White);
		}
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed)
				window.close();

			elapsed = clock.getElapsedTime();
			elapsed.asSeconds();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					affiche = false;
					_text.setString("");
					if (!texture.loadFromFile("ressources/Images/RestoInt.jpg"))
					{
						window.close();
					}
					backgroundMusic.stop();
					gameplayMusic.play();
					fondEcran.setTexture(&texture);
					initialiseJeu();

					trouverClient();

					textureClient.loadFromFile(_textureClient1);
					client.setTexture(textureClient);
					client.setScale(0.40, 0.40);
					client.setPosition(600, 178);
					elapsed = clock.restart();

					_ingredient.drawIngredients();
					_ingredient.ingredientsAleatoires();
				}
			}
			/*
			setText(_text, "Quel est votre nom ? ", font, 630, 400, 40, Color::Red);
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
					lettre = 20;

				while (lettre != 13) {
					cout << "letre : " << static_cast<char>(event.text.unicode) << endl;
					lettre = _getch();
					_nomJoueur += lettre;
					//setText(text, _nomJoueur);

				}
				cout << _nomJoueur << endl;
			}
			*/
			if (event.type == sf::Event::MouseButtonPressed)
			{
				clickSound.play();
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					
				}

			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					if (event.mouseButton.x > 109 && event.mouseButton.x < 178 && event.mouseButton.y > 520 && event.mouseButton.y < 569)
					{
						//premier pain
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 0);
						//_burger.push_back(ingredientChoisi);
						
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
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 1);
						//_burger.push_back(ingredientChoisi);
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
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 2);
						//_burger.push_back(ingredientChoisi);
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
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 3);
						//_burger.push_back(ingredientChoisi);
					}

					if (event.mouseButton.x > 750 && event.mouseButton.x < 850 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						//cornichon
						_pos.push_back(4);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 4);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 4);
						//_burger.push_back(ingredientChoisi);
					}

					if (event.mouseButton.x > 900 && event.mouseButton.x < 1020 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						//Salade
						_pos.push_back(5);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 5);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 5);
						//_burger.push_back(ingredientChoisi);
					
					}

					if (event.mouseButton.x > 1070 && event.mouseButton.x < 1175 && event.mouseButton.y > 527 && event.mouseButton.y < 660)
					{
						//Oeuf
						_pos.push_back(6);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 6);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 6);
						//window.draw(ingredientChoisi);
						
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
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 7);
						//_burger.push_back(ingredientChoisi);
	
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
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 8);
						//_burger.push_back(ingredientChoisi);
					
					}

					if (event.mouseButton.x > 430 && event.mouseButton.x < 530 && event.mouseButton.y > 621 && event.mouseButton.y < 660)
					{
						//tomate
						_pos.push_back(9);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 9);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 9);
						//_burger.push_back(ingredientChoisi);
					
					}

					if (event.mouseButton.x > 590 && event.mouseButton.x < 690 && event.mouseButton.y > 627 && event.mouseButton.y < 662)
					{
						//Jambon
						_pos.push_back(10);

						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 10);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 10);
						//_burger.push_back(ingredientChoisi);
					}

					if (event.mouseButton.x > 740 && event.mouseButton.x < 860 && event.mouseButton.y > 623 && event.mouseButton.y < 651)
					{
						//Fromage
						_pos.push_back(11);

						if (toucher)
						{
							y -= 15;
						}
						_ingredient.setIngredientChoisi(x, y, 11);
						toucher = true;
						//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 11);
						//_burger.push_back(ingredientChoisi);
					}

					if (event.mouseButton.x > 905 && event.mouseButton.x < 1045 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
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
						afficherIngredientChoisi(textureIngredient, ingredientChoisi, 12);
						_burger.push_back(ingredientChoisi);
					}
					
				}
			}

			if (elapsed.asSeconds() >= 10)
			{
				cout << "allo" << endl;
				textureClient.loadFromFile(_textureClient2);
				client.setTexture(textureClient);
				client.setPosition(600, 178);
				client.setScale(0.40, 0.40);
				elapsed = clock.restart();

			}
		}
		window.clear();
		window.draw(fondEcran);
		//window.draw(ingredientChoisi);
		window.draw(client);
		/*
		for (Sprite item : _burger) {
			window.draw(item);
		}*/
		for (int i = 0; i < 5; i++){
			window.draw(_ingredient.getIngredients(i));
		}

		window.draw(_text);

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

	//

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
	for (int i = 0; i < _clients.size(); i++)
	{
		cout << _clients.at(i) << endl;
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
	for (int i = 0; i < _ingredients.size(); i++)
	{
		cout << _ingredients.at(i) << endl;
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

void Game::trouverIngredient()
{
	int index = numAleatoire(2, 13);
	_textureIngredient = _ingredients.at(index);
	//cout << index + 1 << " - " << _textureIngredient << endl;
}

void Game::afficherIngredientChoisi(Texture& texture, Sprite& ingredientChoisi, int index)
{
	_textureIngredient = _ingredients.at(index);
	texture.loadFromFile(_textureIngredient);
	ingredientChoisi.setTexture(texture);
	ingredientChoisi.setScale(0.70, 0.70);
	ingredientChoisi.setPosition(400, 378 - index * 30);
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

