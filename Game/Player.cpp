#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Engine.h"

void Player::Update()
{
	// ** MOVEMENT **
	// rotate left/right
	if (Bear::g_inputSystem.GetKeyDown(Bear::key_left))
	{
		m_transform.rotation -= Math::Pi * Bear::g_time.deltaTime;
	}

	if (Bear::g_inputSystem.GetKeyDown(Bear::key_right))
	{
		m_transform.rotation += Math::Pi * Bear::g_time.deltaTime;
	}

	// set thrust speed
	m_speed = 0;
	if (Bear::g_inputSystem.GetKeyDown(Bear::key_up))
	{
		m_speed = m_maxSpeed;
	}

	// calculate force
	Bear::Vector2 direction{ 1, 0 };
	direction = Bear::Vector2::Rotate(direction, m_transform.rotation);
	Bear::Vector2 force = direction * m_speed * Bear::g_time.deltaTime;

	//apply force to velocity
	m_velocity += force;

	//apply drag
	m_velocity *= 1.0f / (1.0f + m_damping * Bear::g_time.deltaTime);

	//move
	m_transform.position += m_velocity * Bear::g_time.deltaTime;

	// fire bullet
	if (Bear::g_inputSystem.GetKeyState(Bear::key_space) == Bear::InputSystem::KeyState::Pressed)
	{
		Bear::g_audioSystem.PlayAudio("laser");
		Bear::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(Bear::Model{ "Models/Bullet.txt" }, transform);
		bullet->GetTag() = "player";
		m_scene->Add(std::move(bullet));
	}

	// wrap
	if (m_transform.position.x > Bear::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)Bear::g_renderer.GetWidth();
	if (m_transform.position.y > Bear::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)Bear::g_renderer.GetHeight();
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "enemy")
	{
		m_health -= .5f;//dynamic_cast<Bullet*>(other)->GetDamage();

		m_scene->GetGame()->LoseHealth(.5f);
		if (m_health <= 0)
		{
			Bear::g_audioSystem.PlayAudio("explosion");
			m_destroy = true;
		}
	}
}


//mouse controls

//// face target
//Bear::Vector2 target = Bear::g_inputSystem.GetMousePosition();
//target = target - m_transform.position; // direction vector towards target from ship
//m_transform.rotation = target.GetAngle();