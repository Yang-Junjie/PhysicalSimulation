#ifndef PHYSICS2D_SYSTEM_HPP
#define PHYSICS2D_SYSTEM_HPP
#include "ps_body.hpp"
#include "ps_world.hpp"
#include "ps_detector.hpp"
#include "ps_tree.hpp"
#include "ps_ccd.hpp"
#include "ps_sap.hpp"
#include "ps_grid.hpp"

namespace ps
{
	class PhysicsSystem
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
		void solveOnce(const real& dt);
		int m_positionIteration = 1;
		int m_velocityIteration = 1;
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
