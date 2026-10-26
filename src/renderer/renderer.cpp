#include <iomanip>
#include <sstream>
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

void Renderer::init(const RenderSettings& rS)
{
    frameBuffer = std::make_unique<std::vector<MATH::vec4<>>>(rS.outputWidth*rS.outputHeight); 
}

void Renderer::renderFrame(const RenderSettings& rS, const Scene& scene, const int Frame)
{
    int width{ rS.outputWidth };
    int height{ rS.outputHeight };
    auto sceneCam = scene.getCamera();
    sdf::Paramaters params{ rS.sNear, rS.sFar, rS.epsilon, rS.maxSteps };
    for (int py{ 0 }; py < height; py++) {
        for (int px{ 0 }; px < width; px++)
        {
            double x{ (px + 0.5) / static_cast<double>(width) };
            double y{ (py + 0.5) / static_cast<double>(height) };
            MATH::dvec3 direction = sceneCam->getView(x, 1.0 - y);
            sdf::Ray ray{ sceneCam->Position, direction};
            MATH::dvec4 thisPixelColor{ sdf::raymarchOnePixel(params, ray, scene) };

            int x2{ (py * width + px) };
            (*frameBuffer)[x2].r = static_cast<float>(thisPixelColor.r);
            (*frameBuffer)[x2].g = static_cast<float>(thisPixelColor.g);
            (*frameBuffer)[x2].b = static_cast<float>(thisPixelColor.b);
            (*frameBuffer)[x2].a = static_cast<float>(thisPixelColor.a);
        }
    }
    outputFrame(rS, Frame);
}

/*
This implementation is from the tinyEXR github example
*/
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
