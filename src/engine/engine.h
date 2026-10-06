#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "renderer/renderer.h"
#include "scene/sceneManager.h"

class Engine
{
public:
	Engine();
	void init();
	void run();
	void cleanup();

private:
	std::unique_ptr<SceneManager> m_SceneManager = nullptr;
	std::unique_ptr<Renderer> m_Renderer = nullptr;
};

#endif // !ENGINE_H
