#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "scene/scene.h"
#include "math/linearAlgebra.h"

class Renderer
{
public:
	Renderer();
	void init();
	void renderFrame(const Scene& scene, const int Frame);

private:
	void outputFrame();

	std::unique_ptr<std::vector<MATH::vec4<>>> frameBuffer;
};

#endif // !RENDERER_H
