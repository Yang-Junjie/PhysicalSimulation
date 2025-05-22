#ifndef PHYSICAL_SIMULATION_SYSTEM_HPP
#define PHYSICAL_SIMULATION_SYSTEM_HPP
#include "ps_body.hpp"
#include "ps_world.hpp"
#include "ps_detector.hpp"
#include "ps_tree.hpp"
#include "ps_ccd.hpp"
#include "ps_sap.hpp"
#include "ps_grid.hpp"

namespace ps
{
	/**
	 * @class PhysicsSystem
	 * @brief 管理物理仿真的核心循环和子系统。
	 *
	 * PhysicsSystem 类封装了推进物理仿真所需的主要组件和逻辑。
	 * 它提供了对物理世界、接触维护器、广义相位树和均匀网格的接口。
	 * 系统还管理求解器迭代次数以及各种求解步骤的开关。
	 *
	 * 公有方法:
	 * - void step(const real& dt): 推进仿真一个时间步长。
	 * - PhysicsWorld& world(): 访问物理世界。
	 * - ContactMaintainer& maintainer(): 访问接触维护器。
	 * - Tree& tree(): 访问广义相位树。
	 * - UniformGrid& grid(): 访问均匀网格。
	 * - int& positionIteration(): 获取/设置位置求解器迭代次数。
	 * - int& velocityIteration(): 获取/设置速度求解器迭代次数。
	 * - bool& sliceDeltaTime(): 启用/禁用时间步长切片。
	 * - bool& solveJointVelocity(): 启用/禁用关节速度求解。
	 * - bool& solveJointPosition(): 启用/禁用关节位置求解。
	 * - bool& solveContactVelocity(): 启用/禁用接触速度求解。
	 * - bool& solveContactPosition(): 启用/禁用接触位置求解。
	 *
	 * 私有方法:
	 * - void updateTree(): 更新广义相位树结构。
	 * - void updateGrid(): 更新均匀网格结构。
	 * - void solve(const real& dt): 执行主要的仿真求解步骤。
	 * - bool solveCCD(const real& dt): 执行连续碰撞检测。
	 *
	 * 成员变量:
	 * - m_positionIteration: 位置求解器迭代次数（默认: 3）。
	 * - m_velocityIteration: 速度求解器迭代次数（默认: 8）。
	 * - m_sliceDeltaTime: 是否对仿真步长进行切片。
	 * - m_solveJointVelocity: 是否求解关节速度。
	 * - m_solveJointPosition: 是否求解关节位置。
	 * - m_solveContactVelocity: 是否求解接触速度。
	 * - m_solveContactPosition: 是否求解接触位置。
	 * - m_world: 物理世界实例。
	 * - m_maintainer: 接触维护器实例。
	 * - m_tree: 广义相位树实例。
	 * - m_grid: 均匀网格实例。
	 */
	class   PhysicsSystem
	{
	public:
		void step(const real& dt);
		PhysicsWorld& world();
		ContactMaintainer& maintainer();
		Tree& tree();
		UniformGrid& grid();
		int& positionIteration();
		int& velocityIteration();
		bool& sliceDeltaTime();
		bool& solveJointVelocity();
		bool& solveJointPosition();
		bool& solveContactVelocity();
		bool& solveContactPosition();

	private:
		void updateTree();
		void updateGrid();
		void solve(const real& dt);
		bool solveCCD(const real& dt);
		int m_positionIteration = 3;
		int m_velocityIteration = 8;
		bool m_sliceDeltaTime = false;
		bool m_solveJointVelocity = true;
		bool m_solveJointPosition = true;
		bool m_solveContactVelocity = true;
		bool m_solveContactPosition = true;
		PhysicsWorld m_world;
		ContactMaintainer m_maintainer;
		Tree m_tree;
		UniformGrid m_grid;
	};
}
#endif

