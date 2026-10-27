#include <iomanip>
#include <sstream>
#include <iostream>
#include <thread>
#include <atomic>
#include <algorithm>

#include "math/linearAlgebra.h"
#include "renderer/renderer.h"
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
#include "marcher/marcher.h"

/*
THIS WHOLE IMPLENTATION NEEDS TO HAVE SCREEN W/H SWAPPED IN FOR ACTUAL VALUES INSTEAD OF MAGIC NUMBERS
*/

Renderer::Renderer() {}

void Renderer::init(const RenderSettings& rS)
{
    frameBuffer = std::make_unique<std::vector<MATH::vec4<>>>(rS.outputWidth*rS.outputHeight); 
}

void Renderer::renderFrame(const RenderSettings& rS, const Scene& scene, const int Frame)
{
    renderTiles.clear();
    buildTiles(rS);
    rS.dynamicSchedule ? renderDynamic(rS, scene, Frame) : renderStatic(rS, scene, Frame);
    outputFrame(rS, Frame);
}

void Renderer::renderTile(const RenderSettings& rS, const Scene& scene, const int tileIdx)
{
    Tile currTile = renderTiles[tileIdx];
    int startX{ currTile.x }, finishX{ currTile.x + currTile.w };
    int startY{ currTile.y }, finishY{ currTile.y + currTile.h };
    int width{ rS.outputWidth };
    int height{ rS.outputHeight };
    auto sceneCam = scene.getCamera();
    sdf::Paramaters params{ rS.sNear, rS.sFar, rS.epsilon, rS.maxSteps };
    for (int py{ startY }; py < finishY; py++) {
        for (int px{ startX }; px < finishX; px++) {
            double x{ (px + 0.5) / static_cast<double>(width) };
            double y{ (py + 0.5) / static_cast<double>(height) };
            MATH::dvec3 direction = sceneCam->getView(x, 1.0 - y);
            sdf::Ray ray{ sceneCam->Position, direction };
            MATH::dvec4 thisPixelColor{ sdf::raymarchOnePixel(params, ray, scene) };

            int x2{ (py * width + px) };
            (*frameBuffer)[x2].r = static_cast<float>(thisPixelColor.r);
            (*frameBuffer)[x2].g = static_cast<float>(thisPixelColor.g);
            (*frameBuffer)[x2].b = static_cast<float>(thisPixelColor.b);
            (*frameBuffer)[x2].a = static_cast<float>(thisPixelColor.a);
        }
    }
}

void Renderer::renderStatic(const RenderSettings& rS, const Scene& scene, const int Frame)
{
    uint16_t threadCount = determineThreadCount(rS.threads);

    auto worker = [&](int id) {
        while (true) {
            if (static_cast<size_t>(id) >= renderTiles.size()) break;
            renderTile(rS, scene, id);
            id += threadCount;
        }
    };

    std::vector<std::thread> threadPool;
    for (int id{}; id < threadCount; id++)
    {
        threadPool.emplace_back(worker, id);
    }

    for (auto& t : threadPool)
    {
        t.join();
    }
}

void Renderer::renderDynamic(const RenderSettings& rS, const Scene& scene, const int Frame)
{
    std::atomic<size_t> next{};
    auto worker = [&]() {
        while (true) {
            size_t i = next.fetch_add(1);
            if (i >= renderTiles.size()) break;
            renderTile(rS, scene, i);
        }
    };

    uint16_t threadCount = determineThreadCount(rS.threads);

    std::vector<std::thread> threadPool;
    for (int i{}; i < threadCount; i++)
    {
        threadPool.emplace_back(worker);
    }

    for (auto& t : threadPool)
    {
        t.join();
    }
}

void Renderer::buildTiles(const RenderSettings& rS)
{
    int width = { rS.outputWidth };
    int height = { rS.outputHeight };

    int res = std::max(rS.tileRes, 1);
    int TileW = width / res; // Res of 1 is just the full screen
    int TileH = height / res;

    for (int tx{}; tx < res; tx++) {
        for (int ty{}; ty < res; ty++){
            Tile newTile;
            newTile.w = TileW;
            newTile.h = TileH;
            newTile.x = TileW * tx;
            newTile.y = TileH * ty;

            if (tx == res - 1 && width % res != 0) {
                newTile.w += width % res;
            }
            if (ty == res - 1 && height % res != 0) {
                newTile.h += height % res;
            }

            renderTiles.push_back(newTile);
        }
    }
}

void Renderer::outputFrame(const RenderSettings& rS, const int Frame)
{
    std::cout << "Outputting Frame" << std::endl;
    std::ostringstream frameName;
    frameName << "../../../outputs/" << rS.outputName << "." << std::setw(4) << std::setfill('0') << Frame << ".exr";

    const char* error = nullptr;
    int Save = SaveEXR(reinterpret_cast<const float*>(frameBuffer->data()), rS.outputWidth, rS.outputHeight, 4, 0, frameName.str().c_str(), &error);
    if (Save < 0) {
        std::cerr << "ERROR SAVING EXR\n";
        if (error != nullptr) {
            std::cerr << error << std::endl;
        }
    }
    if (error != nullptr) { FreeEXRErrorMessage(error); }
    std::cout << "Image output\n";
}

uint16_t Renderer::determineThreadCount(const uint16_t inputThreads)
{
    uint16_t maxSysThreads = std::max(static_cast<uint16_t>(1), static_cast<uint16_t>(std::thread::hardware_concurrency()));
    uint16_t threadCount = inputThreads;
    uint16_t minThreads = 1;
    if (threadCount == 0 || threadCount > maxSysThreads)
    {
        std::cerr << "Invalid Specified Thread Count\n" <<
            "Thread Count Clamped to [1, " << maxSysThreads << "]" << std::endl;
        threadCount = std::clamp(threadCount, minThreads, maxSysThreads);
    }

    return threadCount;
}