#include "World.h"
#include "Player.h"
#include "Background.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/BaseEnemy.h"
#include "Projectile/ProjectileManager.h"
#include "Game/Projectile/Projectile.h"
#include "Game/GameObjectConst.h"
#include "Core/Utils.h"
#include <assert.h>

const float World::_SCROLL_SPEED = 250;

World* World::_WorldInstance = nullptr;

void World::Init()
{
	assert(_WorldInstance == nullptr);
	_WorldInstance = new World();
}

void World::Shutdown()
{
	delete_safe(_WorldInstance);
}

World& World::GetInstance()
{
	assert(_WorldInstance != nullptr);
	return *_WorldInstance;
}

World::World():
	_Player(new Player()),
	_Background( new Background()),
	_EnemyManager(new EnemyManager()),
	_ProjectileManager(new ProjectileManager())
{
	this->addChild(_Background, 0);
	this->addChild(_EnemyManager, 1);
	this->addChild(_ProjectileManager, 2);
	this->addChild(_Player, 3);
}

World::~World()
{
	delete_safe(_Player);
	delete_safe(_Background);
	delete_safe(_EnemyManager);
	delete_safe(_ProjectileManager);
}

ProjectileManager& World::GetProjectileManager() const
{
	return *_ProjectileManager;
}

void World::Update(float dT)
{
	_Player->Update(dT);
	_Background->Update(dT, _SCROLL_SPEED, _Player->getPosition() );
	_EnemyManager->Update(dT, _SCROLL_SPEED, _Player->getPosition());
	_ProjectileManager->Update(dT, _Player->getPosition());
}

void World::ProjectileCollideEnemy(Node* nodeProjectile, Node* nodeEnemy)
{
	auto projectile = static_cast<Projectile*>(nodeProjectile);
	projectile->Explode();

	auto enemy = static_cast<BaseEnemy*>(nodeEnemy);
	enemy->Hurt(projectile->GetDommagePoint());
}

bool World::OnContactBegin(PhysicsContact& contact)
{
	using namespace GameObjectConst;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	auto tagA = nodeA->getTag();
	auto tagB = nodeB->getTag();

	if (tagA == (int)Tags::PROJECTILE && tagB == (int)Tags::ENEMY)
	{
		ProjectileCollideEnemy(nodeA, nodeB);
	}
	else if (tagA == (int)Tags::ENEMY && tagB == (int)Tags::PROJECTILE)
	{
		ProjectileCollideEnemy(nodeB, nodeA);
	}
	else
	{
		assert(false && "cannot handle this collision");
	}

	return false;
}