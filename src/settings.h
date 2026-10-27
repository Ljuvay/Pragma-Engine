#pragma once

#include <cstdint>
#include <string>

inline constexpr std::string_view DEFAULT_OUTFILE_NAME = "output" ;
inline constexpr std::string_view DEFAULT_SCENE = "FractalTowerScene" ;
inline constexpr double DEFAULT_NEAR_PLANE{ 0.01 };
inline constexpr double DEFAULT_FAR_PLANE{ 100.00 };
inline constexpr double DEFAULT_EPSILON{ 0.001 };
inline constexpr int DEFAULT_FRAME_COUNT{ 120 };
inline constexpr int DEFAULT_MAXSTEPS{5000};
inline constexpr int DEFAULT_OUTPUT_WIDTH{ 1920 };
inline constexpr int DEFAULT_THREAD_COUNT{ 14 };
inline constexpr int DEFAULT_TILE_RES{ 4 };
inline constexpr int DEFAULT_OUTPUT_HEIGHT{ 1080 };
inline constexpr bool DEFAULT_USE_DYNAMIC_THREADS{true};


struct RenderSettings
{
	std::string outputName{ DEFAULT_OUTFILE_NAME };
	std::string scene{ DEFAULT_SCENE };

	double sNear{ DEFAULT_NEAR_PLANE };
	double sFar{ DEFAULT_FAR_PLANE };
	double epsilon{ DEFAULT_EPSILON };
	int maxSteps{ DEFAULT_MAXSTEPS };

	int threads{ DEFAULT_THREAD_COUNT };
	int tileRes{ DEFAULT_TILE_RES };

	int outputWidth{ DEFAULT_OUTPUT_WIDTH };
	int outputHeight{ DEFAULT_OUTPUT_HEIGHT };
	int frameCount{ DEFAULT_FRAME_COUNT };

	bool dynamicSchedule{ DEFAULT_USE_DYNAMIC_THREADS };
};

typedef RenderSettings rs;