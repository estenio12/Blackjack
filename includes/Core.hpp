// ########################
// # 
// # @Author: Estenio Garcia
// # 
// # @Data: 29/06/2021 - Brazil Timezone
// # 
// # @Licensa: MIT
// # 
// ########################

#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../includes/Cards.hpp"

class TableHandle{

public:
	int wins, lose, tie;
	bool playerturn = true;
	bool gamerun = true;
	bool firstCards = true;
	bool buttonLocked = false;
	bool showPlayerWinner = false;
	bool showTableWinner = false;
	bool showTie = false;

	float dt = 0;
	float delayAI = 0;
	float delayShowWinner = 0;

	std::vector<Cards> playerCards;
	std::vector<Cards> tableCards;

	sf::Texture cardsSprite;
	sf::Texture tableWinTex;
	sf::Texture playerWinTex;
	sf::Texture tieTex;
	sf::Sprite tableWinSpr;
	sf::Sprite playerWinSpr;
	sf::Sprite tieSpr;

	sf::Font font;
	sf::Text playerDisplay;
	sf::Text tableDisplay;
	sf::Text playerStats;
	sf::Text tableStats;
	sf::Text tieStats;

	enum Actions{
		AskCards,
		AskStop,
		AskQuit
	};

	bool lockedAI = false;
	bool lockedShowWinner = false;
	bool doOnce = false;
	bool doOnceWinner = false;

	// # Audio
	sf::Sound play1;
	sf::Sound play2;
	sf::Sound play3;
	sf::Sound play4;
	sf::Sound play5;

public:
	explicit TableHandle(sf::Texture&, float& dt );
	~TableHandle();

	void EventHandle(enum Actions);
	void EventStop();
	void EventQuit();
	void RestartMatch();
	void setSound(sf::SoundBuffer*);

	void GameRun(float&);
	
	uint16_t CheckWins();
	bool EventAddCards();

	void DrawTable(sf::RenderWindow& app, float& );

	int getTurn();
};

