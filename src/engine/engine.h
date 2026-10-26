#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "renderer/renderer.h"
#include "scene/sceneManager.h"
#include "settings.h"

class Engine
{
public:
	Engine();
	void init(const RenderSettings& rS);
	void run(const RenderSettings& rS);
	void cleanup();

private:
	std::unique_ptr<SceneManager> m_SceneManager = nullptr;
	std::unique_ptr<Renderer> m_Renderer = nullptr;
};

#endif // !ENGINE_H
