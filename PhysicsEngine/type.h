#pragma once
#include "math.h"
#include "body.h"
struct CircleType
{
	float radius = 0.1f;
	oeVec2 position = { 0.0f,0.0f };
	float color[4] = { 1.0f, 0.0f, 0.0f ,0.3f };
};

struct PolygonType {
	int vertices_count = 4;
	oeVec2 vertices[the_maximum_vertices] = {	{-0.1f, 0.1f},	// --------
												{-0.1f,-0.1f},	// |	  |
												{ 0.1f,-0.1f},	// |	  |
												{ 0.1f, 0.1f} };// --------
	float color[4] = { 1.0f, 0.0f, 0.0f ,0.3f };
};


struct Property {
	//�Ƿ��Ǿ�ֹ����
	bool stationary_ = false;

	//���������
	float mass_ = 1.0f;//g

	//����Ļָ�ϵ��
	float restitution_ = 0.0f;

	//�̶���Ħ����
	float inherent_static_friction_ = 0.5f;

	//�̶���Ħ����
	float inherent_dynamic_friction_ = 0.3f;

	oeVec2 constant_force = { 0.0f,0.0f };
};








