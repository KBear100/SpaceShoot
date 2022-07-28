#pragma once
#include "Framework/Game.h"
#include <string>

namespace Bear
{
	class Font;
	class Text;
}

class SpaceShooter : public Bear::Game
{
public:
	SpaceShooter() = default;
	~SpaceShooter() = default;

	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(Bear::Renderer& renderer) override;

private:
	float m_spawnTimer = 2;
	std::string m_highScore;

	std::unique_ptr<Bear::Font> m_font;
	std::unique_ptr<Bear::Text> m_titleText;
	std::unique_ptr<Bear::Text> m_scoreText;
	std::unique_ptr<Bear::Text> m_scoreText2;
	std::unique_ptr<Bear::Text> m_healthText;
	std::unique_ptr<Bear::Text> m_healthText2;
	std::unique_ptr<Bear::Text> m_highScoreText;
	std::unique_ptr<Bear::Text> m_highScoreText2;
};