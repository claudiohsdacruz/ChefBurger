// ChefBurger.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SFML/Graphics.hpp>
#include<vector>

#include "client.h"
//#include "burger.h"
#include "ingredient.h"
#include "fenetre.h"
#include "game.h"


using namespace sf;	//en mettant ce namespace, ça évite des sf::
using namespace std; //en mettant ce namespace, ça évite des std::

int main() {
	
	Game game; //Crée le jeu

	game.play(); //Commence le jeu
	
	return 0;
}
