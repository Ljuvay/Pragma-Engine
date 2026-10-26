#include <iostream>
#include "math/linearAlgebra.h"
#include "renderer/renderer.h"
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
#include "marcher/marcher.h"

/*
THIS WHOLE IMPLENTATION NEEDS TO HAVE SCREEN W/H SWAPPED IN FOR ACTUAL VALUES INSTEAD OF MAGIC NUMBERS
*/

Renderer::Renderer() {}

void Renderer::init()
{
    frameBuffer = std::make_unique<std::vector<MATH::vec4<>>>(1920*1080); 
}

void Renderer::renderFrame(const Scene& scene, const int Frame)
{
    auto sceneCam = scene.getCamera();
    sdf::Paramaters params;
    for (int py{ 0 }; py < 1080; py++) {
        for (int px{ 0 }; px < 1920; px++)
        {
            double x{ (px + 0.5) / static_cast<double>(1920) };
            double y{ (py + 0.5) / static_cast<double>(1080) };
            MATH::dvec3 direction = sceneCam->getView(x, 1.0 - y);
            sdf::Ray ray{ sceneCam->Position, direction};
            MATH::dvec4 thisPixelColor{ sdf::raymarchOnePixel(params, ray, scene) };

            int x2{ (py * 1920 + px) };
            (*frameBuffer)[x2].r = static_cast<float>(thisPixelColor.r);
            (*frameBuffer)[x2].g = static_cast<float>(thisPixelColor.g);
            (*frameBuffer)[x2].b = static_cast<float>(thisPixelColor.b);
            (*frameBuffer)[x2].a = static_cast<float>(thisPixelColor.a);
        }
    }
    outputFrame();
}

/*
This implementation is from the tinyEXR github example
*/
void Renderer::outputFrame()
{
    const char* error = NULL;
    int Save = SaveEXR(reinterpret_cast<const float*>(frameBuffer->data()), 1920, 1080, 4, 0, "output.exr", &error);
    if (Save < 0) { std::cerr << "ERROR SAVING EXR\n"; }
    FreeEXRErrorMessage(error);
    std::cout << "Image output\n";
}
