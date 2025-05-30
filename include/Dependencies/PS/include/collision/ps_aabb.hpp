#ifndef PHYSICAL_SIMULATION_AABB_HPP
#define PHYSICAL_SIMULATION_AABB_HPP

#include "ps_linear.hpp"
#include "ps_shape.hpp"

namespace ps
{
	class Body;

	struct   AABB
	{
		AABB() = default;
		AABB(const Vector2& topLeft, const real& boxWidth, const real& boxHeight);
		AABB(const Vector2& topLeft, const Vector2& bottomRight);
		real width = 0;
		real height = 0;
		Vector2 position;
		inline Vector2 topLeft()const;
		inline Vector2 topRight()const;
		inline Vector2 bottomLeft()const;
		inline Vector2 bottomRight()const;

		real minimumX()const;
		real minimumY()const;
		real maximumX()const;
		real maximumY()const;

		bool collide(const AABB& other) const;
		void expand(const real& factor);
		void scale(const real& factor);
		void clear();
		AABB& unite(const AABB& other);
		real surfaceArea()const;
		real volume()const;
		bool isSubset(const AABB& other)const;
		bool isEmpty()const;
		bool operator==(const AABB& other)const;
		bool raycast(const Vector2& start, const Vector2& direction)const;
		
		static AABB fromShape(const ShapePrimitive& shape, const real& factor = 0);
		static AABB fromBody(Body* body, const real& factor = 0);
		static AABB fromBox(const Vector2& topLeft, const Vector2& bottomRight);
		static bool collide(const AABB& src, const AABB& target);
		static AABB unite(const AABB& src, const AABB& target, const real& factor = 0);
		static bool isSubset(const AABB& a, const AABB& b);
		static void expand(AABB& aabb, const real& factor = 0.0);
		static bool raycast(const AABB& aabb, const Vector2& start, const Vector2& direction);
		
	};


}
#endif