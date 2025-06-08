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
	class PhysicsWorld
	/**
	 * @class PhysicsWorld
	 * @brief 表示一个二维物理仿真世界，管理刚体、关节和全局仿真参数。
	 *
	 * PhysicsWorld 类封装了物理模拟环境的状态和行为。
	 * 它管理物理刚体和关节的集合，并提供推进仿真、施加重力等全局力、
	 * 配置阻尼、摩擦等仿真参数的方法。
	 *
	 * 主要特性：
	 * - 管理物理刚体和关节的列表。
	 * - 支持刚体和关节的创建与移除。
	 * - 提供推进仿真、求解速度和位置约束的方法。
	 * - 支持配置重力、阻尼、速度阈值、空气摩擦、偏置等全局参数。
	 * - 支持开启/关闭重力、阻尼和休眠优化。
	 *
	 * @note 禁止拷贝 PhysicsWorld 实例。
	 *
	 * @constructor 使用默认参数初始化物理世界。
	 * @destructor 清理所有刚体和关节。
	 *
	 * @method prepareVelocityConstraint 为仿真步准备速度约束。
	 * @param dt 仿真时间步长。
	 *
	 * @method stepVelocity 推进仿真，更新速度。
	 * @param dt 仿真时间步长。
	 *
	 * @method solveVelocityConstraint 求解仿真步的速度约束。
	 * @param dt 仿真时间步长。
	 *
	 * @method stepPosition 推进仿真，更新位置。
	 * @param dt 仿真时间步长。
	 *
	 * @method solvePositionConstraint 求解仿真步的位置约束。
	 * @param dt 仿真时间步长。
	 *
	 * @method gravity 获取当前重力向量。
	 * @return 重力向量。
	 *
	 * @method setGravity 设置重力向量。
	 * @param gravity 新的重力向量。
	 *
	 * @method linearVelocityDamping 获取线性速度阻尼系数。
	 * @return 线性速度阻尼系数。
	 *
	 * @method setLinearVelocityDamping 设置线性速度阻尼系数。
	 * @param linearVelocityDamping 新的线性速度阻尼系数。
	 *
	 * @method angularVelocityDamping 获取角速度阻尼系数。
	 * @return 角速度阻尼系数。
	 *
	 * @method setAngularVelocityDamping 设置角速度阻尼系数。
	 * @param angularVelocityDamping 新的角速度阻尼系数。
	 *
	 * @method linearVelocityThreshold 获取休眠的线性速度阈值。
	 * @return 线性速度阈值。
	 *
	 * @method setLinearVelocityThreshold 设置休眠的线性速度阈值。
	 * @param linearVelocityThreshold 新的线性速度阈值。
	 *
	 * @method angularVelocityThreshold 获取休眠的角速度阈值。
	 * @return 角速度阈值。
	 *
	 * @method setAngularVelocityThreshold 设置休眠的角速度阈值。
	 * @param angularVelocityThreshold 新的角速度阈值。
	 *
	 * @method airFrictionCoefficient 获取空气摩擦系数。
	 * @return 空气摩擦系数。
	 *
	 * @method setAirFrictionCoefficient 设置空气摩擦系数。
	 * @param airFrictionCoefficient 新的空气摩擦系数。
	 *
	 * @method enableGravity 检查是否启用重力。
	 * @return 若启用重力返回 true，否则返回 false。
	 *
	 * @method setEnableGravity 启用或禁用重力。
	 * @param enableGravity true 启用重力，false 禁用。
	 *
	 * @method enableDamping 检查是否启用阻尼。
	 * @return 若启用阻尼返回 true，否则返回 false。
	 *
	 * @method setEnableDamping 启用或禁用阻尼。
	 * @param enableDamping true 启用阻尼，false 禁用。
	 *
	 * @method createBody 创建一个新的刚体。
	 * @return 指向新建 Body 的指针。
	 *
	 * @method removeBody 从世界中移除一个刚体。
	 * @param body 要移除的 Body 指针。
	 *
	 * @method removeJoint 从世界中移除一个关节。
	 * @param joint 要移除的 Joint 指针。
	 *
	 * @method clearAllBodies 移除世界中的所有刚体。
	 *
	 * @method clearAllJoints 移除世界中的所有关节。
	 *
	 * @method createJoint 创建新的 PointJoint 或 DistanceJoint。
	 * @param primitive 关节参数描述体。
	 * @return 指向新建关节的指针。
	 *
	 * @method bias 获取约束求解中的偏置因子。
	 * @return 偏置因子。
	 *
	 * @method setBias 设置约束求解中的偏置因子。
	 * @param bias 新的偏置因子。
	 *
	 * @method bodyList 获取世界中的刚体列表。
	 * @return 指向 Body 智能指针容器的引用。
	 *
	 * @method jointList 获取世界中的关节列表。
	 * @return 指向 Joint 智能指针容器的引用。
	 *
	 * @method enableSleep 获取或设置是否启用刚体休眠。
	 * @return 休眠使能标志的引用。
	 *
	 * @private
	 * @var m_gravity 施加于所有刚体的重力向量。
	 * @var m_linearVelocityDamping 线性速度阻尼系数。
	 * @var m_angularVelocityDamping 角速度阻尼系数。
	 * @var m_linearVelocityThreshold 休眠的线性速度阈值。
	 * @var m_angularVelocityThreshold 休眠的角速度阈值。
	 * @var m_airFrictionCoefficient 空气摩擦系数。
	 * @var m_bias 约束求解的偏置因子。
	 * @var m_enableGravity 是否启用重力的标志。
	 * @var m_enableDamping 是否启用阻尼的标志。
	 * @var m_enableSleep 是否启用休眠的标志。
	 * @var m_bodyList Body 对象的智能指针容器。
	 * @var m_jointList Joint 对象的智能指针容器。
	 */
	{
	public:
		PhysicsWorld() : m_gravity(0, -9.8f), m_linearVelocityDamping(0.9f), m_angularVelocityDamping(0.9f),
						 m_linearVelocityThreshold(0.02f), m_angularVelocityThreshold(0.02f),
						 m_airFrictionCoefficient(0.7f), m_bias(0.8f)
		{
		}

		~PhysicsWorld();
		// disable copy
		PhysicsWorld(const PhysicsWorld &) = delete;
		PhysicsWorld &operator=(const PhysicsWorld &) = delete;
		void prepareVelocityConstraint(const real &dt);
		void stepVelocity(const real &dt);
		void solveVelocityConstraint(real dt);
		void stepPosition(const real &dt);
		void solvePositionConstraint(real dt);

		Vector2 gravity() const;
		void setGravity(const Vector2 &gravity);

		real linearVelocityDamping() const;
		void setLinearVelocityDamping(const real &linearVelocityDamping);

		real angularVelocityDamping() const;
		void setAngularVelocityDamping(const real &angularVelocityDamping);

		real linearVelocityThreshold() const;
		void setLinearVelocityThreshold(const real &linearVelocityThreshold);

		real angularVelocityThreshold() const;
		void setAngularVelocityThreshold(const real &angularVelocityThreshold);

		real airFrictionCoefficient() const;
		void setAirFrictionCoefficient(const real &airFrictionCoefficient);

		bool& enableGravity();
		void setEnableGravity(bool enableGravity);

		bool& enableDamping();
		void setEnableDamping(bool enableDamping);

		Body *createBody();
		void removeBody(Body *body);

		void removeJoint(Joint *joint);

		void clearAllBodies();
		void clearAllJoints();

		PointJoint *createJoint(const PointJointPrimitive &primitive);
		DistanceJoint *createJoint(const DistanceJointPrimitive &primitive);

		real bias() const;
		void setBias(const real &bias);

		Container::Vector<std::unique_ptr<Body>> &bodyList();

		Container::Vector<std::unique_ptr<Joint>> &jointList();

		bool &enableSleep();

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

}
#endif
