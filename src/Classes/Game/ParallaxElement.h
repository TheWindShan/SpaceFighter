#ifndef __PARALLAX_ELEMENT_H__
#define __PARALLAX_ELEMENT_H__

#include "cocos2d.h"

USING_NS_CC;

//moves the node on the x axis, depending on where the player's ship is.
class ParallaxElement: public Node
{
public:
	//virtual const float getLeftBound() const = 0;
	//virtual const float getRightBound() const = 0;
	
	virtual const float GetParallaxWidth() const = 0;
	
	void Update(const Vec2& playerPos);
};

#endif