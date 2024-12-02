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
	bool draw_state = false;
	oeVec2 max;
	oeVec2 min;
};



//������
//���ܣ��Ǳ����������������Ԫ�أ� ���е����嶼��Body�࣬ͨ������ֱ�ӵ���Body�Ĺ��캯���������壬��Ҫͨ��BodyManager��CreateBody��������������
//�ܴ�������Σ�Բ��������״����������������˻�������������
class oeBody {
public:

	//���������������ֵ
	//�����id
	int body_id_ = -1;

	//�������״
	Shape shape_ = NONE;

	float radius_or_half_width_ = 0.0f;

	//�������ɫ�ֱ��Ӧ��rgba
	float color_[4] = { 0,0,0,0 };

	//position�����λ��
	oeVec2 mass_center_ = { 0.0f,0.0f };

	//polygon��״ר������
	oeVec2 vertices_[the_maximum_vertices] = {};

	int vertices_count_ = 0;

	//aabb��Χ�еĶ���
	oeAABB aabb_;

	//aabb��Χ�е���ɫ
	float aabb_color_[4] = { 0,0,0,0 };

	//�Ƿ��Ǿ�ֹ����
	bool stationary_ = false;





	
	float density_ = 0.1f;

	float mass_ = 1.0f;

	float volume_ = 1.0f;

	float area_ = 1.0f;
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
	oeBody(Shape shape, float radius_or_width, float* color,oeVec2 mass_center,float mass);

	//Polygon���캯�������غ���
	//���δ��������shape,vertices��color,mass>0,mass_center,body_id����ѡ��������ʹ���ظ�id��ͨ��body_list�鿴���������id��
	oeBody(Shape shape, oeVec2* vertices,int vertices_count, float* color, float mass);


	void Move(const oeVec2 v);
	void Rotation(const float angle);
	void GetAABB();
};


