#pragma once
#include <vector>
#include "math.h"
#include <iostream>
const int the_maximum_vertices = 8;


enum Shape {
	NONE,
	CIRCLE,
	POLTGON,
	BOX
};

struct oeAABB
{
	oeVec2 lowerBound;
	oeVec2 upperBound;
};



//������
//���ܣ��Ǳ����������������Ԫ�أ� ���е����嶼��Body�࣬ͨ������ֱ�ӵ���Body�Ĺ��캯���������壬��Ҫͨ��BodyManager��CreateBody��������������
//�ܴ�������Σ�Բ��������״����������������˻�������������
class oeBody {
public:

	//���������������ֵ
	//�����id
	int body_id_ = 0;

	//�������״
	Shape shape_ = NONE;

	//Բ������ר�����԰뾶
	float radius_or_width_ = 0.0f;

	//�������ɫ�ֱ��Ӧ��rgba
	float color_[4] = { 0,0,0,0 };

	//position�����λ��
	oeVec2 mass_center_ = { 0.0f,0.0f };

	//polygon��״ר������
	oeVec2 vertices_[the_maximum_vertices] = {};

	int vertices_count_ = 0;

	//aabb��Χ�еĶ���
	oeAABB aabb_;
	
	float color_box_[4] = {1, 1, 1, 1};
	struct shuxing
	{
		

	////��������ֵ
	////�����Ƿ�ֹ��false->�Ǿ�ֹ��true->��ֹ
	//bool stationary_ = true;

	////����Ļָ�ϵ��
	//float restitution_ = 0.0f;

	////������ת�ĽǶ�
	//float angle = 0.0f;

	////����Ľ��ٶ�,���ڶ�ά����½��ٶȵķ����Ǵ�ֱ����Ļ������ʹ��float
	//float angular_velocity_ = 0.0f;

	////������ܶ�
	//float density_ = 0.0f;

	////���������
	//float mass_ = 1.0f;

	////���������ĵ���
	//float inverse_mass_ = 0.0f;

	

	////��������ٶ�
	//oeVec2 velocity_ = { 0.0f,0.0f };

	////����ļ��ٶ�
	//oeVec2 acceleration_ = { 0.0f,0.0f };

	////�̶���Ħ����
	//float inherent_static_friction_ = 0.5f;

	////�̶���Ħ����
	//float inherent_dynamic_friction_ = 0.3f;

	////ת������
	//float rotational_inertia_ = 0.0f;

	////ת�������ĵ���
	//float inverse_rotational_inertia_ = 0.0f;
	};

	//�������������
	~oeBody();
	oeBody();

	//Circle Box���캯��
	//���δ��������shape,radius��color,mass>0,mass_center,body_id����ѡ��������ʹ���ظ�id��ͨ��body_list�鿴���������id��
	oeBody(Shape shape, float radius_or_width, float* color,oeVec2 mass_center);

	//Polygon���캯�������غ���
	//���δ��������shape,vertices��color,mass>0,mass_center,body_id����ѡ��������ʹ���ظ�id��ͨ��body_list�鿴���������id��
	oeBody(Shape shape, oeVec2* vertices,int vertices_count, float* color);


	void Move(const oeVec2 v);
	void Rotation(const float angle);
	void GetAABB();
};


