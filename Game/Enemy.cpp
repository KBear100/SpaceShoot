#include "Enemy.h"
#include "Engine.h"
#include "Bullet.h"
#include "Player.h"

void Enemy::Initialize()
{
	m_fireTimer = Bear::randomf(2, 6);
	m_speed = Bear::random(20, 150);
}

void Enemy::Update()
{
	// fire weapon
	m_fireTimer -= Bear::g_time.deltaTime;
	if (m_fireTimer <= 0)
	{
		Bear::g_audioSystem.PlayAudio("laser");
		m_fireTimer = Bear::randomf(2, 6);
		Bear::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(Bear::Model{ "Models/Bullet.txt" }, transform);
		bullet->GetTag() = "enemy";
		m_scene->Add(std::move(bullet));
	}

	// set rotation toward player
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Bear::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.GetAngle();
	}

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

void Enemy::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "player")
	{
		Bear::g_audioSystem.PlayAudio("explosion");

		//m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		//if (m_health <= 0)

		m_scene->GetGame()->AddPoints(50);
		m_destroy = true;
	}
}
