#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "marcher/marcher.h"
#include "scene/scene.h"
#include "math/linearAlgebra.h"

class Renderer
{
public:
	Renderer();
	void init();
	void renderFrame();
	bool saveEXR(const float* rgb, int width, int height, const char* outfilename);

private:
	std::shared_ptr<Scene> m_Scene;
	std::unique_ptr<Marcher> m_Marcher;
	std::unique_ptr<std::vector<MATH::vec3f>> frameBuffer;
};

#endif // !RENDERER_H
