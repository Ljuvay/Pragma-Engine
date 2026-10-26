#include "engine/engine.h"

Engine::Engine() {
	m_SceneManager = std::make_unique<SceneManager>();
	m_Renderer = std::make_unique<Renderer>();
}

void Engine::init()
{
	m_SceneManager->init();
	m_Renderer->init();
	m_SceneManager->setScene("MandelBulbScene");
}

void Engine::run()
{
	for (int Frame{ 0 }; Frame < 60; Frame++) { //TEMPORARY FRAME LOOP, THE NUMBER OF FRAMES WILL LATER COME FROM SETTINGS
		m_SceneManager->updateCurrentScene(Frame);
		m_Renderer->renderFrame(*m_SceneManager->getCurrentScene(), Frame);
	}
}

void Engine::cleanup()
{
	m_SceneManager.release();
	m_Renderer.release();
}