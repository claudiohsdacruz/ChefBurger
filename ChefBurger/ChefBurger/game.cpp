﻿/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: game.cpp																*
* Date		: 22 mai 2022															*
* Description : La classe Game implémente le jeu ChefBurger en console. 			*
************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "client.h"
#include "ingredient.h"
#include "game.h"

using namespace sf;
using namespace std;

Game::Game()
{
	_score = 0;
	_time = 60;
	_life = 3;
	_lose = false;
	_restartTime = true;
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
	_restartTime = false;
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
	return _time;
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
	_time = newTime;
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
	_ingredient.getIngredientsChoisis(i).setPosition(x, y);

}

void Game::initialiseWindow()
{
	// Creation de variables du jeu
	
	// Variables de initialisation e controle du som
	sf::Music backgroundMusic;
	sf::Music gameplayMusic;
	sf::SoundBuffer buffer;
	buffer.loadFromFile("ressources/Audios/Click.ogg");
	sf::Sound clickSound;
	clickSound.setBuffer(buffer);
	if (!gameplayMusic.openFromFile("ressources/Audios/gameMusic.ogg"))
	{
		cout << "Erreur";
	}
	if (!backgroundMusic.openFromFile("ressources/Audios/MenuMusic.ogg"))
	{
		cout << "Erreur";
	}
	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	// Variable de temps
	Clock clock;
	Clock clockTime;
	Time elapsed;
	Time timeDuJeu;

	// Variables apliquées sur la fenêtre
	RenderWindow window(VideoMode(1280, 800), "Chef Burger", Style::Close);
	RectangleShape fondEcran;
	window.setVerticalSyncEnabled(true); // active la synchronisation verticale
	fondEcran.setSize(Vector2f(1280, 800));
	IntRect rectFond(0, 0, 1208, 800);

	// Variables d'affichage de texte
	sf::Font font;
	bool affiche = true;
	if (!font.loadFromFile("ressources/Polices/LuckiestGuy.ttf"))
	{
		window.close();
	}
	_text.setFont(font);

	// Variables d'affichage du Score
	sf::Font scoreFont;
	sf::Text afficherScore;
	int score = 0;
	int size = 1;

	// Variables d'affichage du Temps
	Font timeFont;
	Text afficherTime;
	double time = 10;

	// Variables de controle du clicage sur les ingredients
	vector <int> _pos;
	int i = 0;
	bool toucher = false;
	float x = 450;
	float y = 400;

	// Textures apliquées
	Texture textureClient;
	Texture texture;
	if (!texture.loadFromFile("ressources/Images/Menu.jpg"))
	{
		window.close();
	}
	fondEcran.setTexture(&texture);

	// D'autres variables
	Event event;
	Sprite client;
	Text finDeJeu;
	int index = 0;
	int index1 = 0;
	int index2 = 0;

	while (window.isOpen()) {

		// Time
		// Initialisation du time du jeu
		timeDuJeu = clockTime.getElapsedTime();
		_time = timeDuJeu.asSeconds();
		time = 10 - trunc(_time);

		// Paramètres pour la affichage du time
		std::ostringstream ssTime;
		if (!affiche) {
			if (time <= 0) {
				ssTime << "Time : " << "0";
			}
			else {
				ssTime << "Time : " << time;
			}
			
			afficherTime.setCharacterSize(30);
			afficherTime.setPosition({ 20, 280 });
			afficherTime.setFont(font);
			afficherTime.setString(ssTime.str());
		}
		// Affiche message de initialisation du jeu
		if (affiche) {
			setText(_text, "Touche <Espace> pour jouer", font, 350, 700, 42, Color::White);
		}

		while (window.pollEvent(event)) {
			// Fermeture de la fenêtre
			if (event.type == Event::Closed)
				window.close();

			// Initialise le temps pour le client faire le burguer
			elapsed = clock.getElapsedTime();
			elapsed.asSeconds();


			if (event.type == Event::KeyPressed) {
				// Fin du jeu
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				// Paramètres de l'affichage du score
				std::ostringstream ssScore;
				ssScore << "Score : " << score;
				afficherScore.setCharacterSize(30);
				afficherScore.setPosition({ 20, 230 });
				afficherScore.setFont(font);
				afficherScore.setString(ssScore.str());

				// Initialise l'ecran du Jeu
				if (event.key.code == Keyboard::Space) {

					system("cls");
					_text.setString("");
					affiche = false;
					// Efface le texte 
					

					// Renitialise le temps du jeu
					if (_restartTime) {
						clockTime.restart();
						_restartTime = false;
					}

					// Change le fond de l'Ecran
					if (!texture.loadFromFile("ressources/Images/RestoInt.jpg"))
					{
						window.close();
					}
					fondEcran.setTexture(&texture);

					// Change la musique
					backgroundMusic.stop();
					gameplayMusic.play();

					initialiseJeu();

					trouverClient();

					// Paramètres du client
					textureClient.loadFromFile(_textureClient1);
					client.setTexture(textureClient);
					client.setScale(0.40, 0.40);
					client.setPosition(600, 178);
					elapsed = clock.restart(); // reinialise le clock du client

					// Recupérer tous les ingredients
					_ingredient.drawIngredients();

					// Recupérer la demande
					_ingredient.ingredientsAleatoires(index, index1, index2);
				}
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				clickSound.play();// Sound du click

				// Permet de choisir le ingredient pour monter le burger
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Premier pain
					if (event.mouseButton.x > 109 && event.mouseButton.x < 178 && event.mouseButton.y > 520 && event.mouseButton.y < 569)
					{
						_pos.push_back(0);
						_ingredient.setIngredientChoisi(x, y, 0);
						toucher = true;
					}
					// Avocat
					if (event.mouseButton.x > 270 && event.mouseButton.x < 340 && event.mouseButton.y > 522 && event.mouseButton.y < 561)
					{
						_pos.push_back(1);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 1);
						toucher = true;
					}
					//Bacon
					if (event.mouseButton.x > 430 && event.mouseButton.x < 495 && event.mouseButton.y > 530 && event.mouseButton.y < 558)
					{
						_pos.push_back(2);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 2);
						toucher = true;
					}
					// Boeuf
					if (event.mouseButton.x > 614 && event.mouseButton.x < 668 && event.mouseButton.y > 525 && event.mouseButton.y < 556)
					{
						_pos.push_back(3);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 3);
						toucher = true;
					}
					// Cornichon
					if (event.mouseButton.x > 750 && event.mouseButton.x < 850 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						_pos.push_back(4);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 4);
						toucher = true;
					}
					// Salade
					if (event.mouseButton.x > 900 && event.mouseButton.x < 1020 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						_pos.push_back(5);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 5);
						toucher = true;
					}
					// Oeuf
					if (event.mouseButton.x > 1070 && event.mouseButton.x < 1175 && event.mouseButton.y > 527 && event.mouseButton.y < 570)
					{
						_pos.push_back(6);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 6);
						toucher = true;
					}
					// Oignon
					if (event.mouseButton.x > 112 && event.mouseButton.x < 176 && event.mouseButton.y > 620 && event.mouseButton.y < 666)
					{
						_pos.push_back(7);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 7);
						toucher = true;
					}
					// Poivron
					if (event.mouseButton.x > 269 && event.mouseButton.x < 341 && event.mouseButton.y > 621 && event.mouseButton.y < 663)
					{
						_pos.push_back(8);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 8);
						toucher = true;
					}
					// Tomate
					if (event.mouseButton.x > 430 && event.mouseButton.x < 530 && event.mouseButton.y > 621 && event.mouseButton.y < 660)
					{
						_pos.push_back(9);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 9);
						toucher = true;
					}
					// Jambon
					if (event.mouseButton.x > 590 && event.mouseButton.x < 690 && event.mouseButton.y > 627 && event.mouseButton.y < 662)
					{
						_pos.push_back(10);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 10);
						toucher = true;
					}
					//Fromage
					if (event.mouseButton.x > 740 && event.mouseButton.x < 860 && event.mouseButton.y > 623 && event.mouseButton.y < 651)
					{
						_pos.push_back(11);
						if (toucher)
						{
							y -= 15;
						}
						_ingredient.setIngredientChoisi(x, y, 11);
						toucher = true;
					}
					// Deuxième pain
					if (event.mouseButton.x > 905 && event.mouseButton.x < 1005 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
					{
						_pos.push_back(12);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 12);
						toucher = true;
					}
					// Delivrer
					if (event.mouseButton.x > 1045 && event.mouseButton.x < 1145 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
					{
						trouverClient();
						// Paramètres du client
						textureClient.loadFromFile(_textureClient1);
						client.setTexture(textureClient);
						client.setScale(0.40, 0.40);
						client.setPosition(600, 178);

						// Recupérer la demande
						_ingredient.ingredientsAleatoires(index, index1, index2);
						cout << validerDemande(_pos) << endl;

						float x = 450;
						float y = 400;
					}
				}
			}
			// Affichage du client colérique après 10 secondes
			if (elapsed.asSeconds() >= 10)
			{
				textureClient.loadFromFile(_textureClient2);
				client.setTexture(textureClient);
				client.setPosition(600, 178);
				client.setScale(0.40, 0.40);
				elapsed = clock.restart();
			}
		}
		
		window.clear();
		window.draw(fondEcran);
		window.draw(afficherScore);
		window.draw(afficherTime);
		window.draw(client);
		window.draw(_text);
		// Affichage de les ingredients da demande du client
		for (int i = 0; i < 5; i++) {
			window.draw(_ingredient.getIngredients(i));
		}
		// Affichage de la liste complet des ingredients
		for (int i = 0; i < 14; i++)
		{
			window.draw(_ingredient.getIngredients2(i));
		}
		// Affichage de les ingredients choisi pour faire le burger
		for (int i = 0; i < _pos.size(); i++)
		{
			window.draw(_ingredient.getIngredientsChoisis(_pos.at(i)));
		}
		
		if (time < 0) {
			cout << time << endl;
			setText(finDeJeu, "GAME OVER", font, 550, 350, 42, Color::Red);
			if (time < -2) {
				setText(_text, "Touche <Espace> pour rejouer ou <Esc> pour sortir", font, 150, 400, 42, Color::Red);
				elapsed = clock.restart();
			}
			endGame();
		}
		window.display();
	}
}

// Initialise les paramêtres du jeu
void Game::initialiseJeu()
{
	_lose = false;
	_restartTime = true;
	_score = 0;
	_time = 60;
	remplirClients();
	remplirIngredients();
}

void Game::demanderNomJoueur()
{
	cout << " Joueur! Entrez votre nom pour débuter : ";
	getline(cin, _nomJoueur);
	cout << _nomJoueur << " Bonne chance pour le jeu " << endl;
}

bool Game::validerDemande(vector <int> _pos)
{
	int index = 0;
	int index1 = 0;
	int index2 = 0;

	bool ingredientPresent1 = false;
	bool ingredientPresent2 = false;
	bool ingredientPresent3 = false;
	bool ingredientPresent4 = false;
	bool ingredientPresent5 = false;
	bool burgerComplet = false;

	for (int i = 0; i < _pos.size(); i++)
	{
		if (_pos.at(i) == 0)
		{
			ingredientPresent1 = true;
		}
		else if (_pos.at(i) == 12)
		{
			ingredientPresent2 = true;
		}
		else if (_pos.at(i) == index)
		{
			ingredientPresent3 = true;
		}
		else if (_pos.at(i) == index1)
		{
			ingredientPresent4 = true;
		}
		else if (_pos.at(i) == index2)
		{
			ingredientPresent5 = true;
		}
	}
	if (ingredientPresent1 && ingredientPresent2 && ingredientPresent3 && ingredientPresent4 && ingredientPresent5)
	{
		burgerComplet = true;
		cout << "sarar" << endl; //verificaion du true
	}
	cout << ingredientPresent1 << " - " << ingredientPresent2 << " - " << ingredientPresent3 << " - " << ingredientPresent4 << " - " << ingredientPresent5 << " - " << endl;

	/*
	if (burgerComplet)
	{
		trouverClient();
		textureClient.loadFromFile(_textureClient1);
		client.setTexture(textureClient);
		client.setScale(0.40, 0.40);
		client.setPosition(600, 178);
		_ingredient.ingredientsAleatoires(index, index1, index2);
		//_ingredient.~Ingredient(); marche pas

	}*/
	return burgerComplet;
}

void Game::play()
{
	afficherInstruction();
	demanderNomJoueur();
	initialiseWindow();

	this->printEndGame(cout); //Affiche la message de fin du jeu
	if (_lose) {
		creerLigneScore(_nomJoueur);
		creerLigneScore(to_string(_score));
	}
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
	printEndGame(cout);
}
/*
void Game::printScore(std::ostream& sortie) const
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 21);
	sortie << "Score : " << _score;
	
}
*/
/*
void Game::printTime(std::ostream& sortie) const
{
}
*/
void Game::printEndGame(std::ostream& sortie) const
{
	sortie << "GAME OVER!" << endl;
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

// Faire le choix Aleatoire du client
void Game::trouverClient()
{
	int index = numAleatoire(0, 3);
	_textureClient1 = _clients.at(index);
	_textureClient2 = _clients.at(index + 4);
	cout << index + 1 << " - " << _textureClient1 << endl;
	cout << index + 1 << " - " << _textureClient2 << endl;
}

// Faire le choix Aleatoire du Ingredient
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
		scores[1].push_back(_nomJoueur);
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

void Game::afficherInstruction()
{
	system("cls");

	cout << "\t" << "\t" << "\t" << "* * * * * ************************************* * * * * * *" << endl
		<< "\t" << "\t" << "\t" << "\t" " * * *                             * * *" << endl
		<< "\t" << "\t" << "\t" << "\t" " * * *                             * * *" << endl

		<< "\t" << "\t" << "\t" << "\t" << "     " << "Bienvenue sur le jeu chefBurger " << endl
		<< "\t" << "\t" << "\t" << "\t" " * * *                             * * *" << endl
		<< "\t" << "\t" << "\t" << "\t" " * * *                             * * *" << endl;
	cout << "\t" << "\t" << "\t" << "* * * * * ************************************* * * * * * *" << endl << endl << endl;


	cout << "\t" << "\t" << "ce jeu se joue seul et non à plusieurs.Pour y jouer c'est très simple " << endl
		<< "\t" << "\t" << "Il vous suffit de sélectionner les bons ingrédients correspondant à celle" << endl
		<< "\t" << "\t" << "du menu de droite et reproduire correctement ce menu dans un temps maximal" << endl
		<< "\t" << "\t" << "de 60 secondes. En cas de faute effacer avec la croix blanche dans un fond rouge."

		<< endl << endl;
}

//afficherIngredientChoisi(textureIngredient, ingredientChoisi, 12);
//_burger.push_back(ingredientChoisi);

