#ifndef PHYSICAL_SIMULATION_JOINT_DISTANCE_HPP
#define PHYSICAL_SIMULATION_JOINT_DISTANCE_HPP
#include "ps_joint.hpp"
namespace ps
{
	struct DistanceJointPrimitive
	{
		Body *bodyA = nullptr;
		Body *bodyB = nullptr;

		Vector2 localPointA;
		Vector2 localPointB;

		real minDistance = 0.0f;
		real maxDistance = 0.0f;

		Vector2 normal;
		real biasFactor = 0.3f;
		Vector2 bias = 0.0f;
		real effectiveMass = 0.0f;
		real accumulatedImpulse = 0.0f;

		real damping = 0.0;
		real stiffness = 0.0;
		real frequency = 5;
		real maxForce = 5000;
		real dampingRatio = 0.707f;
		real gamma = 0.0;

		real length = 0.0f;
		real currentLength = 0.0f;
	};
	class DistanceJoint : public Joint
	{
	private:
		real m_factor = 0.4f;
		DistanceJointPrimitive m_primitive;

	public:
		DistanceJoint();

		DistanceJoint(const DistanceJointPrimitive &primitive);

		void set(const DistanceJointPrimitive &primitive);

		void prepare(const real &dt) override;

		void solveVelocity(const real &dt) override;

		void solvePosition(const real &dt) override;

		DistanceJointPrimitive &primitive();
	};

}
#endif