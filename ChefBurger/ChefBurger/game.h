/************************************************************************************
* Auteur	: Claudio Cruz, Sarah Diakite, Paule Axelle  et Ramin Amiri				*
* Nom		: game.h																*
* Date		: 22 mai 2022															*
* Description : La classe Game implémente le jeu ChefBurger en console. 			*
************************************************************************************/

#pragma once

class Game
{
private:
	int _score;
	double _time;
	int _nbParties;
	int _scoreTotal;
	bool _lose;
	bool _restartTime;

	sf::Text _text;
	std::string _nomJoueur;
	std::string _ligneScore;
	Client _client;
	Ingredient _ingredient;
	std::string _textureClient1;
	std::string _textureClient2;
	std::string _textureIngredient;
	std::vector<std::string> _clients;
	std::vector<std::string> _ingredients;

public:
	Game();
	~Game();

	int getScore() const;
	int getScoreTotal() const;
	int getTime() const;
	int getNbParties()const;
	bool getLose() const;
	std::string getNomJoueur() const;
	Client getClient()const;

	void setScore(int newScore);
	void setTime(int newTime);
	void setLose(bool lose);
	void setNomJoueur(std::string newNomJoueur);
	void setClient(Client newClient);
	void setText(sf::Text& text, const char* message, sf::Font& font, int posX, int posY, int taille, const sf::Color& color);
	void setIngredientChoisi(int x, int y, int i);

	void playGame();
	void initialiseJeu();
	void demanderNomJoueur();
	bool validerDemande(std::vector <int> pos, int& index, int& index1, int& index2);
	void play();
	int numAleatoire(int min, int max);
	Client randClient() const;

	void endGame();
	void printEndGame(std::ostream& sortie) const;//affiche game over et le score
	
	void remplirClients();
	void remplirIngredients();

	void trouverClient();
	void trouverIngredient();
	void afficherIngredientChoisi(sf::Texture& texture, sf::Sprite& ingredientChoisi, int index);

	void creerLigneScore(std::string mot);
	void enregistrerLigneScore();
	void ordonerScores(std::ifstream& monFlux, std::vector<std::string> scores[2]);
	void afficherScores();
	void afficherInstruction();
	void laisserCommentaire(std::string &commentaire, char reponse); // donne la possibilité à l'utilisateur de laisser un commentaire
	void statistiqueDuJeu(std::string& commentaire);
	void viderBuffer();
};
