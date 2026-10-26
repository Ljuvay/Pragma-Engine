#ifndef SCENE_H
#define SCENE_H

#include "math/linearAlgebra.h"

inline constexpr MATH::dvec3 DEFAULT_CAM_POS{0.0, 0.0, 0.0};
inline constexpr MATH::dvec3 DEFAULT_CAM_DIR{0.0, 0.0, 0.0};
inline constexpr MATH::dvec3 DEFAULT_CAM_UP{0.0, 1.0, 0.0};
inline constexpr int DEFAULT_SCR_WIDTH{1920};
inline constexpr int DEFAULT_SCR_HEIGHT{1080};
inline constexpr double DEFAULT_CAM_FOV{60.0};
inline constexpr double DEFAULT_ASPECT = static_cast<double>(DEFAULT_SCR_WIDTH) / static_cast<double>(DEFAULT_SCR_HEIGHT);

inline MATH::dvec3 estimateNormal(MATH::dvec3 p, double epsilon)
{
	return MATH::normalize(p);
}

struct Camera
{
	inline void updateView()
	{
		axis_view = MATH::unitVector(Direction);
		axis_up = MATH::unitVector(UpVector - axis_view * MATH::dot(UpVector, axis_view));
		axis_right = MATH::unitVector(MATH::cross(axis_view, axis_up));
		std::cout << axis_view << axis_up << axis_right;

		htanfov = std::tan(FOV * 0.5 * MATH::PI / 180.0);
		vtanfov = htanfov / DEFAULT_ASPECT;
	}

	const inline MATH::dvec3 getView( const double x, const double y) const
	{
		double xx = (2.0 * x - 1.0) * htanfov;
		double yy = (2.0 * y - 1.0) * vtanfov;
		return MATH::unitVector(UpVector * yy + axis_right * xx + axis_view);
	}

	MATH::dvec3 axis_view, axis_up, axis_right;

	MATH::dvec3 Position = DEFAULT_CAM_POS;
	MATH::dvec3 Direction = DEFAULT_CAM_DIR;
	MATH::dvec3 UpVector = DEFAULT_CAM_UP;
	double htanfov{0.0};
	double vtanfov{0.0};
	double FOV = DEFAULT_CAM_FOV;
	int width = DEFAULT_SCR_WIDTH;
	int height = DEFAULT_SCR_HEIGHT;
};

struct hitInfo
{
	double epsilon{};

	enum class stopReason
	{HIT, MISS, OUTOFSTEPS};

	int maxSteps{};
	int steps{};
	stopReason stopType = stopReason::OUTOFSTEPS;
};

class Scene
{
public:
	Scene() { cam = std::make_shared<Camera>(); }
	virtual ~Scene() = default;
	virtual void update(const int Frame) = 0;

	virtual double eval(const MATH::dvec3& p) const = 0;

	virtual MATH::dvec4 shade(const MATH::dvec3& p, const hitInfo& hI) const = 0;

	const std::shared_ptr<Camera> getCamera() const { return cam; }

protected:
	std::shared_ptr<Camera> cam{ nullptr };
};

class SphereScene : public Scene
{
public:
	void update(const int Frame) override;
	double eval(const MATH::dvec3& p) const override;
	MATH::dvec3 grad(const MATH::dvec3& p) const;
	MATH::dvec4 shade(const MATH::dvec3& p, const hitInfo& hI) const override;
};

class MandelBulbScene : public Scene
{
public:
	void update(const int Frame) override;
	double eval(const MATH::dvec3& P) const override;
	MATH::dvec3 grad(const MATH::dvec3& p) const;
	MATH::dvec4 shade(const MATH::dvec3& p, const hitInfo& hI) const override;
};

class KochSnowFlakeScene : public Scene
{
public:
	void update(const int Frame) override;
	double eval(const MATH::dvec3& P) const override;
	MATH::dvec3 grad(const MATH::dvec3& p) const;
	MATH::dvec4 shade(const MATH::dvec3& p, const hitInfo& hI) const override;
};

#endif // !SCENE_H
