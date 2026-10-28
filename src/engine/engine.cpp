#include "engine/engine.h"

Engine::Engine() {
	m_SceneManager = std::make_unique<SceneManager>();
	m_Renderer = std::make_unique<Renderer>();
	m_Logger = std::make_unique<LOGGING::Logger>();
}

void Engine::init(const RenderSettings& rS)
{
	m_SceneManager->init();
	m_Renderer->init(rS);
	m_SceneManager->setScene(rS.scene);
}

void Engine::run(const RenderSettings& rS)
{
	if(rS.loggingOn == true) m_Logger->createInstance("Entire Render");

	for (int Frame{ 0 }; Frame < rS.frameCount; Frame++) { 
		m_SceneManager->updateCurrentScene(rS, Frame);
		m_Renderer->renderFrame(rS, *m_Logger.get(), *m_SceneManager->getCurrentScene(), Frame);
	}

	if (rS.loggingOn == true) {
		m_Logger->stopInstance("Entire Render");
		m_Logger->writeInstance("Entire Render");
	}
}

void Engine::cleanup()
{
	m_SceneManager.reset();
	m_Renderer.reset();
	m_Logger.reset();
}