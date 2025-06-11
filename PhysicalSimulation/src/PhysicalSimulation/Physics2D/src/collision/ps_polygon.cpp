#include "ps_polygon.hpp"
#include "ps_algorithm_2d.hpp"
namespace ps
{
	Polygon::Polygon()
	{
		m_type = Type::Polygon;
		m_vertices.reserve(4);
	}

	const Container::Vector<Vector2> &Polygon::vertices() const
	{
		return m_vertices;
	}

	const std::vector<int> &Polygon::indices() const
	{
		return m_indices;
	}

	void Polygon::append(const std::initializer_list<Vector2> &vertices)
	{
		for (const Vector2 &vertex : vertices)
			m_vertices.emplace_back(vertex);
		updateVertices();
		updateIndex();
	}

	void Polygon::append(const Vector2 &vertex)
	{
		m_vertices.emplace_back(vertex);
		updateVertices();
		updateIndex();
	}

	Vector2 Polygon::center() const
	{
		return GeometryAlgorithm2D::calculateCenter(this->vertices());
	}

	void Polygon::scale(const real &factor)
	{
		assert(!m_vertices.empty());
		for (Vector2 &vertex : m_vertices)
			vertex *= factor;
	}

	bool Polygon::contains(const Vector2 &point, const real &epsilon)
	{
		// 仅适用于凸多边形
		for (auto iter = m_vertices.begin(); iter != m_vertices.end(); ++iter)
		{
			auto next = iter + 1;
			if (next == m_vertices.end())
				next = m_vertices.begin();
			auto ref = next + 1;
			if (ref == m_vertices.end())
				ref = m_vertices.begin();
			if (!GeometryAlgorithm2D::isPointOnSameSide(*iter, *next, *ref, point))
				return false;
		}
		return true;
	}

	void Polygon::updateVertices()
	{
		Vector2 center = this->center();
		for (auto &elem : m_vertices)
			elem -= center;
	}

	void Polygon::updateIndex()
	{
		m_indices.clear();
		for (size_t i = 0; i < m_vertices.size() - 2; i++)
		{
			m_indices.push_back(0);
			m_indices.push_back(static_cast<int>(i + 1));
			m_indices.push_back(static_cast<int>(i + 2));
		}
	}
}