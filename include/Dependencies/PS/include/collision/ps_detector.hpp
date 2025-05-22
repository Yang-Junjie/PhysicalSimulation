#ifndef PHYSICAL_SIMULATION_DETECTOR_HPP
#define PHYSICAL_SIMULATION_DETECTOR_HPP

#include "ps_math.hpp"
#include "ps_shape.hpp"
#include "ps_body.hpp"
#include "ps_narrowphase.hpp"

namespace ps
{

	/// @struct Collision
	/// @brief 表示两个物体之间的碰撞信息
	/// @var Collision::isColliding
	/// 指示是否发生碰撞
	/// @var Collision::bodyA
	/// 参与碰撞的第一个物体指针
	/// @var Collision::bodyB
	/// 参与碰撞的第二个物体指针
	/// @var Collision::contactList
	/// 碰撞接触点列表
	/// @var Collision::normal
	/// 碰撞法线方向
	/// @var Collision::penetration
	/// 穿透深度
	struct Collision
	{
		bool isColliding = false;
		Body *bodyA = nullptr;
		Body *bodyB = nullptr;
		ContactPair contactList;
		Vector2 normal;
		real penetration = 0;
	};

	/// @class Detector
	/// @brief 碰撞检测器，提供多种碰撞检测与距离计算的静态方法
	///
	/// 提供不同类型物体（Body与ShapePrimitive）之间的碰撞检测与距离计算接口。
	///
	/// 静态方法:
	/// - collide: 判断两个物体是否发生碰撞，支持多种参数组合
	/// - detect: 检测并返回详细的碰撞信息
	/// - distance: 计算两个物体之间的最近距离及相关信息
	class Detector
	{
	public:
		static bool collide(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
		static bool collide(Body *bodyA, Body *bodyB);
		static bool collide(const ShapePrimitive &shapeA, Body *bodyB);
		static bool collide(Body *bodyA, const ShapePrimitive &shapeB);

		static Collision detect(Body *bodyA, Body *bodyB);
		static Collision detect(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
		static Collision detect(Body *bodyA, const ShapePrimitive &shapeB);
		static Collision detect(const ShapePrimitive &shapeA, Body *bodyB);

		static CollisionInfo distance(Body *bodyA, Body *bodyB);
		static CollisionInfo distance(const ShapePrimitive &shapeA, const ShapePrimitive &shapeB);
		static CollisionInfo distance(Body *bodyA, const ShapePrimitive &shapeB);
		static CollisionInfo distance(const ShapePrimitive &shapeA, Body *bodyB);

	private:
	};
}
#endif
