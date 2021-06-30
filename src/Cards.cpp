// ########################
// # 
// # @Author: Estenio Garcia
// # 
// # @Data: 29/06/2021 - Brazil Timezone
// # 
// # @Licensa: MIT
// # 
// ########################

#include "../includes/Cards.hpp"

Cards::Cards(sf::Texture& p_texture, int cardsPosition, int currentPlayer){

    this->screenPosition = cardsPosition + 1;
    this->card_id = ( rand() % 13 );

    if( card_id > 8 ){
        this->card_value = 10;
    }else{
        this->card_value = card_id + 1;
    }
    
    spr.setTexture(p_texture);

    if( currentPlayer == 1 ){
       
        spr.setPosition( (this->CARDS_WIDTH * this->screenPosition) + 10, this->CARDS_HEIGHT );
    }else{

        spr.setPosition( (this->CARDS_WIDTH * this->screenPosition) + 10, this->CARDS_HEIGHT + this->CARDS_HEIGHT + 50);
    }
    // # @Description: this function cut the exclusive cards on sprite to rendering 
    // # 
    // # @Param 1: Position x on sprite, based in width of drawing
    // # @Param 2: Position y on sprite, based in height of drawing
    // # @Param 3: width of drawing
    // # @Param 4: height of drawing
    // # 
    spr.setTextureRect(sf::IntRect(this->CARDS_WIDTH * this->card_id, ( rand() % 4)  * this->CARDS_HEIGHT, this->CARDS_WIDTH, this->CARDS_HEIGHT));
}

Cards::~Cards(){}

sf::Sprite Cards::Draw(){
    return this->spr;
}