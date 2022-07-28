#pragma once
#include "Framework/Actor.h"

class Bullet : public Bear::Actor
{
public:
	Bullet() = default;
	Bullet(const Bear::Model& model, const Bear::Transform& transform, float damage = 1) : Actor{ model, transform }, m_damage{ damage } {}

	void Update() override;
	void OnCollision(Actor* other) override;

	float GetDamage() { return m_damage; }
	
private:
	float m_damage = 1;
	float m_speed = 200;
	float m_lifespan = 2;
};