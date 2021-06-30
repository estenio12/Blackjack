#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./includes/Button.hpp"
#include "./includes/Core.hpp"

int main(){

	srand(time(NULL));

	sf::RenderWindow app(sf::VideoMode(700, 400), "Blackjack - By Estenio Garcia", sf::Style::Close);
	app.setFramerateLimit(60);
	sf::Event event;

	// # System Variables
	sf::Clock clock;
	float dt;

	// # Load Buttons Sprites
	sf::Texture btn_ask_tex;
	btn_ask_tex.loadFromFile("./resource/btn_1.png");
	sf::Texture btn_stop_tex;
	btn_stop_tex.loadFromFile("./resource/btn_2.png");
	sf::Texture btn_quit_tex;
	btn_quit_tex.loadFromFile("./resource/btn_3.png");

	// # Table sprite
	sf::Texture tableTex;
	sf::Sprite tableSprite;
	tableTex.loadFromFile("./resource/table.jpg");
	tableSprite.setTexture(tableTex);

	// # Load Cards Sprite
	sf::Texture CardsSprite;
	CardsSprite.loadFromFile("./resource/cards.png");

	// # Load Sounds
	sf::SoundBuffer btnClick;
	sf::SoundBuffer CoreSound[5];
	btnClick.loadFromFile("./sounds/ButtonClick.wav");
	CoreSound[ 0 ].loadFromFile("./sounds/BuyCards.wav");
	CoreSound[ 1 ].loadFromFile("./sounds/CardsGiven.wav");
	CoreSound[ 2 ].loadFromFile("./sounds/PlayerWin.wav");
	CoreSound[ 3 ].loadFromFile("./sounds/PlayerLose.wav");
	CoreSound[ 4 ].loadFromFile("./sounds/PlayerTie.wav");

	// # Instances
	TableHandle* table = new TableHandle(CardsSprite, dt);
	table->setSound(CoreSound);

	// # Buttons instances
	Button* btn_ask = new Button(table);
	btn_ask->setLocation(sf::Vector2f(580, 50));
	btn_ask->setImage(btn_ask_tex);
	btn_ask->setEvent(TableHandle::Actions::AskCards);
	btn_ask->setSounds(btnClick);

	Button* btn_stop = new Button(table);
	btn_stop->setLocation(sf::Vector2f(580, 130));
	btn_stop->setImage(btn_stop_tex);
	btn_stop->setEvent(TableHandle::Actions::AskStop);
	btn_stop->setSounds(btnClick);

	Button* btn_quit = new Button(table);
	btn_quit->setLocation(sf::Vector2f(580, 200));
	btn_quit->setImage(btn_quit_tex);
	btn_quit->setEvent(TableHandle::Actions::AskQuit);
	btn_quit->setSounds(btnClick);

	while(app.isOpen()){

		dt = clock.restart().asSeconds();

		while(app.pollEvent(event)){

			if(event.type == sf::Event::Closed){
				app.close();
			}
		}

		// # Update Methods
		btn_ask->EventHandle(app, dt);
		btn_stop->EventHandle(app, dt);
		btn_quit->EventHandle(app, dt);

		table->GameRun(dt);

		if( !table->gamerun )
			app.close();

		app.clear();

		// # Draw Object
		app.draw(tableSprite);

		btn_ask->Draw(app);
		btn_stop->Draw(app);
		btn_quit->Draw(app);

		table->DrawTable(app, dt);

		app.display();
	}

	return 0;
}