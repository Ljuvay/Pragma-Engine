#pragma once

#include <cstdint>
#include <string>

constexpr std::string_view DEFAULT_OUTFILE_NAME = "output" ;
constexpr std::string_view DEFAULT_SCENE = "MandelBulbScene" ;
inline constexpr int DEFAULT_FRAME_COUNT{ 30 };
inline constexpr int DEFAULT_MAXSTEPS{200};
inline constexpr int DEFAULT_OUTPUT_WIDTH{ 1920 };
inline constexpr int DEFAULT_OUTPUT_HEIGHT{ 1080 };
inline constexpr double DEFAULT_NEAR_PLANE{ 0.01 };
inline constexpr double DEFAULT_FAR_PLANE{ 10.00 };
inline constexpr double DEFAULT_EPSILON{ 0.00001 };

struct RenderSettings
{

	std::string outputName{ DEFAULT_OUTFILE_NAME };
	std::string scene{ DEFAULT_SCENE };

	int outputWidth{ DEFAULT_OUTPUT_WIDTH };
	int outputHeight{ DEFAULT_OUTPUT_HEIGHT };
	int frameCount{ DEFAULT_FRAME_COUNT };

	double sNear{ DEFAULT_NEAR_PLANE };
	double sFar{ DEFAULT_FAR_PLANE };
	double epsilon{ DEFAULT_EPSILON };
	int maxSteps{ DEFAULT_MAXSTEPS };
};

typedef RenderSettings rs;