/************************************************************************************
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

int Game::getScoreTotal() const
{
	return _scoreTotal;
}

int Game::getTime() const
{
	return _time;
}

int Game::getNbParties()const
{
	return _nbParties;
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

void Game::playGame()
{
	// Creation de variables du jeu

	// Variables de initialisation e controle du som
	Music backgroundMusic;
	Music gameplayMusic;
	SoundBuffer buffer;
	buffer.loadFromFile("ressources/Audios/Click.ogg");
	Sound clickSound;
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
	Clock clockEchange;
	Time elapsed;
	Time echange;
	Time timeDuJeu;

	// Variables apliquées sur la fenêtre
	RenderWindow window(VideoMode(1280, 800), "Chef Burger", Style::Close);
	RectangleShape fondEcran;
	window.setVerticalSyncEnabled(true); // active la synchronisation verticale
	fondEcran.setSize(Vector2f(1280, 800));
	IntRect rectFond(0, 0, 1208, 800);

	// Variables d'affichage de texte
	Font font;
	bool affiche = true;
	if (!font.loadFromFile("ressources/Polices/LuckiestGuy.ttf"))
	{
		window.close();
	}
	_text.setFont(font);

	// Variables d'affichage du Score
	Font scoreFont;
	Text afficherScore;
	int size = 1;

	// Variables d'affichage du Temps
	Font timeFont;
	Text afficherTime;
	double time = 10;

	// Variables de controle du clicage sur les ingredients
	vector <int> pos;
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
	bool burgerComplet = false;

	while (window.isOpen()) {

		// Time
		// Initialisation du time du jeu
		timeDuJeu = clockTime.getElapsedTime();
		_time = timeDuJeu.asSeconds();
		time = 20 - trunc(_time);

		echange = clockEchange.getElapsedTime();

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

		// Paramètres de l'affichage du score
		if (!affiche) {
			std::ostringstream ssScore;
			ssScore << "Score : " << _score;
			afficherScore.setCharacterSize(30);
			afficherScore.setPosition({ 20, 230 });
			afficherScore.setFont(font);
			afficherScore.setString(ssScore.str());
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

				// Initialise l'ecran du Jeu
				if (event.key.code == Keyboard::Space) {
					
					_score = 0;
					system("cls");
					_text.setString("");
					affiche = false;


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
					// Efface le burger passée

					for (int i = 0; i < 13; i++)
					{
						_ingredient.setSizeIngredientChoisi(i, 0, 0);
					}
					_nbParties += 1;

				}
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				
				_text.setString("");
				// Permet de choisir le ingredient pour monter le burger
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Premier pain
					if (event.mouseButton.x > 100 && event.mouseButton.x < 178 && event.mouseButton.y > 520 && event.mouseButton.y < 569)
					{
						clickSound.play();// Sound du click
						pos.push_back(0);
						x = 450;
						y = 400;

						_ingredient.setIngredientChoisi(x, y, 0);
						_ingredient.setSizeIngredientChoisi(0, 120, 90);

						toucher = true;
					}
					// Avocat
					if (event.mouseButton.x > 270 && event.mouseButton.x < 340 && event.mouseButton.y > 522 && event.mouseButton.y < 561)
					{
						clickSound.play();// Sound du click
						pos.push_back(1);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 1);
						_ingredient.setSizeIngredientChoisi(1, 120, 90);
						toucher = true;
					}
					//Bacon
					if (event.mouseButton.x > 430 && event.mouseButton.x < 495 && event.mouseButton.y > 530 && event.mouseButton.y < 558)
					{
						clickSound.play();// Sound du click
						pos.push_back(2);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 2);
						_ingredient.setSizeIngredientChoisi(2, 120, 90);
						toucher = true;
					}
					// Boeuf
					if (event.mouseButton.x > 614 && event.mouseButton.x < 668 && event.mouseButton.y > 525 && event.mouseButton.y < 556)
					{
						clickSound.play();// Sound du click
						pos.push_back(3);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 3);
						_ingredient.setSizeIngredientChoisi(3, 120, 90);
						toucher = true;
					}
					// Cornichon
					if (event.mouseButton.x > 750 && event.mouseButton.x < 850 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						clickSound.play();// Sound du click
						pos.push_back(4);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 4);
						_ingredient.setSizeIngredientChoisi(4, 120, 90);
						toucher = true;
					}
					// Salade
					if (event.mouseButton.x > 900 && event.mouseButton.x < 1020 && event.mouseButton.y > 520 && event.mouseButton.y < 570)
					{
						clickSound.play();// Sound du click
						pos.push_back(5);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 5);
						_ingredient.setSizeIngredientChoisi(5, 120, 90);
						toucher = true;
					}
					// Oeuf
					if (event.mouseButton.x > 1070 && event.mouseButton.x < 1175 && event.mouseButton.y > 527 && event.mouseButton.y < 570)
					{
						clickSound.play();// Sound du click
						pos.push_back(6);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 6);
						_ingredient.setSizeIngredientChoisi(6, 120, 90);
						toucher = true;
					}
					// Oignon
					if (event.mouseButton.x > 112 && event.mouseButton.x < 176 && event.mouseButton.y > 620 && event.mouseButton.y < 666)
					{
						clickSound.play();// Sound du click
						pos.push_back(7);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 7);
						_ingredient.setSizeIngredientChoisi(7, 120, 90);
						toucher = true;
					}
					// Poivron
					if (event.mouseButton.x > 269 && event.mouseButton.x < 341 && event.mouseButton.y > 621 && event.mouseButton.y < 663)
					{
						clickSound.play();// Sound du click
						pos.push_back(8);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 8);
						_ingredient.setSizeIngredientChoisi(8, 120, 90);
						toucher = true;
					}
					// Tomate
					if (event.mouseButton.x > 430 && event.mouseButton.x < 530 && event.mouseButton.y > 621 && event.mouseButton.y < 660)
					{
						clickSound.play();// Sound du click
						pos.push_back(9);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 9);
						_ingredient.setSizeIngredientChoisi(9, 120, 90);
						toucher = true;
					}
					// Jambon
					if (event.mouseButton.x > 590 && event.mouseButton.x < 690 && event.mouseButton.y > 627 && event.mouseButton.y < 662)
					{
						clickSound.play();// Sound du click
						pos.push_back(10);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 10);
						_ingredient.setSizeIngredientChoisi(10, 120, 90);
						toucher = true;
					}
					//Fromage
					if (event.mouseButton.x > 740 && event.mouseButton.x < 860 && event.mouseButton.y > 623 && event.mouseButton.y < 651)
					{
						clickSound.play();// Sound du click
						pos.push_back(11);
						if (toucher)
						{
							y -= 15;
						}
						_ingredient.setIngredientChoisi(x, y, 11);
						_ingredient.setSizeIngredientChoisi(11, 120, 90);
						toucher = true;
					}
					// Deuxième pain
					if (event.mouseButton.x > 905 && event.mouseButton.x < 1005 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
					{
						clickSound.play();// Sound du click
						pos.push_back(12);
						if (toucher)
						{
							y -= 20;
						}
						_ingredient.setIngredientChoisi(x, y, 12);
						_ingredient.setSizeIngredientChoisi(12, 120, 90);
						toucher = true;
					}
					burgerComplet = validerDemande(pos, index, index1, index2);
					// Delivrer
					if (event.mouseButton.x > 1080 && event.mouseButton.x < 1180 && event.mouseButton.y > 615 && event.mouseButton.y < 674)
					{
						clickSound.play();// Sound du click
						if (burgerComplet)
						{
							trouverClient();
							// Paramètres du client
							textureClient.loadFromFile(_textureClient1);
							client.setTexture(textureClient);
							client.setScale(0.40, 0.40);
							client.setPosition(600, 178);

							// Recupérer la demande
							_ingredient.ingredientsAleatoires(index, index1, index2);
							//cout << validerDemande(pos, index, index1, index2) << endl;

							for (int i = 0; i < 13; i++)
							{
								_ingredient.setSizeIngredientChoisi(i, 0, 0);
							}

							// Ajouter le pointage sur le score
							if (echange.asSeconds() > 10) {
								_score += 5;
							}
							else {
								_score += 10;
							}

							// Reinitialise les clock
							elapsed = clock.restart();
							echange = clockEchange.restart();
						}
						else if (!burgerComplet)
						{
							for (int i = 0; i < 13; i++)
							{
								_ingredient.setSizeIngredientChoisi(i, 0, 0);
							}
							setText(finDeJeu, "FAUX", font, 550, 350, 42, Color::Red);							
						}
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
			if (echange.asSeconds() > 15) {
				trouverClient();
				echange = clockEchange.restart();
				
				// Paramètres du client
				textureClient.loadFromFile(_textureClient1);
				client.setTexture(textureClient);
				client.setScale(0.40, 0.40);
				client.setPosition(600, 178);

				// Recupérer la demande
				_ingredient.ingredientsAleatoires(index, index1, index2);

				for (int i = 0; i < 13; i++)
				{
					_ingredient.setSizeIngredientChoisi(i, 0, 0);
				}
				
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
		for (int i = 0; i < pos.size(); i++)
		{
			window.draw(_ingredient.getIngredientsChoisis(pos.at(i)));
		}

		if (time < 0) {
			setText(finDeJeu, "GAME OVER", font, 550, 350, 42, Color::Red);
			if (time < -2) {
				setText(_text, "Touche deux fois <Espace> pour rejouer ou <Esc> pour sortir", font, 80, 700, 38, Color::Red);
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
	do
	{
		cout << " Joueur! Entrez votre nom pour débuter : ";
		getline(cin, _nomJoueur);

	} while (_nomJoueur == "");

	cout << _nomJoueur << " Bonne chance pour le jeu " << endl;
}

bool Game::validerDemande(vector <int> pos, int& index, int& index1, int& index2)
{
	bool ingredientPresent1 = false;
	bool ingredientPresent2 = false;
	bool ingredientPresent3 = false;
	bool ingredientPresent4 = false;
	bool ingredientPresent5 = false;
	bool burgerComplet = false;

	for (int i = 0; i < pos.size(); i++)
	{
		if (pos.at(i) == 0)
		{
			ingredientPresent1 = true;
		}
		else if (pos.at(i) == 12)
		{
			ingredientPresent2 = true;
		}
		else if (pos.at(i) == index)
		{
			ingredientPresent3 = true;
		}
		else if (pos.at(i) == index1)
		{
			ingredientPresent4 = true;
		}
		else if (pos.at(i) == index2)
		{
			ingredientPresent5 = true;
		}
	}
	if (ingredientPresent1 && ingredientPresent2 && ingredientPresent3 && ingredientPresent4 && ingredientPresent5)
	{
		burgerComplet = true;
	}

	return burgerComplet;
}

void Game::play()
{
	string commentaire = " ";
	char reponse = ' ';
	afficherInstruction();
	demanderNomJoueur();
	playGame();

	if (_lose) {
		creerLigneScore(_nomJoueur);
		creerLigneScore(to_string(_score));
		enregistrerLigneScore();
		afficherScores();
	}
	laisserCommentaire(commentaire, reponse);
	statistiqueDuJeu( commentaire);
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

// Faire le choix Aleatoire du client
void Game::trouverClient()
{
	int index = numAleatoire(0, 3);
	_textureClient1 = _clients.at(index);
	_textureClient2 = _clients.at(index + 4);
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
		<< "\t" << "\t" << "Il vous suffit de sélectionner les bons ingrédients correspondant à ceux" << endl
		<< "\t" << "\t" << "du menu de droite et reproduire correctement ce menu dans un temps maximal" << endl
		<< "\t" << "\t" << "de 60 secondes." << endl
		<< "\t" << "\t" << "Entrer votre nom dans la console." << endl
		<< "\t" << "\t" << "Appuyer sur la touche espace pour commencer à jouer, une fois le burger complété, " << endl 
		<< "\t" << "\t" << "cliquer sur l'icône de burger pour le donner au client" << endl
		<< "\t" << "\t" << "Attention ! le client est très impatient, vous n'avez donc que 15 seconde pour le servir " << endl 
		<< "\t" << "\t" << "avant qu'il ne parte énervé. " << endl
		<< "\t" << "\t" << "Lorsque le burger est faux il s'efface et vous avez la possibilité de le recommencer avant "<< endl 
		<< "\t" << "\t" << "que le client ne parte" << endl
		<< "\t" << "\t" << "Lorsque le temps est écoulé appuyer sur la touche espace si vous voulez rejouer seinon " << endl 
		<< "\t" << "\t" << "appuyer sur la touche 'esc' pour quitter" << endl
		<< "\t" << "\t" << "Noter aussi qu'il est possible d'effectuer les action cités précedemment à n'importe quel moment du jeu" << endl
		<< "\t" << "\t" << "Vous devez aussi savoir que vous commencez une nouvelle partie à chaque fois que vous appuyer 'espace'" << endl << endl
		<< "\t" << "\t" << "Vous trouverez les statistiques de votre jeu (nombre de parties, score final pour l'ensemble des parties, " << endl 
		<< "\t" << "\t" << "nom, moyenne de score) dans le fichier texte 'statistiqueDuJeu'" << endl
		<< "\t" << "\t" << "Il est aussi possible de laisser un commentaire à la fin du jeu" << endl
		<< endl << endl;
}

void Game::laisserCommentaire(string& commentaire, char reponse)
{
	do
	{
		cout << "Souhaitez-vous laisser un commentaire sur le jeu ?(O/N) : ";
		cin >> reponse;
	} while (reponse != 'O' && reponse != 'N');

	if (reponse == 'O')
	{
		cout << "Entrez votre Commentaire : ";
		viderBuffer();
		getline(cin ,commentaire);

	}
	else if (reponse == 'N')
	{
			
		cout << "Merci d'avoir joué" << endl;
	}

}

void Game::statistiqueDuJeu(string& commentaire)
{
	
	ofstream monFlux;
	monFlux.open("StatistiqueDuJeu.txt", ios::app) ;

	if (monFlux.is_open())
	{
		monFlux << "****************************Joueur : " << getNomJoueur() << "*****************************" << endl << endl;
		monFlux << "Score Total : " << getScoreTotal() << endl;
		monFlux << "Moyenne des scores : " << getScoreTotal() / getNbParties() << endl;
		monFlux << "Nombre de parties jouées : " << getNbParties() << endl;
		if (commentaire != " ")
		{
			monFlux << "Commentaire : " << commentaire << endl << endl;
		}
		else
		{
			monFlux << "Commentaire : Aucun"  << endl<<endl;
		}
	}
	else
	{
		cout << "Erreur d'ouverture de fichier" << endl;
		system("pause");
		exit(1);
		monFlux.close();
	}

	monFlux.close();
}

void Game::viderBuffer()
{
	cin.clear();
	cin.seekg(0, ios::end);
	if (!cin.fail())
	{
		cin.ignore();
	}
	else 
	{
		cin.clear();
	}
		
}