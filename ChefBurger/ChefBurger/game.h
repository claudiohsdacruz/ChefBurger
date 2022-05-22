/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: game.h																*
* Date		: 20 mai 2022															*
* Description : La classe Game implémente Le jeu ChefBurger en console. 			*
************************************************************************************/

#pragma once

class Game
{
private:
	int _score;
	double _time;
	int _life;
	bool _lose;
	bool _restartTime;

	sf::Text _text;
	//sf::Text _Jouer;
	std::string _nomJoueur;
	std::string _ligneScore;
	
	Client _client;
	Ingredient _ingredient;
	

	std::string _textureClient1;
	std::string _textureClient2;
	std::string _textureIngredient;
	std::vector<std::string> _clients;
	std::vector<std::string> _ingredients;
	std::vector<sf::Sprite> _burger;

public:
	Game();
	~Game();

	int getScore() const;
	int getTime() const;
	int getLife() const;
	bool getLose() const;

	std::string getNomJoueur() const;
	Client getClient()const;

	void setScore(int newScore);
	void setTime(int newTime);
	void setLife(int newLife);
	void setLose(bool lose);
	void setNomJoueur(std::string newNomJoueur);
	void setClient(Client newClient);
	void setText(sf::Text& text, const char* message, sf::Font& font, int posX, int posY, int taille, const sf::Color& color);
	void setIngredientChoisi(int x, int y, int i);

	void initialiseWindow();
	void initialiseJeu();
	void demanderNomJoueur();
	void play();				//la main loop du jeu
	int numAleatoire(int min, int max);
	Client randClient() const;

	void endGame();
	void printScore(std::ostream& sortie) const;	//affiche le score
	void printTime(std::ostream& sortie) const;	//affiche le compteur de temps)
	void printEndGame(std::ostream& sortie) const;//affiche game over et le score
	
	void remplirClients();
	void remplirIngredients();

	void trouverClient();
	void trouverIngredient();
	void afficherIngredientChoisi(sf::Texture& texture, sf::Sprite& ingredientChoisi, int index);

	void creerLigneScore(std::string mot);
	void enregistrerLigneScore();
	void ordonerScores(std::ifstream& monFlux, std::vector<std::string> scores[2]);
	void afficherInformation(sf::Text& texte, std::string texteAffichee, sf::Font font, std::ostringstream& ssTime, double valeurInitial, int posX, int posY, int size);
	void afficherScores();
	

};
