#ifndef PHYSICAL_SIMULATION_JOINT_POINT_HPP
#define PHYSICAL_SIMULATION_JOINT_POINT_HPP
#include "ps_joint.hpp"

namespace ps
{
	struct PointJointPrimitive
	{
		Body *bodyA = nullptr;
		Vector2 localPointA;
		Vector2 targetPoint;
		Vector2 normal;

		real damping = 0.0;
		real stiffness = 0.0;
		real frequency = 10;
		real maxForce = 1000;
		real dampingRatio = 0.707f;
		real gamma = 0.0;
		Vector2 bias;
		Matrix2x2 effectiveMass;
		Vector2 accumulatedImpulse;

		void clear()
		{
			accumulatedImpulse.clear();
			effectiveMass.clear();
			bias.clear();
		}
	};

	class PointJoint : public Joint
	{
	private:
		PointJointPrimitive m_primitive;
		real m_factor = 0.22f;

	public:
		PointJoint();

		PointJoint(const PointJointPrimitive &prim);

		void set(const PointJointPrimitive &prim);

		void prepare(const real &dt) override;

		void solveVelocity(const real &dt) override;

		void solvePosition(const real &dt) override;

		PointJointPrimitive &primitive();
	};
}
#endif
