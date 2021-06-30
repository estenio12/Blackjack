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
#include <SFML/Graphics.hpp>

class Cards{

public:
	const float CARDS_WIDTH = 61.6, CARDS_HEIGHT = 81;

	int card_value = 0;
	int card_id = 0;
	int screenPosition = 0;

	sf::Sprite spr;

public:
	// # @Description: Class Constructor
	// # 
	// # @Param 1: texture from memory
	// # @Param 2: position this class in vector
	// # 
	Cards(sf::Texture&, int cardsPosition, int currentPlayer);
	~Cards();

	// # Draw Object
	sf::Sprite Draw();

};