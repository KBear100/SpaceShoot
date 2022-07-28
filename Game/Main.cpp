#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include "SpaceShooter.h"

using namespace std;

int main()
{
	Bear::InitializeMemory();
	Bear::SetFilePath("../Assets");

	// initialize systems
	Bear::g_renderer.Initialize();
	Bear::g_inputSystem.Initialize();
	Bear::g_audioSystem.Initialize();

	// create window
	Bear::g_renderer.CreateWindow("Space Shoot", 800, 600);
	Bear::g_renderer.SetClearColor(Bear::Color{ 0, 0, 0, 255 });

	{
		// create game
		SpaceShooter game;
		game.Initialize();

		bool quit = false;
		while (!quit)
		{
			//update (engine)
			Bear::g_time.Tick();
			Bear::g_inputSystem.Update();
			Bear::g_audioSystem.Update();

			if (Bear::g_inputSystem.GetKeyDown(Bear::key_escape)) quit = true;

			game.Update();

			//render
			Bear::g_renderer.BeginFrame();

			game.Draw(Bear::g_renderer);

			Bear::g_renderer.EndFrame();
		}
	}

	Bear::g_renderer.ShutDown();
	Bear::g_audioSystem.ShutDown();
	Bear::g_inputSystem.ShutDown();
}