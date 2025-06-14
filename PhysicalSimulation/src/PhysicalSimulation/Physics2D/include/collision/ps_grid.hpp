#ifndef PHYSICAL_SIMULATION_GRID_HPP
#define PHYSICAL_SIMULATION_GRID_HPP
#include "ps_aabb.hpp"
#include "ps_body.hpp"
#include <list>
#include <vector>

namespace ps
{
	/**
	 * @class UniformGrid
	 * @brief 均匀网格类，用于物理仿真中的空间划分和碰撞检测。
	 *
	 * 提供均匀网格的创建、更新、查询等功能，支持动态物体的插入、删除和更新操作。
	 */
	class UniformGrid
	{
	public:
		UniformGrid(const real &width = 400.0f, const real &height = 400.0f, uint32_t rows = 400,
					uint32_t columns = 400);
		Container::Vector<std::pair<Body *, Body *>> generate();
		Container::Vector<Body *> raycast(const Vector2 &p, const Vector2 &d);

		void updateAll();
		void update(Body *body);
		void insert(Body *body);
		void remove(Body *body);
		void clearAll();
		Container::Vector<Body *> query(const AABB &aabb);

		int rows() const;
		void setRows(const int &size);

		int columns() const;
		void setColumns(const int &size);

		real width() const;
		void setWidth(const real &size);

		real height() const;
		void setHeight(const real &size);

		struct Position
		{
			Position() = default;

			Position(const uint32_t &_x, const uint32_t &_y) : x(_x), y(_y)
			{
			}

			uint32_t x = 0;
			uint32_t y = 0;

			bool operator<(const Position &rhs) const
			{
				if (x < rhs.x)
					return true;
				if (x == rhs.x)
					return y < rhs.y;
				return false;
			}

			bool operator>(const Position &rhs) const
			{
				if (x > rhs.x)
					return true;
				if (x == rhs.x)
					return y > rhs.y;
				return false;
			}

			bool operator==(const Position &rhs) const
			{
				return x == rhs.x && y == rhs.y;
			}
		};

		// AABB query cells
		Container::Vector<Position> queryCells(const AABB &aabb);

		// ray cast query cells
		Container::Vector<Position> queryCells(const Vector2 &start, const Vector2 &direction);
		real cellHeight() const;
		real cellWidth() const;

		Container::Map<Position, Container::Vector<Body *>> m_cellsToBodies;
		Container::Map<Body *, Container::Vector<Position>> m_bodiesToCells;

		void fullUpdate(Body *body);
		void incrementalUpdate(Body *body);

	private:
		enum class Operation
		{
			Add,
			Delete
		};

		void updateGrid();
		void changeGridSize();
		void updateBodies();
		Container::Vector<std::pair<Operation, Position>> compareCellList(
			const Container::Vector<Position> &oldCellList, const Container::Vector<Position> &newCellList);
		real m_width = 100.0f;
		real m_height = 100.0f;
		uint32_t m_rows = 200;
		uint32_t m_columns = 200;

		real m_cellWidth = 0.0f;
		real m_cellHeight = 0.0f;
	};
}

#endif
