#include "ps_world.hpp"


namespace ps
{
	PhysicsWorld::~PhysicsWorld()
	{
		clearAllBodies();

		clearAllJoints();
	}

	void PhysicsWorld::prepareVelocityConstraint(const real& dt)
	{
		for (auto& joint : m_jointList)
			if (joint->active())
				joint->prepare(dt);
	}

	void PhysicsWorld::stepVelocity(const real& dt)
	{
		const Vector2 g = m_enableGravity ? m_gravity : Vector2{ 0.0, 0.0 };
		//std::cout<<m_gravity.x<<","<<m_gravity.y<<std::endl;
		real lvd = 1.0f;
		real avd = 1.0f;

		//damping ratio from box2d
		if (m_enableDamping)
		{
			lvd = 1.0f / (1.0f + dt * m_linearVelocityDamping);
			avd = 1.0f / (1.0f + dt * m_angularVelocityDamping);
		}
		for (auto& body : m_bodyList)
		{
			switch (body->type())
			{
			case Body::BodyType::Static:
			{
				body->velocity().clear();
				body->angularVelocity() = 0;
				break;
			}
			case Body::BodyType::Dynamic:
			{
				body->forces() += body->mass() * g;

				if (body->sleep() && body->kineticEnergy() > Constant::MinEnergy)
					body->setSleep(false);
				
				body->velocity() += body->inverseMass() * body->forces() * dt;
				//std::cout << body->velocity().x << "," << body->velocity().y << std::endl;
				//std::cout<<"velocity: "<<body->velocity().x<<","<<body->velocity().y<<std::endl;
				body->angularVelocity() += body->inverseInertia() * body->torques() * dt;

				body->velocity() *= lvd;

				break;
			}
			case Body::BodyType::Kinematic:
			{
				body->velocity() += body->inverseMass() * body->forces() * dt;
				body->angularVelocity() += body->inverseInertia() * body->torques() * dt;

				body->velocity() *= lvd;
				body->angularVelocity() *= avd;
				break;
			}
			case Body::BodyType::Bullet:
			{
				body->forces() += body->mass() * g;

				body->velocity() += body->inverseMass() * body->forces() * dt;
				body->angularVelocity() += body->inverseInertia() * body->torques() * dt;


				body->velocity() *= lvd;
				body->angularVelocity() *= avd;
				break;
			}
			}
		}
	}
	void PhysicsWorld::solveVelocityConstraint(real dt)
	{
		for (auto& joint : m_jointList)
			if (joint->active())
				joint->solveVelocity(dt);
	}
	void PhysicsWorld::solvePositionConstraint(real dt)
	{
		for (auto& joint : m_jointList)
			if (joint->active())
				joint->solvePosition(dt);
	}

	void PhysicsWorld::stepPosition(const real& dt)
	{

		for (auto& body : m_bodyList)
		{
			switch (body->type())
			{
			case Body::BodyType::Static:
				break;
			case Body::BodyType::Dynamic:
			{
				body->forces().clear();
				body->clearTorque();

				body->lastPosition() = body->position();
				body->lastRotation() = body->rotation();

				body->position() += body->velocity() * dt;
				body->rotation() += body->angularVelocity() * dt;

				if (body->sleep())
					break;

				if (m_enableSleep)
				{
					if (body->kineticEnergy() < Constant::MinEnergy)
						body->sleepCountdown()++;
					else
						body->sleepCountdown() = 0;

					if (body->sleepCountdown() >= Constant::SleepCountdown) {
						body->sleepCountdown() = 0;
						body->setSleep(true);
						body->velocity().clear();
						body->angularVelocity() = 0.0f;
					}
				}

				break;
			}
			case Body::BodyType::Kinematic:
			{
				body->position() += body->velocity() * dt;
				body->rotation() += body->angularVelocity() * dt;

				body->forces().clear();
				body->clearTorque();
				break;
			}
			case Body::BodyType::Bullet:
			{
				body->position() += body->velocity() * dt;
				body->rotation() += body->angularVelocity() * dt;

				body->forces().clear();
				body->clearTorque();

				if (body->velocity().lengthSquare() < Constant::CCDMinVelocity * Constant::CCDMinVelocity
					&& body->rotation() < Constant::CCDMinVelocity)
					body->setType(Body::BodyType::Dynamic);
				break;
			}
			}
		}

	}

	real PhysicsWorld::bias() const
	{
		return m_bias;
	}

	void PhysicsWorld::setBias(const real& bias)
	{
		m_bias = bias;
	}



	Container::Vector<std::unique_ptr<Body>>& PhysicsWorld::bodyList()
	{
		return m_bodyList;
	}

	Container::Vector<std::unique_ptr<Joint>>& PhysicsWorld::jointList()
	{
		return m_jointList;
	}

	bool& PhysicsWorld::enableSleep()
	{
		return m_enableSleep;
	}

	Vector2 PhysicsWorld::gravity() const
	{
		return m_gravity;
	}

	void PhysicsWorld::setGravity(const Vector2& gravity)
	{
		m_gravity = gravity;
	}

	real PhysicsWorld::linearVelocityDamping() const
	{
		return m_linearVelocityDamping;
	}

	void PhysicsWorld::setLinearVelocityDamping(const real& linearVelocityDamping)
	{
		m_linearVelocityDamping = linearVelocityDamping;
	}

	real PhysicsWorld::angularVelocityDamping() const
	{
		return m_angularVelocityDamping;
	}

	void PhysicsWorld::setAngularVelocityDamping(const real& angularVelocityDamping)
	{
		m_angularVelocityDamping = angularVelocityDamping;
	}

	real PhysicsWorld::linearVelocityThreshold() const
	{
		return m_linearVelocityThreshold;
	}

	void PhysicsWorld::setLinearVelocityThreshold(const real& linearVelocityThreshold)
	{
		m_linearVelocityThreshold = linearVelocityThreshold;
	}

	real PhysicsWorld::angularVelocityThreshold() const
	{
		return m_angularVelocityThreshold;
	}

	void PhysicsWorld::setAngularVelocityThreshold(const real& angularVelocityThreshold)
	{
		m_angularVelocityThreshold = angularVelocityThreshold;
	}

	real PhysicsWorld::airFrictionCoefficient() const
	{
		return m_airFrictionCoefficient;
	}

	void PhysicsWorld::setAirFrictionCoefficient(const real& airFrictionCoefficient)
	{
		m_airFrictionCoefficient = airFrictionCoefficient;
	}

	bool& PhysicsWorld::enableGravity()
	{
		return m_enableGravity;
	}

	void PhysicsWorld::setEnableGravity(bool enableGravity)
	{
		m_enableGravity = enableGravity;
	}

	bool& PhysicsWorld::enableDamping() 
	{
		return m_enableDamping;
	}

	void PhysicsWorld::setEnableDamping(bool enableDamping)
	{
		m_enableDamping = enableDamping;
	}


	Body* PhysicsWorld::createBody()
	{
		auto body = std::make_unique<Body>();
		Body* temp = body.get();
		temp->setId(RandomGenerator::unique());
		m_bodyList.emplace_back(std::move(body));
		return temp;
	}

	void PhysicsWorld::removeBody(Body* body)
	{
		for (auto iter = m_bodyList.begin(); iter != m_bodyList.end(); ++iter)
		{
			if (iter->get() == body)
			{
				RandomGenerator::pop(body->id());
				iter->release();
				m_bodyList.erase(iter);
				break;
			}
		}
	}

	void PhysicsWorld::removeJoint(Joint* joint)
	{
		for (auto iter = m_jointList.begin(); iter != m_jointList.end(); ++iter)
		{
			if (iter->get() == joint)
			{
				RandomGenerator::pop(joint->id());
				iter->release();
				m_jointList.erase(iter);
				break;
			}
		}
	}

	void PhysicsWorld::clearAllBodies()
	{
		for (auto& body : m_bodyList)
			body.release();
		m_bodyList.clear();
	}

	void PhysicsWorld::clearAllJoints()
	{
		for (auto& joint : m_jointList)
			joint.release();
		m_jointList.clear();
	}

	PointJoint* PhysicsWorld::createJoint(const PointJointPrimitive& primitive)
	{
		auto joint = std::make_unique<PointJoint>(primitive);
		PointJoint* temp = joint.get();
		temp->setId(RandomGenerator::unique());
		m_jointList.emplace_back(std::move(joint));
		return temp;
	}

	DistanceJoint* PhysicsWorld::createJoint(const DistanceJointPrimitive& primitive)
	{
		auto joint = std::make_unique<DistanceJoint>(primitive);
		DistanceJoint* temp = joint.get();
		temp->setId(RandomGenerator::unique());
		m_jointList.emplace_back(std::move(joint));
		return temp;
	}
	RevoluteJoint* PhysicsWorld::createJoint(const RevoluteJointPrimitive& primitive)
	{
		auto joint = std::make_unique<RevoluteJoint>(primitive);
		RevoluteJoint* temp = joint.get();
		temp->setId(RandomGenerator::unique());
		m_jointList.emplace_back(std::move(joint));
		return temp;
	}

}
