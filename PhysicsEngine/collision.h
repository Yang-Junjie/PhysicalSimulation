#pragma once

#include <vector>
#include "Body.h"


//���º�����ʹ��const ���ü���copy�ڴ濪��

/*�������
Collision���Ƿ���ײ���ཻ��
depth:��ײ���
normal����������
*/
struct IntersectData {
    bool Collision = false;
    float depth = std::numeric_limits<float>::max();
    oeVec2 normal;
};


    /*�˺��������ж�2�������AABB�Ƿ��ཻ*/
static bool IntersectAABB(oeAABB& a, oeAABB& b){
    // ��� x ���ϵ��ص�
    if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
    // ��� y ���ϵ��ص�
    if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

    // ������������������㣬������ AABB �ཻ
    return true;
}


//�ҵ�����ξ��������Ķ���
static size_t FindVertexClosestPoint(const oeVec2& point, const oeVec2 vertices[],const int vertices_count) {
    size_t result = 0;
    float min_distance = std::numeric_limits<float>::max();
    for (size_t i = 0; i < vertices_count; ++i) {
        float distance = oeVec2::Distance(vertices[i], point);
        if (distance <= min_distance) {
            min_distance = distance;
            result = i;
        }
    }
    return result;
}

//�������������ϵ�ͶӰ
static oeVec2 ProjectVertices(const oeVec2& axis, const oeVec2 vertices[], int vertices_count) {
    float min_proj = std::numeric_limits<float>::max();
    float max_proj = -std::numeric_limits<float>::max();

    for (int i = 0; i < vertices_count; ++i) {
        float projection = axis.dot(vertices[i]);
        min_proj = std::min(min_proj, projection);
        max_proj = std::max(max_proj, projection);
    }

    return oeVec2(min_proj, max_proj);
}



/*Բ��Բ��ײ���*/
static IntersectData IntersectCircles(const oeVec2& center_a, const float& radius_a, const oeVec2& center_b, const float& radius_b) {
    IntersectData data;
    float both_distance = oeVec2::Distance(center_a, center_b);
    float sum_of_radii = radius_a + radius_b;

    if (both_distance >= sum_of_radii) {
        return data;
    }

    //���㵥λ��������
    oeVec2 unit_direction_vector_ab = center_b - center_a;
    unit_direction_vector_ab.normalize();

    //����data
    data.Collision = true;
    data.normal = unit_direction_vector_ab;
    data.depth = sum_of_radii - both_distance;

    return data;
}


// ����Բ��ĳ�����ϵ�ͶӰ
static oeVec2 ProjectCircle(const oeVec2& center, const float& radius, const oeVec2& axis) {
    float center_projection = axis.dot(center);
    return oeVec2(center_projection - radius, center_projection + radius);
}

// �ж����������Ƿ��ص�
static bool overlaps(const oeVec2& interval_a, const oeVec2& interval_b) {
    return !(interval_a.y < interval_b.x || interval_b.y < interval_a.x);
}
static IntersectData IntersectCirclePolygon(
    const oeVec2& circle_center, const float& circle_radius,
    const oeVec2 polygon_mass_center, const oeVec2 polygon_vertices[], const int vertices_count
) {
    IntersectData data;
    data.depth = std::numeric_limits<float>::max();
    data.Collision = true;  // Ĭ�ϼ��跢����ײ

    // ����Բ�����������ϵ�ͶӰ
    auto ProjectCircle = [&](const oeVec2& axis) -> oeVec2 {
        float projection = oeVec2::dot(circle_center, axis);
        return oeVec2(projection - circle_radius, projection + circle_radius);
    };

    // �ж�����ͶӰ�����Ƿ��ص�
    auto Overlaps = [](const oeVec2& proj_a, const oeVec2& proj_b) -> bool {
        return !(proj_a.y < proj_b.x || proj_b.y < proj_a.x);
    };

    // ��������ε�ÿ���ߣ����ߵķ�������Ϊ������
    for (int i = 0; i < vertices_count && data.Collision; ++i) {
        oeVec2 v_a = polygon_vertices[i];
        oeVec2 v_b = polygon_vertices[(i + 1) % vertices_count];

        // ����ߵķ���������ʱ��˳�򣬷�����ָ���ⲿ��
        oeVec2 edge_vector = v_b - v_a;
        oeVec2 axis = oeVec2(-edge_vector.y, edge_vector.x); // ���ַ���
        axis.normalize();

        // �������
        std::cout << "Edge from " << v_a << " to " << v_b << "\n";
        std::cout << "Normal: " << axis << "\n";

        // �������κ�Բ�ڸ����ϵ�ͶӰ
        oeVec2 project_polygon = ProjectVertices(axis, polygon_vertices, vertices_count);
        oeVec2 project_circle = ProjectCircle(axis);

        // �ж�ͶӰ�Ƿ��ص���������ص�˵��û������ײ
        if (!Overlaps(project_polygon, project_circle)) {
            data.Collision = false;
            return data;  // û���ص�������
        }

        // ����ص�������ͶӰ���ص����
        float axis_depth = std::min(project_circle.y - project_polygon.x, project_polygon.y - project_circle.x);

        // ������С�ڵ�ǰ��С��ȣ�����·����������
        if (axis_depth < data.depth) {
            data.depth = axis_depth;
            data.normal = axis;
        }
    }

    // ����������϶����ص���������ײ���
    if (data.Collision) {
        oeVec2 direction_vector = circle_center - polygon_mass_center;

        // �����������Ҫ��ת��ȷ�����ս����ȷ
        if (oeVec2::dot(direction_vector, data.normal) < 0) {
            data.normal = -data.normal;
        }
    }

    return data;
}
static IntersectData IntersectPolygons(
    const oeVec2& mass_center_a, const oeVec2* vertices_a, int verticesA_count,
    const oeVec2& mass_center_b, const oeVec2* vertices_b, int verticesB_count
) {
    // �������Ķ�����Ƿ����㹻�Ķ���
    if (verticesA_count < 3 || verticesB_count < 3) {
        IntersectData data = { false, 0.0f, oeVec2(0, 0) };
        return data;
    }

    IntersectData data = { true, std::numeric_limits<float>::max(), oeVec2(0, 0) };

    auto CheckAxis = [&](const oeVec2& axis) -> bool {
        // ���������ڸ����ϵ�ͶӰ
        oeVec2 proj_a = ProjectVertices(axis, vertices_a, verticesA_count);
        oeVec2 proj_b = ProjectVertices(axis, vertices_b, verticesB_count);

        // �ж�ͶӰ�Ƿ��ص�
        if (proj_a.y < proj_b.x || proj_b.y < proj_a.x) {
            data.Collision = false;
            return false;
        }

        // ����ͶӰ���ص����
        float axis_depth = std::min(proj_b.y - proj_a.x, proj_a.y - proj_b.x);

        // ������С�ڵ�ǰ��С��ȣ�����·����������
        if (axis_depth < data.depth) {
            data.depth = axis_depth;
            data.normal = axis;
        }
        return true;
        };

    // ���������A��ÿ����
    for (int i = 0; i < verticesA_count && data.Collision; ++i) {
        oeVec2 v_a = vertices_a[i];
        oeVec2 v_b = vertices_a[(i + 1) % verticesA_count];

        // ����ߵķ���������ʱ��˳�򣬷�����ָ���ⲿ��
        oeVec2 edge_vector = v_b - v_a;
        oeVec2 axis = oeVec2(-edge_vector.y, edge_vector.x); // ���ַ���
        axis.normalize();

        // ����Ƿ��ص�
        if (!CheckAxis(axis)) {
            return data; // û���ص�������
        }
    }

    // ���������B��ÿ����
    for (int i = 0; i < verticesB_count && data.Collision; ++i) {
        oeVec2 v_a = vertices_b[i];
        oeVec2 v_b = vertices_b[(i + 1) % verticesB_count];

        // ����ߵķ���������ʱ��˳�򣬷�����ָ���ⲿ��
        oeVec2 edge_vector = v_b - v_a;
        oeVec2 axis = oeVec2(-edge_vector.y, edge_vector.x); // ���ַ���
        axis.normalize();

        // ����Ƿ��ص�
        if (!CheckAxis(axis)) {
            return data; // û���ص�������
        }
    }

    // ����������϶����ص���������ײ���
    if (data.Collision) {
        oeVec2 direction_vector = mass_center_b - mass_center_a;

        // �����������Ҫ��ת��ȷ�����ս����ȷ
        if (oeVec2::dot(direction_vector, data.normal) < 0) {
            data.normal = -data.normal;
        }
    }

    return data;
}

static IntersectData  Collide(oeBody& body_a, oeBody& body_b) {
    IntersectData intersect_data;
    Shape shape_type_a = body_a.shape_;
    Shape shape_type_b = body_b.shape_;

    if (shape_type_a == BOX || shape_type_a == POLTGON) {
        if (shape_type_b == BOX || shape_type_b == POLTGON) {
            intersect_data = IntersectPolygons(body_a.mass_center_, body_a.vertices_,body_a.vertices_count_,
                                               body_b.mass_center_, body_b.vertices_,body_b.vertices_count_);
            
            return intersect_data;
        }
        else if (shape_type_b == CIRCLE) {
            intersect_data = IntersectCirclePolygon(body_b.mass_center_, body_b.radius_or_half_width_, body_a.mass_center_, body_a.vertices_,body_a.vertices_count_);
            return intersect_data;
        }
    }
    else if (shape_type_a == CIRCLE) {
        if (shape_type_b == CIRCLE) {
            intersect_data =IntersectCircles(body_a.mass_center_, body_a.radius_or_half_width_, body_b.mass_center_, body_b.radius_or_half_width_);
            return intersect_data;
        }
        else if (shape_type_b == POLTGON|| shape_type_b == BOX) {
            intersect_data = IntersectCirclePolygon(body_a.mass_center_, body_a.radius_or_half_width_, body_b.mass_center_, body_b.vertices_, body_b.vertices_count_);
            return intersect_data;
        }
    }

    return intersect_data;
}

