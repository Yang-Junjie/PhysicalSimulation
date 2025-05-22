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
	/**
	 * @class PhysicsWorld
	 * @brief Represents a 2D physics simulation world, managing bodies, joints, and global simulation parameters.
	 *
	 * The PhysicsWorld class encapsulates the state and behavior of a physical simulation environment.
	 * It manages collections of physical bodies and joints, and provides methods to step the simulation,
	 * apply global forces such as gravity, and configure simulation parameters like damping and friction.
	 *
	 * Key Features:
	 * - Manages a list of physical bodies and joints.
	 * - Supports creation and removal of bodies and joints.
	 * - Provides methods to advance the simulation in time, solving velocity and position constraints.
	 * - Allows configuration of global simulation parameters such as gravity, damping, velocity thresholds, air friction, and bias.
	 * - Supports enabling/disabling gravity, damping, and sleep optimization.
	 *
	 * @note Copying of PhysicsWorld instances is disabled.
	 *
	 * @constructor Initializes the physics world with default parameters.
	 * @destructor Cleans up all bodies and joints.
	 *
	 * @method prepareVelocityConstraint Prepares velocity constraints for the simulation step.
	 * @param dt The time step for the simulation.
	 *
	 * @method stepVelocity Advances the simulation by updating velocities.
	 * @param dt The time step for the simulation.
	 *
	 * @method solveVelocityConstraint Solves velocity constraints for the simulation step.
	 * @param dt The time step for the simulation.
	 *
	 * @method stepPosition Advances the simulation by updating positions.
	 * @param dt The time step for the simulation.
	 *
	 * @method solvePositionConstraint Solves position constraints for the simulation step.
	 * @param dt The time step for the simulation.
	 *
	 * @method gravity Gets the current gravity vector.
	 * @return The gravity vector.
	 *
	 * @method setGravity Sets the gravity vector.
	 * @param gravity The new gravity vector.
	 *
	 * @method linearVelocityDamping Gets the linear velocity damping factor.
	 * @return The linear velocity damping factor.
	 *
	 * @method setLinearVelocityDamping Sets the linear velocity damping factor.
	 * @param linearVelocityDamping The new linear velocity damping factor.
	 *
	 * @method angularVelocityDamping Gets the angular velocity damping factor.
	 * @return The angular velocity damping factor.
	 *
	 * @method setAngularVelocityDamping Sets the angular velocity damping factor.
	 * @param angularVelocityDamping The new angular velocity damping factor.
	 *
	 * @method linearVelocityThreshold Gets the linear velocity threshold for sleeping.
	 * @return The linear velocity threshold.
	 *
	 * @method setLinearVelocityThreshold Sets the linear velocity threshold for sleeping.
	 * @param linearVelocityThreshold The new linear velocity threshold.
	 *
	 * @method angularVelocityThreshold Gets the angular velocity threshold for sleeping.
	 * @return The angular velocity threshold.
	 *
	 * @method setAngularVelocityThreshold Sets the angular velocity threshold for sleeping.
	 * @param angularVelocityThreshold The new angular velocity threshold.
	 *
	 * @method airFrictionCoefficient Gets the air friction coefficient.
	 * @return The air friction coefficient.
	 *
	 * @method setAirFrictionCoefficient Sets the air friction coefficient.
	 * @param airFrictionCoefficient The new air friction coefficient.
	 *
	 * @method enableGravity Checks if gravity is enabled.
	 * @return True if gravity is enabled, false otherwise.
	 *
	 * @method setEnableGravity Enables or disables gravity.
	 * @param enableGravity True to enable gravity, false to disable.
	 *
	 * @method enableDamping Checks if damping is enabled.
	 * @return True if damping is enabled, false otherwise.
	 *
	 * @method setEnableDamping Enables or disables damping.
	 * @param enableDamping True to enable damping, false to disable.
	 *
	 * @method createBody Creates a new body in the world.
	 * @return Pointer to the created Body.
	 *
	 * @method removeBody Removes a body from the world.
	 * @param body Pointer to the Body to remove.
	 *
	 * @method removeJoint Removes a joint from the world.
	 * @param joint Pointer to the Joint to remove.
	 *
	 * @method clearAllBodies Removes all bodies from the world.
	 *
	 * @method clearAllJoints Removes all joints from the world.
	 *
	 * @method createJoint Creates a new PointJoint or DistanceJoint in the world.
	 * @param primitive The joint primitive describing the joint parameters.
	 * @return Pointer to the created joint.
	 *
	 * @method bias Gets the bias factor used in constraint resolution.
	 * @return The bias factor.
	 *
	 * @method setBias Sets the bias factor used in constraint resolution.
	 * @param bias The new bias factor.
	 *
	 * @method bodyList Gets the list of bodies in the world.
	 * @return Reference to the container of unique pointers to Body.
	 *
	 * @method jointList Gets the list of joints in the world.
	 * @return Reference to the container of unique pointers to Joint.
	 *
	 * @method enableSleep Gets or sets whether sleeping is enabled for bodies.
	 * @return Reference to the boolean flag for sleep enablement.
	 *
	 * @private
	 * @var m_gravity The gravity vector applied to all bodies.
	 * @var m_linearVelocityDamping The linear velocity damping factor.
	 * @var m_angularVelocityDamping The angular velocity damping factor.
	 * @var m_linearVelocityThreshold The linear velocity threshold for sleeping.
	 * @var m_angularVelocityThreshold The angular velocity threshold for sleeping.
	 * @var m_airFrictionCoefficient The air friction coefficient.
	 * @var m_bias The bias factor for constraint resolution.
	 * @var m_enableGravity Flag indicating if gravity is enabled.
	 * @var m_enableDamping Flag indicating if damping is enabled.
	 * @var m_enableSleep Flag indicating if sleeping is enabled.
	 * @var m_bodyList Container of unique pointers to Body objects.
	 * @var m_jointList Container of unique pointers to Joint objects.
	 */
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
