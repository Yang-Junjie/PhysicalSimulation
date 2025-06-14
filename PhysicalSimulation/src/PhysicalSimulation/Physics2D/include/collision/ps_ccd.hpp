#ifndef PHYSICAL_SIMULATION_CCD_HPP
#define PHYSICAL_SIMULATION_CCD_HPP
#include "ps_detector.hpp"

#include "ps_body.hpp"
#include "ps_grid.hpp"
#include "ps_tree.hpp"

namespace ps
{
	class CCD
	{
	public:
		struct AABBShot
		{
			AABBShot(const AABB &box, const Body::PhysicsAttribute &attr, const real &t) : aabb(box), attribute(attr),
																						   time(t)
			{
			}

			AABB aabb;
			Body::PhysicsAttribute attribute;
			real time = 0;
		};

		struct IndexSection
		{
			int forward = -1;
			int backward = -1;
		};

		struct CCDPair
		{
			CCDPair() = default;

			CCDPair(const real &time, Body *target) : toi(time), body(target)
			{
			}

			real toi = 0.0;
			Body *body = nullptr;
		};

		using BroadphaseTrajectory = Container::Vector<AABBShot>;
		static std::tuple<BroadphaseTrajectory, AABB> buildTrajectoryAABB(Body *body, const real &dt);
		
		static std::tuple<Container::Vector<AABBShot>, AABB> buildTrajectoryAABB(Body *body, const Vector2 &target, const real &dt);

		static std::optional<IndexSection> findBroadphaseRoot(Body *staticBody,
															  const BroadphaseTrajectory &staticTrajectory,
															  Body *dynamicBody,
															  const BroadphaseTrajectory &dynamicTrajectory,
															  const real &dt);

		static std::optional<real> findNarrowphaseRoot(Body *staticBody,
													   const BroadphaseTrajectory &staticTrajectory,
													   Body *dynamicBody,
													   const BroadphaseTrajectory &dynamicTrajectory,
													   const IndexSection &index,
													   const real &dt);

		static std::optional<Container::Vector<CCDPair>> query(Tree &tree, Body *body, const real &dt);
		static std::optional<Container::Vector<CCDPair>> query(UniformGrid &grid, Body *body, const real &dt);
		static std::optional<real> earliestTOI(const Container::Vector<CCDPair> &pairs,
											   const real &epsilon = Constant::GeometryEpsilon);
	};
}
#endif
