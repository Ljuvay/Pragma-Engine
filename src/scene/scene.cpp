#include <cmath>

#include "scene/scene.h"

/*
Equations are implemented from jbaker.graphics/writings/DEC.html
*/

void SphereScene::update(const int Frame)
{
	cam->Position = { 0.0, 0.0, 5.0 };
	cam->Direction = MATH::unitVector(MATH::dvec3(0.0, 0.0, 1.0) - cam->Position);
	cam->updateView();
}

double SphereScene::eval(const MATH::dvec3& p) const
{
	double r{ 1.0 }; // Radius
	return MATH::length(p) - r;
}

MATH::dvec3 SphereScene::grad(const MATH::dvec3& p) const
{
	double r{ 1.0 };
	MATH::dvec3 top = p - MATH::dvec3(0.0, 0.0, 0.0);
	return top / (length(p) - r);
}

MATH::dvec4 SphereScene::shade(const MATH::dvec3& p, const hitInfo& hI) const
{
	return MATH::dvec4(1.0, 0.0, 0.0, 1.0);
}

void MandelBulbScene::update(const int Frame)
{
	cam->Position = { 0.0, 0.0, 5.0 };
	cam->Direction = MATH::unitVector(MATH::dvec3(0.0, 0.0, 1.0) - cam->Position);
	cam->updateView();
}

//https://icefractal.com/articles/mandelbulb/
double MandelBulbScene::eval(const MATH::dvec3& p) const
{
	MATH::dvec3 z = p;
	double r{};
	double dr{ 1.0 };
	const double power = 8.0;

	for (int n{}; n < 12; n++)
	{
		r = MATH::length(z);
		if (r > 2.0)break;

		double phi = std::asin(z.z / r);
		double theta = std::atan2(z.y, z.x);
		double derivpow = std::pow( r, power - 1.0);
		dr = derivpow * power * dr + 1.0;

		phi = phi * power;
		theta = theta * power;

		z =  MATH::dvec3(std::cos(theta) * std::cos(phi), std::sin(theta) * std::cos(phi), std::sin(phi)) * (derivpow * r);
		z = z + p;
	}
	return 0.5 * std::log(r) * r / dr;
}

MATH::dvec3 MandelBulbScene::grad(const MATH::dvec3& p) const
{
	return MATH::dvec3(0.0, 0.0, 0.0);
}

MATH::dvec4 MandelBulbScene::shade(const MATH::dvec3& p, const hitInfo& hI) const
{
	switch (hI.stopType)
	{
	case hitInfo::stopReason::HIT:
		return MATH::dvec4((1.0 / hI.maxSteps) * hI.steps * p.x, (1.0 / hI.maxSteps) * hI.steps * p.y, (1.0 / hI.maxSteps) * hI.steps, 1.0);
	case hitInfo::stopReason::MISS:
		return MATH::dvec4(0.1, 0.1, 0.1, 1.0);
	case::hitInfo::stopReason::OUTOFSTEPS:
		return MATH::dvec4(1.0, 0.0, 0.0, 1.0);
	default:
		return MATH::dvec4(1.0, 0.0, 1.0, 1.0);
	}

}

void KochSnowFlakeScene::update(const int Frame)
{

}

double KochSnowFlakeScene::eval(const MATH::dvec3& p) const
{
	return 0.8;
}

MATH::dvec3 KochSnowFlakeScene::grad(const MATH::dvec3& p) const
{
	return MATH::dvec3(0.0, 0.0, 0.0);
}

MATH::dvec4 KochSnowFlakeScene::shade(const MATH::dvec3& p, const hitInfo& hI) const
{
	return MATH::dvec4(0.0, 0.0, 0.0, 0.0);
}