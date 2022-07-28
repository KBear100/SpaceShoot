#pragma once
#include "Framework/Actor.h"

class Enemy : public Bear::Actor
{
public:
	Enemy() = default;
	Enemy(const Bear::Model& model, const Bear::Transform& transform, float health = 1.0f) : Actor{ model, transform }, m_health{ health } { Initialize(); }

	void Initialize();
	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health = 1;

	float m_speed = 50;
	float m_fireTimer = 0;
};