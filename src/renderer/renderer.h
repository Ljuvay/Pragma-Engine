#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "scene/scene.h"
#include "math/linearAlgebra.h"
#include "settings.h"

struct Tile
{
	int x, y; // x/y position
	int w, h; // w/h of tile
};

class Renderer
{
public:
	Renderer();
	void init(const RenderSettings& rS);
	void renderFrame(const RenderSettings& rS, const Scene& scene, const int Frame);
	void renderTile(const RenderSettings& rS, const Scene& scene, const int tileIdx);

	void renderStatic(const RenderSettings& rS, const Scene& scene, const int Frame);
	void renderDynamic(const RenderSettings& rS, const Scene& scene, const int Frame);

private:
	void buildTiles(const RenderSettings& rS);

	void outputFrame(const RenderSettings& rS, const int Frame);

	static uint16_t determineThreadCount(const uint16_t inputThreads);

	std::vector<Tile> renderTiles;
	std::unique_ptr<std::vector<MATH::vec4<>>> frameBuffer;
};

#endif // !RENDERER_H
