#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "scene/scene.h"
#include "math/linearAlgebra.h"
#include "settings.h"

class Renderer
{
public:
	Renderer();
	void init(const RenderSettings& rS);
	void renderFrame(const RenderSettings& rS, const Scene& scene, const int Frame);

private:
	void outputFrame(const RenderSettings& rS, const int Frame);

	std::unique_ptr<std::vector<MATH::vec4<>>> frameBuffer;
};

#endif // !RENDERER_H
