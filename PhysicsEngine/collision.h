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

//�������������ϵ�ͶӰ
static  oeVec2 ProjectVertices(const oeVec2& axis, const std::vector<oeVec2>& vertices) {
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();

    for (const auto& vertex : vertices) {
        float projection = axis.dot(vertex);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }

    return oeVec2(min, max);
}

//����Բ��ĳ�����ϵ�ͶӰ
static oeVec2 ProjectCircle(const oeVec2& center, const float& radius, const oeVec2& axis) {
    oeVec2 interval;

    oeVec2 direction_vector = oeVec2::normalize(axis);
    oeVec2 direction_and_radius = direction_vector * radius;

    oeVec2 p1 = center + direction_and_radius;
    oeVec2 p2 = center - direction_and_radius;

    interval.x = oeVec2::dot(p1, axis);
    interval.y = oeVec2::dot(p2, axis);

    if (interval.x > interval.y) {
        float temp;
        temp = interval.x;
        interval.x = interval.y;
        interval.y = temp;
    }
    return interval;
}

//�ҵ�����ξ��������Ķ���
static size_t FindVertexClosestPoint(const oeVec2& point, const std::vector<oeVec2>& vertices) {
    size_t result = 0;
    float min_distance = std::numeric_limits<float>::max();
    for (size_t i = 0; i < vertices.size(); ++i) {
        float distance = oeVec2::Distance(vertices[i], point);
        if (distance <= min_distance) {
            min_distance = distance;
            result = i;
        }
    }
    return result;
}




//�������AABB�⽫������㵽AABB�ľ����ƽ��
//�������AABB�ϻ�����AABB�ڽ������0
static float DistSqdPointAABB(const oeVec2& p, const std::vector<oeVec2>& vertices_aabb) {
    float sqDist = 0.0f;
    for (int i = 0; i < 2; i++) {
        float v, min, max;
        if (i == 0)
        {
            v = p.x;
            min = vertices_aabb[3].x;
            max = vertices_aabb[1].x;
            /*��iΪ0ʱ��Ӧx
            v����Ϊ�� p �� x ���ꡣ
            min ����Ϊ�߽�����Ͻǵ�� x ���꣨vertices_aabb[3].x����
            max ����Ϊ�߽�����½ǵ�� x ���꣨vertices_aabb[1].x����*/
        }
        if (i == 1)
        {
            v = p.y;
            min = vertices_aabb[3].y;
            max = vertices_aabb[1].y;
            /*��iΪ1ʱ��Ӧy
            v����Ϊ�� p �� y ���ꡣ
            min ����Ϊ�߽�����Ͻǵ�� y ���꣨vertices_aabb[3].y����
            max ����Ϊ�߽�����½ǵ�� y ���꣨vertices_aabb[1].y����y*/
        }
        if (v >= min && v <= max) return 0.0f;//�����AABB����ֱ�ӷ���0��
        if (v < min) sqDist += (min - v) * (min - v);
        if (v > max) sqDist += (v - max) * (v - max);
    }
    return sqDist; // ����ƽ����  
}


//�������ֱ�ߵĽӴ���
//��ԭ���Ǽ��������߶��ĸ��˵����ô�Ǹ��˵㼫�п����ǽӴ���
static oeVec2 GetSegmentContactPoint(const oeVec2& point, const oeVec2& segment_start, const oeVec2& segment_end) {
    oeVec2 segment_vector = segment_end - segment_start;//�����߶�����
    oeVec2 point_to_segment_start_vector = point - segment_start;//������߶����ָ��������

    float projection_length = oeVec2::dot(point_to_segment_start_vector, segment_vector);
    float segment_length_squared = oeVec2::LengthSquared(segment_vector);
    float projection_parameter = projection_length / segment_length_squared;//����ͶӰ���� proj_param = (|AP||AB| * cos(��)) / |AB|^2

    if (projection_parameter <= 0) {
        return segment_start;
    }
    if (projection_parameter >= 1) {
        return segment_end;
    }
    else {
        return segment_start + (segment_end - segment_start) * projection_parameter;
    }
}

//�������ֱ�ߵ�����㣨���ܵĽӴ��㣩���������(���ܵĽӴ���)
inline oeVec2 SegmentNearestEndpoint(const float& projection_parameter, const oeVec2& segment_start, const oeVec2& segment_end) {
    if (projection_parameter <= 0) {
        return segment_start;
    }
    if (projection_parameter >= 1) {
        return segment_end;
    }
    else {
        return segment_start + (segment_end - segment_start) * projection_parameter;
    }
}

//���������߶�����Ķ˵�ľ����ƽ��
static float DisSqdPointSegmentNearestEndpoint(const oeVec2& point, const oeVec2& segment_start, const oeVec2& segment_end) {
    oeVec2 segment_vector = segment_end - segment_start;//�����߶�����
    oeVec2 point_to_segment_start_vector = point - segment_start;//������߶����ָ��������

    float projection_length = oeVec2::dot(point_to_segment_start_vector, segment_vector);
    float segment_length_squared = oeVec2::LengthSquared(segment_vector);
    float projection_parameter = projection_length / segment_length_squared;//����ͶӰ���� proj_param = (|AP||AB| * cos(��)) / |AB|^2

    oeVec2 closest_point = SegmentNearestEndpoint(projection_parameter, segment_start, segment_end);
    float distance_squared = oeVec2::DistanceSquared(point, closest_point);

    return distance_squared;
}


//�������ռ������Ѱ������������ĽӴ���ĺ���
//�����������ռ���Ϊ�˴���ģ�黯��ʹ����ṹ������
namespace FindContactPoint {

    /*�ҵ�Բ��Բ��ײʱ�ĽӴ���*/
    static oeVec2 FindCirclesContactPoint(const oeVec2& center_a, const float& radius_a, const oeVec2& center_b) {
        oeVec2 v_ab = center_b - center_a;
        v_ab.normalize();
        oeVec2 contact_point = center_a + v_ab * radius_a;
        return contact_point;
    }


    /*�ҵ�Բ��������ײʱ�ĽӴ���*/
    static oeVec2 FindCirclePolygonContactPoint(const oeVec2& circle_center, const std::vector<oeVec2>& polygon_vertices) {
        float min_distance_Sq = std::numeric_limits<float>::max();
        oeVec2 contact_point;

        for (int i = 0; i < static_cast<int>(polygon_vertices.size()); i++) {
            oeVec2 v_a = polygon_vertices[i];
            oeVec2 v_b = polygon_vertices[(i + 1) % polygon_vertices.size()];

            float distance_sq = DisSqdPointSegmentNearestEndpoint(circle_center, v_a, v_b);

            if (distance_sq < min_distance_Sq) {
                min_distance_Sq = distance_sq;
                contact_point = GetSegmentContactPoint(circle_center, v_a, v_b);
            }
        }
        return contact_point;
    }

    //�ҵ�����������εĽӴ���
    static std::vector<oeVec2> FindPolygonsContactPoints(const std::vector<oeVec2>& vertices_a, const std::vector<oeVec2>& vertices_b) {
        //��ʼ���Ӵ���
        std::vector<oeVec2> contact_points;
        oeVec2 contact1;//��һ���Ӵ���
        oeVec2 contact2;//�ڶ����Ӵ��㣬���û�еڶ����Ӵ��㣬�򱣳�Ϊԭ�� 
        size_t contact_count = 0;

        //��ʼ����С�����ƽ��Ϊ��������ں����Ƚ�
        float min_distancesq = std::numeric_limits<float>::max();

        //������һ������ε�ÿ�����㣬���������ڶ��������ÿ���ߵľ���  
        for (oeVec2 point : vertices_a) {

            for (size_t j = 0; j < vertices_b.size(); j++) {
                oeVec2 v_a = vertices_b[j];//�ڶ�������εĵ�ǰ�ߵ����
                oeVec2 v_b = vertices_b[(j + 1) % vertices_b.size()];//�ڶ�������εĵ�ǰ�ߵ��յ㣬ʹ��ģ���㴦��պ϶����  
                float distancesq = DisSqdPointSegmentNearestEndpoint(point, v_a, v_b);
                oeVec2 cloesest_point = GetSegmentContactPoint(point, v_a, v_b);

                //�����ǰ�����ƽ������������С�����ƽ���������½Ӵ��㲻���ڵ�һ���Ӵ���  
                if (oeVec2::NearlyEqual(distancesq, min_distancesq)) {
                    if (!oeVec2::NearlyEqualFv(cloesest_point, contact1)) {
                        contact2 = cloesest_point;
                        contact_count = 2;
                    }
                }
                else if (distancesq < min_distancesq) {
                    min_distancesq = distancesq;
                    contact_count = 1;
                    contact1 = cloesest_point;
                }
            }
        }
        // �Եڶ���������ظ��������̣��Դ���������ڶ���θ�����״����©�ĽӴ���
        for (oeVec2 point : vertices_b) {

            for (size_t j = 0; j < vertices_a.size(); j++) {
                oeVec2 v_a = vertices_a[j];//�ڶ�������εĵ�ǰ�ߵ����
                oeVec2 v_b = vertices_a[(j + 1) % vertices_a.size()];//�ڶ�������εĵ�ǰ�ߵ��յ㣬ʹ��ģ���㴦��պ϶����  
                float distancesq = DisSqdPointSegmentNearestEndpoint(point, v_a, v_b);
                oeVec2 cloesest_point = GetSegmentContactPoint(point, v_a, v_b);


                //�����ǰ�����ƽ������������С�����ƽ���������½Ӵ��㲻���ڵ�һ���Ӵ���
                if (oeVec2::NearlyEqual(distancesq, min_distancesq)) {
                    if (!oeVec2::NearlyEqualFv(cloesest_point, contact1)) {
                        contact2 = cloesest_point;
                        contact_count = 2;
                    }
                }
                else if (distancesq < min_distancesq) {
                    min_distancesq = distancesq;
                    contact_count = 1;
                    contact1 = cloesest_point;

                }
            }
        }

        //�жϽӴ������
        if (contact_count == 1) {
            contact_points.push_back(contact1);
        }
        else {
            contact_points.push_back(contact1);
            contact_points.push_back(contact2);
        }


        return contact_points;
    }


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


 

//
////�ҵ�������ײ����ĽӴ���
//static std::vector<oeVec2> FindContactPoints(oeBody& body_a, oeBody& body_b) {
//    std::vector<oeVec2> contact_points;
//    Shape shape_type_a = body_a.shape_;
//
//    Shape shape_type_b = body_b.shape_;
//    if (shape_type_a == POLTGON) {
//        if (shape_type_b == POLTGON) {
//            contact_points = FindContactPoint::FindPolygonsContactPoints(body_a.vertices_, body_b.vertices_);
//            return contact_points;
//        }
//        else if (shape_type_b == CIRCLE) {
//            contact_points.push_back(FindContactPoint::FindCirclePolygonContactPoint(body_b.mass_center_, body_a.vertices_));
//            return contact_points;
//        }
//    }
//    else if (shape_type_a == CIRCLE) {
//        if (shape_type_b == CIRCLE) {
//            contact_points.push_back(FindContactPoint::FindCirclesContactPoint(body_a.mass_center_, body_a.radius_, body_b.mass_center_));
//            return contact_points;
//        }
//        else if (shape_type_b == POLTGON) {
//            contact_points.push_back(FindContactPoint::FindCirclePolygonContactPoint(body_a.mass_center_, body_b.vertices_));
//            return contact_points;
//        }
//
//    }
//    return contact_points;
//}


//�ж����������Ƿ���ײ�������������ײboolֵ����ײ���,��ײ����
static IntersectData  Collide(oeBody& body_a, oeBody& body_b) {
    IntersectData intersect_data;
    Shape shape_type_a = body_a.shape_;
    Shape shape_type_b = body_b.shape_;

    if (shape_type_a == POLTGON) {
        if (shape_type_b == POLTGON) {
            
        }
        else if (shape_type_b == CIRCLE) {
            
        }
    }
    else if (shape_type_a == CIRCLE) {
        if (shape_type_b == CIRCLE) {
            
        }
        else if (shape_type_b == POLTGON) {
            
        }
    }

    return intersect_data;
}

