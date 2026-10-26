#ifndef MARCHER_H
#define MARCHER_H

#include <cmath>

#include "math/linearAlgebra.h"
#include "scene/scene.h"

inline constexpr double DEFAULT_NEAR_PLANE{ 0.01 };
inline constexpr double DEFAULT_FAR_PLANE{ 10.00 };
inline constexpr double DEFAULT_EPSILON = 0.0001;
inline constexpr int DEFAULT_MAXSTEPS = 500;

namespace sdf
{
	struct Paramaters
	{
		double sNear = DEFAULT_NEAR_PLANE;
		double sFar = DEFAULT_FAR_PLANE;
		double epsilon = DEFAULT_EPSILON;
		int maxSteps = DEFAULT_MAXSTEPS;
	};

	struct Ray
	{
		MATH::dvec3 direction;
		MATH::dvec3 origin;
		Ray(const MATH::dvec3& origin, const MATH::dvec3& direction)
			: origin(origin), direction(direction) {}
	};

	// kawmekdma
	double distToSurface(const Ray& r, const Paramaters& p, const Scene& scene, hitInfo& info)
	{
		double depth{ p.sNear };
		for (int i = 0; i < p.maxSteps; i++)
		{
				double dist{ scene.eval(r.origin + r.direction * depth) };
				if (dist < p.epsilon) 
				{ 
					info.stopType = hitInfo::stopReason::HIT;
					info.maxSteps = p.maxSteps;
					info.steps = i;
					return depth; 
				}
				depth += dist;
				if (depth >= p.sFar) 
				{ 
					info.stopType = hitInfo::stopReason::MISS;
					return p.sFar; 
				}
		}
		info.stopType = hitInfo::stopReason::OUTOFSTEPS;
		return p.sFar;
	}

	// gjnwjdcanwkdnk
	inline MATH::dvec4 raymarchOnePixel(const Paramaters& p, const Ray& r, const Scene& scene)
	{
		hitInfo hit;
		double dist = distToSurface(r, p, scene, hit);
		/*if (dist > p.sFar - p.epsilon)
		{
			return MATH::dvec4(0.0,0.0,0.0,0.0);
		}*/
		return scene.shade(r.origin + r.direction * dist, hit);
	}
};

#endif // !MARCHER_H
