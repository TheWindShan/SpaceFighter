#ifndef __SIMPLE_ENEMY_
#define __SIMPLE_ENEMY_

#include "BaseEnemy.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace SpaceFighter
{
	class SimpleEnemy : public BaseEnemy
	{
	public:
		SimpleEnemy(const Vec2& startPos);
		virtual ~SimpleEnemy();

		virtual void Update(const float dT, const Vec2& playerPos) override;
		virtual bool ShouldBeDestroyed() override;
	private:
	};
}
#endif