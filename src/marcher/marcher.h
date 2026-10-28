#ifndef MARCHER_H
#define MARCHER_H

#include <cmath>

#include "math/linearAlgebra.h"
#include "scene/scene.h"

namespace sdf
{
	struct Paramaters
	{
		double sNear{};
		double sFar{};
		double epsilon{};
		int maxSteps{};
	};

	struct Ray
	{
		MATH::dvec3 origin;
		MATH::dvec3 direction;
		Ray(const MATH::dvec3& origin, const MATH::dvec3& direction)
			: origin(origin), direction(direction) {}
	};

	double distToSurface(const Ray& r, const Paramaters& p, const Scene& scene, hitInfo& info)
	{
		double depth{ p.sNear };
		info.epsilon = p.epsilon;
		info.maxSteps = p.maxSteps;
		for (int i = 0; i < p.maxSteps; i++)
		{
				double dist{ scene.eval(r.origin + r.direction * depth) };
				if (dist < p.epsilon) 
				{ 
					info.stopType = hitInfo::stopReason::HIT;
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

	inline MATH::dvec4 raymarchOnePixel(const Paramaters& p, const Ray& r, const Scene& scene)
	{
		hitInfo hit;
		double dist = distToSurface(r, p, scene, hit);
		return scene.shade(r.origin + r.direction * dist, hit);
	}
};

#endif // !MARCHER_H
