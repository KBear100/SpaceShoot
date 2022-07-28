#pragma once
#include "Framework/Actor.h"

class Player : public Bear::Actor
{
public:
	Player() = default;
	Player(const Bear::Model& model, const Bear::Transform& transform) : Actor{ model, transform } {}

	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health{ 3 };

	float m_speed{ 0 };
	float m_maxSpeed{ 200 };
};