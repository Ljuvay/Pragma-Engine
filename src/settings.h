#pragma once

#include <cstdint>
#include <string>

inline constexpr std::string DEFAULT_OUTFILE_NAME{ "" };
inline constexpr std::string DEFAULT_SCENE{ "SphereScene" };
inline constexpr int DEFAULT_MAXSTEPS{200};
inline constexpr double DEFAULT_NEAR_PLANE{ 0.01 };
inline constexpr double DEFAULT_FAR_PLANE{ 10.00 };
inline constexpr double DEFAULT_EPSILON{ 0.00001 };

struct RenderSettings
{
	std::string outputName{ DEFAULT_OUTFILE_NAME };
	std::string scene{ DEFAULT_SCENE };

	double near{ DEFAULT_NEAR_PLANE };
	double far{ DEFAULT_FAR_PLANE };
	double epsilon{ DEFAULT_EPSILON };
	int maxSteps{ DEFAULT_MAXSTEPS };

};

typedef RenderSettings rs;