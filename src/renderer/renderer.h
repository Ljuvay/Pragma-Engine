#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

#include "marcher/marcher.h"
#include "scene/scene.h"

class Renderer
{
public:
	Renderer();
	void init();
	void renderFrame();

private:
	std::shared_ptr<Scene> m_Scene;
	std::unique_ptr<Marcher> m_Marcher;

};

#endif // !RENDERER_H
