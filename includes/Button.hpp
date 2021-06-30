// ########################
// # 
// # @Author: Estenio Garcia
// # 
// # @Data: 28/06/2021
// # 
// # @Licensa: MIT
// # 
// ########################

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../includes/Core.hpp"

class Button{

public:
	//sf::Texture btnTex;
	sf::Sprite btnSpr;
	sf::RenderWindow app;

	sf::Vector2f location;
	sf::Vector2f btnSize;

	bool isLocked = false;
	bool enable = true;
	float currentTimeLocked = 0;
	float timeLocked = 1;

	float delay = 0;

	TableHandle* event;
	enum TableHandle::Actions action;

	// # Audio
	sf::Sound play;

public:
	Button(TableHandle* );
	~Button();
	void EventHandle(sf::RenderWindow& app, float&);
	void Draw(sf::RenderWindow& app);
	void setEvent(enum TableHandle::Actions);
	void setImage(sf::Texture&);
	void setLocation(sf::Vector2f);
	void setTimeLocked(float );
	void setEnable(bool);
	void setSounds(sf::SoundBuffer&);

};