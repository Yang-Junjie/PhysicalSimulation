#ifndef PHYSICAL_SIMULATION_WORLD_HPP
#define PHYSICAL_SIMULATION_WORLD_HPP
#include "ps_common.hpp"
#include "ps_body.hpp"
#include "ps_math.hpp"
#include "ps_integrator.hpp"
#include "ps_joints.hpp"
#include "ps_random.hpp"
#include "ps_contact.hpp"

namespace ps
{
	class   PhysicsWorld
	{
	public:
		PhysicsWorld() : m_gravity(0, -9.8f), m_linearVelocityDamping(0.9f), m_angularVelocityDamping(0.9f),
		                 m_linearVelocityThreshold(0.02f), m_angularVelocityThreshold(0.02f),
		                 m_airFrictionCoefficient(0.7f), m_bias(0.8f)
		{
		}

		~PhysicsWorld();
		//disable copy
		PhysicsWorld(const PhysicsWorld&) = delete;
		PhysicsWorld& operator=(const PhysicsWorld&) = delete;
		void prepareVelocityConstraint(const real& dt);
		void stepVelocity(const real& dt);
		void solveVelocityConstraint(real dt);
		void stepPosition(const real& dt);
		void solvePositionConstraint(real dt);


		Vector2 gravity() const;
		void setGravity(const Vector2& gravity);

		real linearVelocityDamping() const;
		void setLinearVelocityDamping(const real& linearVelocityDamping);

		real angularVelocityDamping() const;
		void setAngularVelocityDamping(const real& angularVelocityDamping);

		real linearVelocityThreshold() const;
		void setLinearVelocityThreshold(const real& linearVelocityThreshold);

		real angularVelocityThreshold() const;
		void setAngularVelocityThreshold(const real& angularVelocityThreshold);

		real airFrictionCoefficient() const;
		void setAirFrictionCoefficient(const real& airFrictionCoefficient);

		bool enableGravity() const;
		void setEnableGravity(bool enableGravity);

		bool enableDamping() const;
		void setEnableDamping(bool enableDamping);

		Body* createBody();
		void removeBody(Body* body);

		void removeJoint(Joint* joint);

		void clearAllBodies();
		void clearAllJoints();

	
		PointJoint* createJoint(const PointJointPrimitive& primitive);
		DistanceJoint* createJoint(const DistanceJointPrimitive& primitive);
		

		real bias() const;
		void setBias(const real& bias);

		Container::Vector<std::unique_ptr<Body>>& bodyList();

		Container::Vector<std::unique_ptr<Joint>>& jointList();

		bool& enableSleep();

	private:
		Vector2 m_gravity;
		real m_linearVelocityDamping;
		real m_angularVelocityDamping;
		real m_linearVelocityThreshold;
		real m_angularVelocityThreshold;
		real m_airFrictionCoefficient;

		real m_bias;

		bool m_enableGravity = true;
		bool m_enableDamping = true;
		bool m_enableSleep = false;
		Container::Vector<std::unique_ptr<Body>> m_bodyList;
		Container::Vector<std::unique_ptr<Joint>> m_jointList;
	};

	class   DiscreteWorld
	{
	public:
		using ObjectID = uint32_t;
		ObjectID createBody(const ShapePrimitive& primitive);
		ObjectID createJoint();

		void step(real dt);
		void stepPosition(real dt);
		void stepVelocity(real dt);

		void removeBody(const ObjectID& id);
		void removeJoint(const ObjectID& id);

		void solveVelocity(real dt);
		void solvePosition(real dt);

	private:
		Container::Vector<ObjectID> m_bodyList;
		Container::Vector<ObjectID> m_jointList;
		Container::Vector<bool> m_sleepList;

		Vector2 m_gravity;
		real m_linearVelocityDamping = 0.9f;
		real m_angularVelocityDamping = 0.9f;
		real m_linearVelocityThreshold = 0.02f;
		real m_angularVelocityThreshold = 0.02f;
		real m_airFrictionCoefficient = 0.7f;
	};
}
#endif
