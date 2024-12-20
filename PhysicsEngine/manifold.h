#pragma once
#include "math.h"
#include "body.h"
struct IntersectData {
    /*
        �ཻ�������
        Collision���Ƿ���ײ���ཻ��
            depth: ��ײ���
           normal����������
    */
    bool Collision = false;
    float depth = std::numeric_limits<float>::max();
    oeVec2 normal;
    
};

struct ContactData {
    /*
       �Ӵ�����
       contact_count���Ӵ���ĸ���һ��С�ڵ���2��
            contact1: �Ӵ���һ������
            contact2���Ӵ����������
   */
    int contact_count = 0;
    oeVec2 contact1 = { 0.0f,0.0f };
    oeVec2 contact2 = { 0.0f,0.0f };;
};


struct Manifold {
    /*
        �Ӵ���������
                body_a���Ӵ�����A
                body_b���Ӵ�����B
          contact_data���Ӵ�����
        intersect_data���ཻ����
    */
    oeBody* body_a = nullptr;
    oeBody* body_b = nullptr;
    ContactData contact_data;
    IntersectData intersect_data;
    oeVec2 r1, r2;
    float separation;
    float Pn;	// accumulated normal impulse
    float Pt;	// accumulated tangent impulse
    float Pnb;	// accumulated normal impulse for position bias
    float massNormal, massTangent;
    float bias;
};