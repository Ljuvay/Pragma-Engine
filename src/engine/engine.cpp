#include "engine/engine.h"

Engine::Engine() {
	m_SceneManager = std::make_unique<SceneManager>();
	m_Renderer = std::make_unique<Renderer>();
}

void Engine::init(const RenderSettings& rS)
{
	m_SceneManager->init();
	m_Renderer->init(rS);
	m_SceneManager->setScene(rS.scene);
}

void Engine::run(const RenderSettings& rS)
{
	for (int Frame{ 0 }; Frame < rS.frameCount; Frame++) { //TEMPORARY FRAME LOOP, THE NUMBER OF FRAMES WILL LATER COME FROM SETTINGS
		m_SceneManager->updateCurrentScene(rS, Frame);
		m_Renderer->renderFrame(rS, *m_SceneManager->getCurrentScene(), Frame);
	}
}

void Engine::cleanup()
{
	m_SceneManager.release();
	m_Renderer.release();
}