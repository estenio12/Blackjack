// ########################
// # 
// # @Author: Estenio Garcia
// # 
// # @Data: 29/06/2021 - Brazil Timezone
// # 
// # @Licensa: MIT
// # 
// ########################

#include "../includes/Core.hpp"

TableHandle::TableHandle(sf::Texture& p_texture, float& dt){

	this->cardsSprite = p_texture;
	this->dt = dt;

	this->wins = 0;
	this->lose = 0;
	this->tie = 0;

	this->tableWinTex.loadFromFile("./resource/tableWin.png");
	this->playerWinTex.loadFromFile("./resource/playerWin.png");
	this->tieTex.loadFromFile("./resource/Tie.png");

	this->tableWinSpr.setTexture(tableWinTex);
	this->tableWinSpr.setPosition(sf::Vector2f(0.f, -115.f));

	this->playerWinSpr.setTexture(playerWinTex);
	this->playerWinSpr.setPosition(sf::Vector2f(-1.f, -115.f));

	this->tieSpr.setTexture(tieTex);
	this->tieSpr.setPosition(sf::Vector2f(-1.f, -300.f));

	this->font.loadFromFile("./font/SuperMario256.ttf");

	this->playerDisplay.setFont(this->font);
	this->playerDisplay.setString("Player:");
	this->playerDisplay.setFillColor(sf::Color::White);
	this->playerDisplay.setPosition(sf::Vector2f(65, 45));
	
	this->tableDisplay.setFont(this->font);
	this->tableDisplay.setFillColor(sf::Color(156, 167, 195, 255));
	this->tableDisplay.setString("Table:");
	this->tableDisplay.setPosition(sf::Vector2f(65, 175));

	this->tableStats.setFont(this->font);
	this->tableStats.setFillColor(sf::Color::White);
	this->tableStats.setPosition(sf::Vector2f(300, 350));
	this->tableStats.setCharacterSize(18);

	this->playerStats.setFont(this->font);
	this->playerStats.setFillColor(sf::Color(134, 34, 95, 255));
	this->playerStats.setPosition(sf::Vector2f(50, 350));
	this->playerStats.setCharacterSize(18);

	this->tieStats.setFont(this->font);
	this->tieStats.setFillColor(sf::Color::Yellow);
	this->tieStats.setPosition(sf::Vector2f(550, 350));
	this->tieStats.setCharacterSize(18);
}

TableHandle::~TableHandle(){

	playerCards.clear();
	tableCards.clear();

}

void TableHandle::GameRun(float& dt){

	if( this->gamerun ){

		// # Display Text
		if( this->playerturn ){

			this->playerDisplay.setString("Player: ( * Playing ) ");
			this->tableDisplay.setString("Table: ");
		}else{

			this->tableDisplay.setString("Table: ( * Playing )");
			this->playerDisplay.setString("Player: ");
		}


		if( firstCards ){

			// # player init cards given
			for(int i = 0; i < 2; i++){
				this->EventAddCards();
			}

			// # Table init cards given
			playerturn = false;
			for(int i = 0; i < 2; i++){
				this->EventAddCards();
			}

			this->playerturn = true;
			this->firstCards = false;
			this->buttonLocked = false;
		}else{

			// # AI Table
			if( !playerturn ){

				if( this->delayAI >= 1.f ){
					this->lockedAI = false;
					this->delayAI = 0;
				}

				if( !lockedAI ){

					int tablesum = 0;
					int playersum = 0;

					for( auto& pc : this->playerCards ){

						playersum += pc.card_value;
					}

					for( auto& tc : this->tableCards ){

						tablesum += tc.card_value;
					}

					if( tablesum >  playersum || playersum > 21 || tablesum > 21){

						switch(this->CheckWins()){

							case 0:

								if( !doOnce ){
									this->wins++;
									this->doOnce = true;
								}

								this->showPlayerWinner = true;
								this->lockedShowWinner = true;
								this->playerDisplay.setString("Player Win!");
								break;
							case 1:

								if( !doOnce ){
									this->lose++;
									this->doOnce = true;
								}

								this->showTableWinner = true;
								this->lockedShowWinner = true;
								this->tableDisplay.setString("Table Win!");
								break;
							case 2:

								if( !doOnce ){
									this->tie++;
									this->doOnce = true;
								}

								this->showTie = true;
								this->lockedShowWinner = true;
								this->playerDisplay.setString("Player: Tie!");
								this->tableDisplay.setString("Table: Tie");
								break;

						}

					}else{

						this->EventAddCards();
						this->lockedAI = true;
						this->delayAI = 0;
					}

				}else{

					this->delayAI += dt;
				}
			}
		}

		this->playerStats.setString("Player Wins: " + std::to_string(this->wins));
		this->tableStats.setString("Table Wins: " + std::to_string(this->lose));
		this->tieStats.setString("Tie: " + std::to_string(this->tie));
	}
}

void TableHandle::setSound(sf::SoundBuffer* p_sdx){

	this->play1.setBuffer(p_sdx[ 0 ]);
	this->play2.setBuffer(p_sdx[ 1 ]);
	this->play3.setBuffer(p_sdx[ 2 ]);
	this->play4.setBuffer(p_sdx[ 3 ]);
	this->play5.setBuffer(p_sdx[ 4 ]);

	play1.setVolume(20.f);
	play2.setVolume(20.f);
	play3.setVolume(20.f);
	play4.setVolume(20.f);
	play5.setVolume(20.f);
}

bool TableHandle::EventAddCards(){

	play1.play();

	if( playerturn ){

		playerCards.push_back(*new Cards(this->cardsSprite, playerCards.size(), getTurn()));
	
		int playersum = 0;

		for( auto& pc : this->playerCards ){

			playersum += pc.card_value;
		}

		if( playersum > 21 ){

			return true;
		}

		return false;

	}else{

		int tablesum = 0;
		tableCards.push_back(*new Cards(this->cardsSprite, tableCards.size(), getTurn()));
		
		for( auto& tc : this->tableCards ){

			tablesum += tc.card_value;
		}

		if( tablesum > 21 ){

			return true;
		}

		return false;

	}
}

inline void TableHandle::EventStop(){

	if( playerturn ){
		playerturn = false;
		buttonLocked = false;
	}else{
	  	playerturn = true;
		buttonLocked = true;
	 }
}

inline void TableHandle::EventQuit(){

	this->gamerun = false;
}

uint16_t TableHandle::CheckWins(){

	int playersum = 0;
	int tablesum = 0;

	for( auto& pc : this->playerCards ){

		playersum += pc.card_value;
	}

	for( auto& tc : this->tableCards ){

		tablesum += tc.card_value;
	}

	// # 0 = Player Win
	// # 1 = Table Win
	// # 2 = Tie

	if( playersum == 21 && tablesum == 21 ){
		return 2;
	}else if( playersum == 21 && tablesum != 21 ){
		return 0;
	}else if( tablesum == 21 && playersum != 21 ){
		return 1;
	}else if( tablesum > playersum && tablesum <= 21 ){
		return 1;
	}else if( playersum < tablesum && tablesum > 21 ){
		return 0;
	}else if( playersum > 21 && tablesum <= 21 ){
		return 1;
	}else{
		return 2;
	}
}

void TableHandle::RestartMatch(){

	playerCards.clear();
	tableCards.clear();
	this->playerturn = true;
	this->firstCards = true;
	this->buttonLocked = true;

	this->showTableWinner = false;
	this->showPlayerWinner = false;
	this->showTie = false;

	this->delayShowWinner = 0;
	this->lockedShowWinner = false;
	this->doOnce = false;
	this->doOnceWinner = false;

	play2.play();
}

inline int TableHandle::getTurn(){

	return (playerturn) ? 1 : 2;
}

void TableHandle::EventHandle(enum Actions event){

	switch(event){

		case this->Actions::AskCards:

			if( this->EventAddCards() ){

				this->playerturn = false;
				this->buttonLocked = true;
			}
		
			break;
		case this->Actions::AskStop:
			this->EventStop();
			break;
		case this->Actions::AskQuit:
			this->EventQuit();
			break;

	}
}

void TableHandle::DrawTable(sf::RenderWindow& app, float& dt){

	if( this->gamerun ){

		for( auto& pc : this->playerCards ){

			app.draw(pc.Draw());
		}

		for( auto& tc : this->tableCards ){

			app.draw(tc.Draw());
		}

		app.draw(playerStats);
		app.draw(tableStats);
		app.draw(tieStats);

		app.draw(playerDisplay);
		app.draw(tableDisplay);

		if( this->showPlayerWinner ){

			if( !this->doOnceWinner ){
				play3.play();
				this->doOnceWinner = true;
			}

			app.draw(this->playerWinSpr);

			if( this->delayShowWinner >= 3.f ){
				
				this->lockedShowWinner = false;
				this->delayShowWinner = 0;
			}

			if( !lockedShowWinner ){
				this->RestartMatch();
			}else{

				this->delayShowWinner += dt;
			}
		}
		if( this->showTableWinner ){

			if( !this->doOnceWinner ){

				if(rand() % 2 == 1){
					play4.play();
				}else{
					play5.play();
				}
				this->doOnceWinner = true;
			}

			app.draw(this->tableWinSpr);

			if( this->delayShowWinner >= 3.f ){
				this->lockedShowWinner = false;
				this->delayShowWinner = 0;
			}

			if( !lockedShowWinner ){

				this->RestartMatch();
			}else{

				this->delayShowWinner += dt;
			}
		}
		if( this->showTie ){

			if( !this->doOnceWinner ){
				play5.play();
				this->doOnceWinner = true;
			}

			app.draw(this->tieSpr);

			if( this->delayShowWinner >= 3.f ){
				this->lockedShowWinner = false;
				this->delayShowWinner = 0;
			}

			if( !lockedShowWinner ){

				this->RestartMatch();
			}else{

				this->delayShowWinner += dt;
			}
		}
	}
}