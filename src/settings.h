#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>
#include <string_view>

inline constexpr std::string_view DEFAULT_OUTFILE_NAME = "output" ;
inline constexpr std::string_view DEFAULT_SCENE = "MandelBulbScene" ;
inline constexpr double DEFAULT_NEAR_PLANE{ 0.01 };
inline constexpr double DEFAULT_FAR_PLANE{ 100.00 };
inline constexpr double DEFAULT_EPSILON{ 0.0001 };
inline constexpr int DEFAULT_FRAME_COUNT{ 24 };
inline constexpr int DEFAULT_MAXSTEPS{500};
inline constexpr int DEFAULT_OUTPUT_WIDTH{ 1920 };
inline constexpr int DEFAULT_THREAD_COUNT{ 1 };
inline constexpr int DEFAULT_TILE_RES{ 16 }; //16x16 tiles
inline constexpr int DEFAULT_OUTPUT_HEIGHT{ 1080 };
inline constexpr bool DEFAULT_USE_DYNAMIC_THREADS{false};
inline constexpr bool DEFAULT_USE_LOGGING{false};

struct RenderSettings
{
	RenderSettings(int argc, char** argv)
	{
		for (int i = 1; i < argc; i++)
		{
			std::string input = argv[i];

			// File Settings
			if (input == "-w") this->outputWidth = std::atoi(argv[++i]);
			if (input == "-h") this->outputHeight = std::atoi(argv[++i]);
			if (input == "-fName") this->outputName = argv[++i];

			// Scene Settings
			if (input == "-scene") this->scene = argv[++i];
			if (input == "-frames") this->frameCount = std::atoi(argv[++i]);

			// Render Settings
			if (input == "-steps") this->maxSteps = std::atoi(argv[++i]);
			if (input == "-near") this->sNear = std::atof(argv[++i]);
			if (input == "-far") this->sFar = std::atof(argv[++i]);
			if (input == "-epsilon") this->epsilon = std::atof(argv[++i]);

			// Performance Settings
			if (input == "-threads") this->threads = atoi(argv[++i]);
			if (input == "-tres") this->tileRes = atoi(argv[++i]);
			if (input == "-dynamic") this->dynamicSchedule = true;

			// Logger Settings
			if (input == "-logging") this->loggingOn = true;
		}
	}

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
	bool loggingOn{ DEFAULT_USE_LOGGING };
};