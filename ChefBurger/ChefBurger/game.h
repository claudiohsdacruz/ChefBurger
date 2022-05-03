#pragma once

class Game
{
private:
	int _score;
	int _time;
	std::string _nomJoueur;
	Burger _burger;
	Client _client;
public:
	Game();
	~Game();
};
