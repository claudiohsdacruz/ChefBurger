// ChefBurger.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<vector>

#include "client.h"
//#include "burger.h"
#include "ingredient.h"
#include "fenetre.h"
#include "game.h"


using namespace sf;	//en mettant ce namespace, ça évite des sf::
using namespace std; //en mettant ce namespace, ça évite des std::

int main() {
	
	srand(time(NULL));
	Game game; //Crée le jeu
	Ingredients ingredient;
	ingredient.drawIngredients();
	game.play(); //Commence le jeu

	Client client;
	client.afficherClient();

	
	return 0;
}
