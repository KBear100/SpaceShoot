#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"

void Bullet::Update()
{
	m_lifespan -= Bear::g_time.deltaTime;
	if (m_lifespan <= 0) m_destroy = true;

	Bear::Vector2 direction{ 1, 0 };
	direction = Bear::Vector2::Rotate(direction, m_transform.rotation);
	Bear::Vector2 velocity = direction * m_speed * Bear::g_time.deltaTime;

	m_transform.position += velocity;

	// wrap
	if (m_transform.position.x > Bear::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)Bear::g_renderer.GetWidth();
	if (m_transform.position.y > Bear::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)Bear::g_renderer.GetHeight();
}

void Bullet::OnCollision(Actor* other)
{
	if (dynamic_cast<Player*>(other) && m_tag != "player")
	{
		m_destroy = true;
	}

	if (dynamic_cast<Enemy*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}

	if (dynamic_cast<Bullet*>(other))
	{
		m_destroy = true;
	}
}
