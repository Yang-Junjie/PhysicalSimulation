#ifndef PHYSICAL_SIMULATION_CONSTRAINT_CONTACT_HPP
#define PHYSICAL_SIMULATION_CONSTRAINT_CONTACT_HPP
#include <string>

#include "ps_body.hpp"
#include "ps_random.hpp"
#include "ps_detector.hpp"

namespace ps
{
	struct   VelocityConstraintPoint
	/**
	 * @brief 表示两个物体之间接触点的信息结构体。
	 *
	 * 该结构体包含了解决两个物体接触点所需的所有数据，包括局部和世界空间的位置、速度、接触法线和切线、偏置值、穿透深度、恢复系数、有效质量以及累计冲量等。
	 *
	 * 成员说明:
	 * - localA: 物体A上的局部接触点。
	 * - localB: 物体B上的局部接触点。
	 * - ra: 从物体A质心到接触点的向量。
	 * - rb: 从物体B质心到接触点的向量。
	 * - va: 物体A在接触点的速度。
	 * - vb: 物体B在接触点的速度。
	 * - normal: 接触法线向量。
	 * - tangent: 接触切线向量。
	 * - velocityBias: 用于位置修正的偏置速度。
	 * - bias: 用于位置修正的标量偏置值。
	 * - penetration: 接触点的穿透深度。
	 * - restitution: 接触的恢复系数（弹性）。
	 * - effectiveMassNormal: 法线方向的有效质量。
	 * - effectiveMassTangent: 切线方向的有效质量。
	 * - accumulatedNormalImpulse: 法线方向的累计冲量。
	 * - accumulatedTangentImpulse: 切线方向的累计冲量。
	 */
	{
		Vector2 localA;
		Vector2 localB;
		Vector2 ra;
		Vector2 rb;
		Vector2 va;
		Vector2 vb;
		Vector2 normal;
		Vector2 tangent;
		Vector2 velocityBias;
		real bias = 0;
		real penetration = 0.0f;
		real restitution = 0.8f;
		real effectiveMassNormal = 0;
		real effectiveMassTangent = 0;
		real accumulatedNormalImpulse = 0;
		real accumulatedTangentImpulse = 0;
	};

	struct   ContactConstraintPoint
	/**
	 * @brief 表示物理仿真中两个物体之间的接触约束点。
	 *
	 * 该结构体包含了解决接触约束所需的所有数据，包括相关物体的引用、局部接触点、摩擦系数和约束矩阵等。
	 *
	 * 成员说明:
	 * - relation: 涉及接触的物体对的标识符。
	 * - friction: 接触点的摩擦系数。
	 * - active: 该接触约束是否处于激活状态。
	 * - localA: 物体A上的局部接触点。
	 * - localB: 物体B上的局部接触点。
	 * - bodyA: 指向参与接触的第一个物体的指针。
	 * - bodyB: 指向参与接触的第二个物体的指针。
	 * - vcp: 该接触点的速度约束数据。
	 * - k: 约束的有效质量矩阵。
	 * - normalMass: 沿接触法线的质量矩阵。
	 */
	{

		ContactConstraintPoint() = default;
		Body::BodyPair::BodyPairID relation = 0;
		real friction = 0.2f;
		bool active = true;
		Vector2 localA;
		Vector2 localB;
		Body* bodyA = nullptr;
		Body* bodyB = nullptr;
		VelocityConstraintPoint vcp;
		Matrix2x2 k;
		Matrix2x2 normalMass;
	};

	class   ContactMaintainer
	/**
	 * @brief 管理物理仿真中的接触约束。
	 *
	 * 该类提供处理物体间接触点、求解速度和位置约束、以及管理接触约束表的方法。
	 * 支持速度和位置的热启动（warm starting）与块求解器（block solver）。
	 *
	 * @note 本类使用映射表存储与物体对相关联的接触约束点。
	 *
	 * 成员说明:
	 * - clearAll(): 清除所有接触约束。
	 * - solveVelocity(real dt): 在给定时间步长下求解速度约束。
	 * - solvePosition(real dt): 在给定时间步长下求解位置约束。
	 * - add(const Collision& collision): 向接触表中添加新的碰撞信息。
	 * - prepare(ContactConstraintPoint& ccp, const VertexPair& pair, const Collision& collision): 准备一个接触约束点。
	 * - clearInactivePoints(): 移除非激活的接触点。
	 * - deactivateAllPoints(): 使所有接触点失效。
	 * - m_maxPenetration: 允许的最大穿透深度（默认: 0.005f）。
	 * - m_biasFactor: 约束求解中的偏置因子（默认: 0.2f）。
	 * - m_warmStart: 是否启用热启动（默认: true）。
	 * - m_velocityBlockSolver: 是否启用速度块求解器（默认: false）。
	 * - m_positionBlockSolver: 是否启用位置块求解器（默认: false）。
	 * - m_contactTable: 存储按物体对ID映射的接触约束点。
	 */
	{

	public:
		void clearAll();
		void solveVelocity(real dt);
		void solvePosition(real dt);
		void add(const Collision& collision);
		void prepare(ContactConstraintPoint& ccp, const VertexPair& pair, const Collision& collision);
		void clearInactivePoints();
		void deactivateAllPoints();
		real m_maxPenetration = 0.005f;
		real m_biasFactor = 0.2f;
		bool m_warmStart = true;
		bool m_velocityBlockSolver = false;
		bool m_positionBlockSolver = false;
		Container::Map<Body::BodyPair::BodyPairID, Container::Vector<ContactConstraintPoint>> m_contactTable;

	private:
	};
}
#endif

