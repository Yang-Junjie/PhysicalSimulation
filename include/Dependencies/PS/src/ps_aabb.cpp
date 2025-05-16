#include "ps_aabb.hpp"

#include "ps_body.hpp"
#include "ps_algorithm_2d.hpp"
#include "ps_narrowphase.hpp"

namespace ps
{

	bool AABB::isEmpty() const
	{
		return realEqual(width, 0) && realEqual(height, 0) && position.fuzzyEqual({0, 0});
	}
	bool AABB::raycast(const Vector2 &start, const Vector2 &direction) const
	{
		return raycast(*this, start, direction);
	}

	AABB::AABB(const Vector2 &topLeft, const real &boxWidth, const real &boxHeight)
	{
		this->width = boxWidth;
		this->height = boxHeight;
		this->position = topLeft + Vector2(boxWidth * 0.5f, -boxHeight * 0.5f);
	}

	AABB::AABB(const Vector2 &topLeft, const Vector2 &bottomRight)
	{
		*this = fromBox(topLeft, bottomRight);
	}

	Vector2 AABB::topLeft() const
	{
		return Vector2{minimumX(), maximumY()};
	}

	Vector2 AABB::topRight() const
	{
		return Vector2{maximumX(), maximumY()};
	}

	Vector2 AABB::bottomLeft() const
	{
		return Vector2{minimumX(), minimumY()};
	}

	Vector2 AABB::bottomRight() const
	{
		return Vector2{maximumX(), minimumY()};
	}

	real AABB::minimumX() const
	{
		return -width * 0.5f + position.x_;
	}

	real AABB::minimumY() const
	{
		return -height * 0.5f + position.y_;
	}

	real AABB::maximumX() const
	{
		return width * 0.5f + position.x_;
	}

	real AABB::maximumY() const
	{
		return height * 0.5f + position.y_;
	}

	bool AABB::collide(const AABB &other) const
	{
		return collide(*this, other);
	}

	void AABB::expand(const real &factor)
	{
		expand(*this, factor);
	}

	void AABB::scale(const real &factor)
	{
		width *= factor;
		height *= factor;
	}

	void AABB::clear()
	{
		position.clear();
		width = 0.0;
		height = 0.0;
	}

	AABB &AABB::unite(const AABB &other)
	{
		*this = unite(*this, other);
		return *this;
	}

	real AABB::surfaceArea() const
	{
		return (width + height) * 2.0f;
	}

	real AABB::volume() const
	{
		return width * height;
	}

	bool AABB::isSubset(const AABB &other) const
	{
		return isSubset(other, *this);
	}

	bool AABB::operator==(const AABB &other) const
	{
		return position.fuzzyEqual(other.position) &&
			   realEqual(width, other.width) && realEqual(height, other.height);
	}

	AABB AABB::fromShape(const ShapePrimitive &shape, const real &factor)
	{
		AABB aabb;
		switch (shape.shape->type())
		{
		case ShapeType::Polygon:
		{
			const Polygon *polygon = static_cast<Polygon *>(shape.shape);
			real max_x = Constant::NegativeMin, max_y = Constant::NegativeMin, min_x = Constant::Max, min_y = Constant::Max;
			for (const Vector2 &v : polygon->vertices())
			{
				const Vector2 vertex = Matrix2x2(shape.transform.rotation).multiply(v);
				if (max_x < vertex.x_)
					max_x = vertex.x_;

				if (min_x > vertex.x_)
					min_x = vertex.x_;

				if (max_y < vertex.y_)
					max_y = vertex.y_;

				if (min_y > vertex.y_)
					min_y = vertex.y_;
			}
			aabb.width = std::fabs(max_x - min_x);
			aabb.height = std::fabs(max_y - min_y);
			aabb.position.set((max_x + min_x) * 0.5f, (max_y + min_y) * 0.5f);
			break;
		}
		case ShapeType::Circle:
		{
			const Circle *circle = static_cast<Circle *>(shape.shape);
			aabb.width = circle->radius() * 2;
			aabb.height = circle->radius() * 2;
			break;
		}
		case ShapeType::Edge:
		{
			const Edge *edge = static_cast<Edge *>(shape.shape);
			aabb.width = std::fabs(edge->startPoint().x_ - edge->endPoint().x_);
			aabb.height = std::fabs(edge->startPoint().y_ - edge->endPoint().y_);
			aabb.position.set(edge->startPoint().x_ + edge->endPoint().x_, edge->startPoint().y_ + edge->endPoint().y_);
			aabb.position *= 0.5f;
			aabb.expand(0.5f);
			break;
		}
		}
		aabb.position += shape.transform.position;
		aabb.expand(factor);
		return aabb;
	}

	AABB AABB::fromBody(Body *body, const real &factor)
	{
		assert(body != nullptr);
		assert(body->shape() != nullptr);

		ShapePrimitive primitive;
		primitive.shape = body->shape();
		primitive.transform.rotation = body->rotation();
		primitive.transform.position = body->position();
		return fromShape(primitive, factor);
	}

	AABB AABB::fromBox(const Vector2 &topLeft, const Vector2 &bottomRight)
	{
		AABB result;
		result.width = bottomRight.x_ - topLeft.x_;
		result.height = topLeft.y_ - bottomRight.y_;
		result.position = (topLeft + bottomRight) * 0.5f;
		return result;
	}

	bool AABB::collide(const AABB &src, const AABB &target)
	{
		const Vector2 srcTopLeft = src.topLeft();
		const Vector2 srcBottomRight = src.bottomRight();

		const Vector2 targetTopLeft = target.topLeft();
		const Vector2 targetBottomRight = target.bottomRight();

		return !(srcBottomRight.x_ < targetTopLeft.x_ || targetBottomRight.x_ < srcTopLeft.x_ || srcTopLeft.y_ < targetBottomRight.y_ || targetTopLeft.y_ < srcBottomRight.y_);
	}

	AABB AABB::unite(const AABB &src, const AABB &target, const real &factor)
	{
		if (src.isEmpty())
			return target;

		if (target.isEmpty())
			return src;

		const Vector2 srcTopLeft = src.topLeft();
		const Vector2 srcBottomRight = src.bottomRight();

		const Vector2 targetTopLeft = target.topLeft();
		const Vector2 targetBottomRight = target.bottomRight();

		const real low_x = Math::min(srcTopLeft.x_, targetTopLeft.x_);
		const real high_x = Math::max(srcBottomRight.x_, targetBottomRight.x_);

		const real low_y = Math::min(srcBottomRight.y_, targetBottomRight.y_);
		const real high_y = Math::max(srcTopLeft.y_, targetTopLeft.y_);

		AABB aabb;
		aabb.position.set((low_x + high_x) * 0.5f, (low_y + high_y) * 0.5f);
		aabb.width = high_x - low_x;
		aabb.height = high_y - low_y;

		aabb.expand(factor);
		return aabb;
	}
	// b is a subset of a
	bool AABB::isSubset(const AABB &a, const AABB &b)
	{

		const Vector2 aTopLeft = a.topLeft();
		const Vector2 aBottomRight = a.bottomRight();

		const Vector2 bTopLeft = b.topLeft();
		const Vector2 bBottomRight = b.bottomRight();

		return aBottomRight.x_ >= bBottomRight.x_ && bTopLeft.x_ >= aTopLeft.x_ &&
			   aTopLeft.y_ >= bTopLeft.y_ && bBottomRight.y_ >= aBottomRight.y_;
	}
	void AABB::expand(AABB &aabb, const real &factor)
	{
		aabb.width += factor;
		aabb.height += factor;
	}
	bool AABB::raycast(const AABB &aabb, const Vector2 &start, const Vector2 &direction)
	{
		auto result = GeometryAlgorithm2D::raycastAABB(start, direction, aabb.topLeft(), aabb.bottomRight());
		if (!result.has_value())
			return false;
		auto [p1, p2] = result.value();
		return GeometryAlgorithm2D::isPointOnAABB(p1, aabb.topLeft(), aabb.bottomRight()) && GeometryAlgorithm2D::isPointOnAABB(p2, aabb.topLeft(), aabb.bottomRight());
	}
}
