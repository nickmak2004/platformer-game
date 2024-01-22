#pragma once
#include "dynamic_object.h"
#include "moving_enemy.h"
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
class ProjectileEnemy : public DynamicObject {
	std::chrono::time_point<std::chrono::system_clock> startTime;
public:
	std::list<Projectile*> m_projectiles;
	void startTimer();
	bool threeSecondsPassed();
	void update(float dt) override;
	void createProjectileEveryThreeSeconds();
	void draw() override;
	void init()	override;
	void handleCollision(CollisionType type) override;
	void createProjectile();
	void checkPlayerpos();
	void checkcollision();
	void checkProjectileBoundaries();
	ProjectileEnemy(float x, float y, float w, float h , const std::string& assetName);
};
