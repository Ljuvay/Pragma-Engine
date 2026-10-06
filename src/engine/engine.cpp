#include "engine/engine.h"

Engine::Engine() {
	m_SceneManager = std::make_unique<SceneManager>();
	m_Renderer = std::make_unique<Renderer>();
}

void Engine::init()
{

}

void Engine::run()
{

}

void Engine::cleanup()
{
	m_SceneManager.release();
	m_Renderer.release();
}