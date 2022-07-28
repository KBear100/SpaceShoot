#include "SpaceShooter.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"

void SpaceShooter::Initialize()
{
	m_scene = std::make_unique<Bear::Scene>(this);

	// sounds
	Bear::g_audioSystem.AddAudio("laser", "Sounds/laser.wav");
	Bear::g_audioSystem.AddAudio("explosion", "Sounds/Explosion.wav");
	Bear::g_audioSystem.AddAudio("music", "Sounds/Music.mp3");
	Bear::g_audioSystem.PlayAudio("music", true);

	// text
	m_font = std::make_unique<Bear::Font>("Fonts/Arcade.ttf", 24);

	m_titleText = std::make_unique<Bear::Text>(m_font.get());
	m_titleText->Create(Bear::g_renderer, "Space Shoot", { 0,255,255,255 });

	m_scoreText = std::make_unique<Bear::Text>(m_font.get());
	m_scoreText->Create(Bear::g_renderer, "000000", { 0,255,255,255 });

	m_healthText = std::make_unique<Bear::Text>(m_font.get());
	m_healthText->Create(Bear::g_renderer, "3", { 0,255,255,255 });

	m_scoreText2 = std::make_unique<Bear::Text>(m_font.get());
	m_scoreText2->Create(Bear::g_renderer, "Score:", { 0,255,255,255 });

	m_healthText2 = std::make_unique<Bear::Text>(m_font.get());
	m_healthText2->Create(Bear::g_renderer, "Health:", { 0,255,255,255 });

	Bear::ReadFile("HighScore.txt", m_highScore);
	m_highScoreText = std::make_unique<Bear::Text>(m_font.get());
	m_highScoreText->Create(Bear::g_renderer, m_highScore, { 0,255,255,255 });

	m_highScoreText2 = std::make_unique<Bear::Text>(m_font.get());
	m_highScoreText2->Create(Bear::g_renderer, "High Score:", { 0,255,255,255 });

	// ** CREATE ACTOR **
	// transform
	Bear::Transform transform;
	transform.position = Bear::Vector2{ 400, 300 };
	transform.rotation = 0;
	transform.scale = 3;

	std::unique_ptr<Player> player = std::make_unique<Player>(Bear::Model{ "Models/Player.txt" }, transform);
	m_scene->Add(std::move(player));

	// model
	for (int i = 0; i < 1; i++)
	{
		transform.position.x = Bear::random(800);
		transform.position.y = Bear::random(600);
		transform.rotation = Bear::randomf(Math::TwoPi);
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Bear::Model{ "Models/Enemy.txt" }, transform, 5);
		m_scene->Add(std::move(enemy));
	}
}

void SpaceShooter::Shutdown()
{

}

void SpaceShooter::Update()
{
	// spawn enemies
	m_spawnTimer -= Bear::g_time.deltaTime;
	if (m_spawnTimer <= 0)
	{
		m_spawnTimer = Bear::randomf(2);

		Bear::Transform transform;

		transform.position.x = Bear::random(800);
		transform.position.y = Bear::random(600);
		transform.rotation = Bear::randomf(Math::TwoPi);
		transform.scale = 3;
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Bear::Model{ "Models/Enemy.txt" }, transform, 5);
		m_scene->Add(std::move(enemy));
	}

	// update scene
	m_scene->Update();

	// update score text
	m_scoreText->Create(Bear::g_renderer, std::to_string(m_score), { 0, 255, 255, 255 });

	// update health
	m_healthText->Create(Bear::g_renderer, std::to_string(m_health), { 0, 255, 255, 255 });

	// update high score
	if (m_score > std::stoi(m_highScore))
	{
		m_highScore = std::to_string(m_score);
		m_highScoreText->Create(Bear::g_renderer, m_highScore, { 0, 255, 255, 255 });
		Bear::WriteFile("HighScore.txt", m_highScore);
	}
}

void SpaceShooter::Draw(Bear::Renderer& renderer)
{
	// render game objects
	m_scene->Draw(Bear::g_renderer);

	// render text
	m_titleText->Draw(Bear::g_renderer, { 340, 40 });

	m_scoreText->Draw(Bear::g_renderer, { 100, 70 });
	m_scoreText2->Draw(Bear::g_renderer, { 30, 70 });

	m_healthText->Draw(Bear::g_renderer, { 750, 70 });
	m_healthText2->Draw(Bear::g_renderer, { 680, 70 });

	m_highScoreText->Draw(Bear::g_renderer, { 150, 100 });
	m_highScoreText2->Draw(Bear::g_renderer, { 30, 100 });
}