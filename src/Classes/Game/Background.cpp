#include "Background.h"
#include "math/MathUtil.h"
#include <algorithm>

Sprite* Background::_CreateSprite(const Vec2& spritePos)
{
	auto sprite = Sprite::create("Images/Background.png");
	this->addChild(sprite);
    sprite->setPosition(spritePos) ;

	return sprite;
}

Background::Background()
{
	auto screenSize = Director::getInstance()->getWinSize();
	auto w = screenSize.width;
	auto h = screenSize.height;

	_TopSprite = _CreateSprite(Vec2(w/2, h/2 + h));
	_BotSprite = _CreateSprite(Vec2(w/2, h/2));
}

Background::~Background()
{
}

float Background::GetParallaxWidth() const
{
	return _TopSprite->getContentSize().width;
}

void Background::Update(const float dT, const float scrollSpeed, const Vec2& playerPos)
{
	ParallaxElement::Update(playerPos);

	auto yOffset = -dT * scrollSpeed;
	_TopSprite->setPosition(0, _TopSprite->getPosition().y + yOffset);
	_BotSprite->setPosition(0, _BotSprite->getPosition().y + yOffset);

	//if _BottomSprite is offscreen
	if(_BotSprite->getPosition().y + _BotSprite->getContentSize().height/2 < 0 )
	{
		auto winSize = Director::getInstance()->getWinSize();
		auto botPos = _BotSprite->getPosition() + Vec2(0, 2*winSize.height);
		_BotSprite->setPosition( botPos );

		std::swap(_BotSprite, _TopSprite);
	}
}