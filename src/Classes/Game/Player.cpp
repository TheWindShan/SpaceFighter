#include "Player.h"
#include <algorithm>

//USING_NS_CC;

Player::Player()
{
	_Sprite = Sprite::create("Images/playerShip2_blue.png");
	this->addChild(_Sprite);

	auto screenSize = Director::getInstance()->getWinSize();
	auto pos = Vec2( (screenSize.width/2)*1, 50);
    this->setPosition(pos) ;
	_Destination = pos;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

Player::~Player()
{
	this->removeAllChildren();
}
		
bool Player::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	 _Destination = touch->getLocation();
	 return true;
}

void Player::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_Destination = touch->getLocation();
}

void Player::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_Destination = this->getPosition();
}

void Player::Update(float dT)
{
	// Moves the ship
	auto pos = this->getPosition();
	auto dir = _Destination - pos;
	auto len = dir.length();
	dir.normalize();
	auto offset = std::min(len, dT * SHIP_SPEED);

	pos = pos + dir * offset;

	// And constraint its position without the world
	auto halfShip = _Sprite->getContentSize() / 2;
	pos = pos.getClampPoint( halfShip, Director::getInstance()->getWinSize()-halfShip);

	this->setPosition(pos);
}