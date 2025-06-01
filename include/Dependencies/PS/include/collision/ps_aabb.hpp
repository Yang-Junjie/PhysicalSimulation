#ifndef PHYSICAL_SIMULATION_AABB_HPP
#define PHYSICAL_SIMULATION_AABB_HPP

#include "ps_linear.hpp"  // 包含线性代数相关定义
#include "ps_shape.hpp"   // 包含形状基类定义

namespace ps
{
	class Body;  

	// 轴对齐包围盒(Axis-Aligned Bounding Box)
	struct   AABB
	{
		AABB() = default;  // 默认构造函数
		AABB(const Vector2& topLeft, const real& boxWidth, const real& boxHeight);  // 通过左上角坐标和宽高构造
		AABB(const Vector2& topLeft, const Vector2& bottomRight);  // 通过左上角和右下角坐标构造
		
		real width = 0;    // 包围盒宽度
		real height = 0;   // 包围盒高度
		Vector2 position;  // 包围盒位置
		
		inline Vector2 topLeft()const;     // 获取左上角坐标
		inline Vector2 topRight()const;    // 获取右上角坐标
		inline Vector2 bottomLeft()const;  // 获取左下角坐标
		inline Vector2 bottomRight()const; // 获取右下角坐标

		real minimumX()const;  // 获取最小X坐标
		real minimumY()const;  // 获取最小Y坐标
		real maximumX()const;  // 获取最大X坐标
		real maximumY()const;  // 获取最大Y坐标

		bool collide(const AABB& other) const;  // 检测与另一个AABB的碰撞
		void expand(const real& factor);        // 按比例扩展包围盒
		void scale(const real& factor);         // 按比例缩放包围盒
		void clear();                           // 清空包围盒(重置为0)
		AABB& unite(const AABB& other);         // 合并两个包围盒
		real surfaceArea()const;                // 计算表面积
		real volume()const;                     // 计算体积(面积)
		bool isSubset(const AABB& other)const;  // 判断是否完全包含在另一个AABB内
		bool isEmpty()const;                    // 判断是否为空包围盒
		bool operator==(const AABB& other)const; // 相等比较运算符
		bool raycast(const Vector2& start, const Vector2& direction)const;  // 射线检测
		
		// 静态工厂方法
		static AABB fromShape(const ShapePrimitive& shape, const real& factor = 0);  // 从形状创建AABB
		static AABB fromBody(Body* body, const real& factor = 0);  // 从物理体创建AABB
		static AABB fromBox(const Vector2& topLeft, const Vector2& bottomRight);  // 从边界坐标创建AABB
		
		// 静态工具方法
		static bool collide(const AABB& src, const AABB& target);  // 检测两个AABB的碰撞
		static AABB unite(const AABB& src, const AABB& target, const real& factor = 0);  // 合并两个AABB
		static bool isSubset(const AABB& a, const AABB& b);  // 判断a是否完全包含在b内
		static void expand(AABB& aabb, const real& factor = 0.0);  // 扩展AABB
		static bool raycast(const AABB& aabb, const Vector2& start, const Vector2& direction);  // 射线检测
	};

}
#endif