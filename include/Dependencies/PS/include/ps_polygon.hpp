#ifndef PS_POLYGON_HPP
#define PS_POLYGON_HPP
#include "ps_shape.hpp"
/**
 * @brief 多边形类，继承自 Shape。
 * 
 * 该类用于表示和操作二维多边形，支持顶点的添加、缩放、包含性判断等功能。
 */
namespace ps
{
    /**
     * @class Polygon
     * @brief 表示二维多边形的类。
     * 
     * 提供多边形的顶点管理、缩放、中心点计算以及点包含性判断等操作。
     */
    class Polygon : public Shape
    {
    public:
        /**
         * @brief 构造一个空的多边形对象。
         */
        Polygon();

        /**
         * @brief 获取多边形的顶点列表。
         * @return const std::vector<Vector2>& 顶点的常量引用。
         */
        const std::vector<Vector2> &vertices() const;

        /**
         * @brief 获取多边形的索引列表。
         * @return const std::vector<int>& 索引的常量引用。
         */
        const std::vector<int> &indices() const;

        /**
         * @brief 通过初始化列表添加多个顶点。
         * @param vertices 要添加的顶点列表。
         */
        void append(const std::initializer_list<Vector2> &vertices);

        /**
         * @brief 添加一个顶点到多边形。
         * @param vertex 要添加的顶点。
         */
        void append(const Vector2 &vertex);

        /**
         * @brief 计算并返回多边形的中心点。
         * @return Vector2 多边形的中心点坐标。
         */
        Vector2 center() const override;

        /**
         * @brief 按比例缩放多边形。
         * @param factor 缩放因子。
         */
        void scale(const real &factor) override;

        /**
         * @brief 判断一个点是否在多边形内部。
         * @param point 要判断的点。
         * @param epsilon 容差值，默认为 Constant::GeometryEpsilon。
         * @return bool 点是否在多边形内部。
         */
        bool contains(const Vector2 &point, const real &epsilon = Constant::GeometryEpsilon) override;

    protected:
        /**
         * @brief 多边形的顶点列表。
         */
        std::vector<Vector2> m_vertices;

        /**
         * @brief 多边形的索引列表。
         */
        std::vector<int> m_indices;

        /**
         * @brief 更新顶点数据。
         */
        void updateVertices();

        /**
         * @brief 更新索引数据。
         */
        void updateIndex();
    };
}
#endif