// ########################
// # 
// # @Author: Estenio Garcia
// # 
// # @Data: 28/06/2021 - Brazil Timezone
// # 
// # @Licensa: MIT
// # 
// ########################

#include "../includes/Button.hpp"

Button::Button(TableHandle* event){

	this->event = event;
}

Button::~Button(){

	this->play.~Sound();
}

void Button::Draw(sf::RenderWindow& app){

	app.draw(btnSpr);
}

void Button::EventHandle(sf::RenderWindow& app, float& dt){

	// # if playerturn is false, this button became unable
	this->enable = !this->event->buttonLocked;

	if(currentTimeLocked >= timeLocked)
		isLocked = false;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		
		if( sf::Mouse::getPosition(app).x > this->btnSpr.getPosition().x
		&& sf::Mouse::getPosition(app).x < this->btnSpr.getPosition().x + this->btnSize.x 
		&& sf::Mouse::getPosition(app).y > this->btnSpr.getPosition().y 
		&& sf::Mouse::getPosition(app).y < this->btnSpr.getPosition().y + this->btnSize.y ){

			if( !isLocked && enable ){
				
				this->isLocked = true;
				this->currentTimeLocked = 0;

				// # Execute event call here
				this->event->EventHandle(this->action);
				this->play.play();
			}
		}
	}

	if( isLocked )
		this->currentTimeLocked += dt;
}

void Button::setEvent(enum TableHandle::Actions action){
	this->action = action;
}

void Button::setImage(sf::Texture& tex){
	
	this->btnSpr.setTexture(tex);
	this->btnSize = sf::Vector2f(btnSpr.getTexture()->getSize().x, btnSpr.getTexture()->getSize().y);
}

void Button::setLocation(sf::Vector2f ploc){

	this->btnSpr.setPosition(ploc);
}

void Button::setTimeLocked(float newTimeLocked){

	this->timeLocked = newTimeLocked;
}

void Button::setEnable(bool state){

	this->enable = state;
}

void Button::setSounds(sf::SoundBuffer& sdx){

	this->play.setBuffer(sdx);
	this->play.setVolume(25.f);
}