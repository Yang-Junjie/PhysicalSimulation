#ifndef PS_AABB_HPP
#define PS_AABB_HPP

#include "ps_lineralg.hpp"
#include "ps_shape.hpp"

namespace ps
{
	class Body;

	struct AABB
	/**
	 * @brief Axis-Aligned Bounding Box (AABB) class for 2D physical simulations.
	 *
	 * This class represents a rectangle aligned with the coordinate axes, defined by its position (top-left corner), width, and height.
	 * It provides a variety of methods for collision detection, expansion, scaling, union, subset checks, and raycasting.
	 *
	 * 成员变量:
	 * - width: 包围盒的宽度。
	 * - height: 包围盒的高度。
	 * - position: 包围盒左上角的位置。
	 *
	 * 构造函数:
	 * - 默认构造函数。
	 * - 通过左上角位置、宽度和高度构造。
	 * - 通过左上角和右下角位置构造。
	 *
	 * 方法:
	 * - topLeft(), topRight(), bottomLeft(), bottomRight(): 获取包围盒的四个角坐标。
	 * - minimumX(), minimumY(), maximumX(), maximumY(): 获取包围盒的最小和最大坐标。
	 * - collide(): 检查与另一个AABB的碰撞。
	 * - expand(): 按因子扩展包围盒。
	 * - scale(): 按因子缩放包围盒。
	 * - clear(): 重置包围盒为初始状态。
	 * - unite(): 扩展当前包围盒以包含另一个AABB。
	 * - surfaceArea(): 获取包围盒的表面积。
	 * - volume(): 获取包围盒的体积（二维情况下为面积）。
	 * - isSubset(): 检查当前包围盒是否为另一个包围盒的子集。
	 * - isEmpty(): 检查包围盒是否为空。
	 * - operator==: 判断两个包围盒是否相等。
	 * - raycast(): 对包围盒进行射线检测。
	 *
	 * 静态方法:
	 * - fromShape(): 通过形状创建AABB。
	 * - fromBody(): 通过物体创建AABB。
	 * - fromBox(): 通过两个角点创建AABB。
	 * - collide(): 检查两个AABB是否重叠。
	 * - unite(): 返回两个AABB的并集。
	 * - isSubset(): 检查一个AABB是否为另一个的子集。
	 * - expand(): 按因子扩展AABB。
	 * - raycast(): 对AABB进行射线检测。
	 */
	{
		AABB() = default;
		AABB(const Vector2 &topLeft, const real &boxWidth, const real &boxHeight);
		AABB(const Vector2 &topLeft, const Vector2 &bottomRight);
		real width = 0;
		real height = 0;
		Vector2 position;
		inline Vector2 topLeft() const;
		inline Vector2 topRight() const;
		inline Vector2 bottomLeft() const;
		inline Vector2 bottomRight() const;

		real minimumX() const;
		real minimumY() const;
		real maximumX() const;
		real maximumY() const;

		bool collide(const AABB &other) const;
		void expand(const real &factor);
		void scale(const real &factor);
		void clear();
		AABB &unite(const AABB &other);
		real surfaceArea() const;
		real volume() const;
		bool isSubset(const AABB &other) const;
		bool isEmpty() const;
		bool operator==(const AABB &other) const;
		bool raycast(const Vector2 &start, const Vector2 &direction) const;
		/// <summary>
		/// Create AABB from shape.
		/// </summary>
		/// <param name="shape">shape source</param>
		/// <param name="factor">AABB scale factor. Default factor 1 means making tight AABB</param>
		/// <returns></returns>
		static AABB fromShape(const ShapePrimitive &shape, const real &factor = 0);
		static AABB fromBody(Body *body, const real &factor = 0);
		static AABB fromBox(const Vector2 &topLeft, const Vector2 &bottomRight);
		/// <summary>
		/// Check if two aabbs are overlapping
		/// </summary>
		/// <param name="src"></param>
		/// <param name="target"></param>
		/// <returns></returns>
		static bool collide(const AABB &src, const AABB &target);
		/// <summary>
		/// Return two aabb union result
		/// </summary>
		/// <param name="src"></param>
		/// <param name="target"></param>
		/// <returns></returns>
		static AABB unite(const AABB &src, const AABB &target, const real &factor = 0);
		/// <summary>
		/// Check if b is subset of a
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static bool isSubset(const AABB &a, const AABB &b);

		static void expand(AABB &aabb, const real &factor = 0.0);

		static bool raycast(const AABB &aabb, const Vector2 &start, const Vector2 &direction);
	};

}
#endif