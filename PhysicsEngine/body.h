#pragma once
#include <vector>
#include "math.h"
#include <iostream>
#include "forcegenerator.h"
const int the_maximum_vertices = 8;


enum Shape {
	NONE,
	CIRCLE,
	POLYGON
	
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

private:
	
	//�ܶ�
	float density_ = 0.1f;

	//���
	float volume_ = 1.0f;
	
	//���
	float area_ = 1.0f;

	
public:
	//������ת�ĽǶ�
	float angle_ = 0.0f;

	oeVec2 force_;
	
	oeVec2 constant_force_;

	//����Ľ��ٶ�,���ڶ�ά����½��ٶȵķ����Ǵ�ֱ����Ļ������ʹ��float
	float angular_velocity_ = 0.0f;

	//��������ٶ�
	oeVec2 velocity_ = { 0.0f,0.0f };

	//����ļ��ٶ�
	oeVec2 acceleration_ = { 0.0f,0.0f };

	//�����id
	int body_id_ = -1;

	//�������״
	Shape shape_ = NONE;

	float radius_ = 0.0f;

	//�������ɫ�ֱ��Ӧ��rgba
	float color_[4] = { 0,0,0,0 };

	//position�����λ��
	oeVec2 mass_center_ = { 0.0f,0.0f };

	//polygon��״ר������
	oeVec2 vertices_[the_maximum_vertices] = {};

	//������
	int vertices_count_ = 0;

	//aabb��Χ�еĶ���
	oeAABB aabb_;

	//aabb��Χ�е���ɫ
	float aabb_color_[4] = { 0,0,0,0 };

	//����
	float mass_ = 0.0f;

	//���������ĵ���
	float inverse_mass_ = 0.0f;

	//�Ƿ��Ǿ�ֹ����
	bool stationary_ = false;

	//�̶���Ħ����
	float inherent_static_friction_ = 0.5f;

	//�̶���Ħ����
	float inherent_dynamic_friction_ = 0.3f;

	float rotational_inertia_ = 0.0f;
	//ת�������ĵ���
	float inverse_rotational_inertia_ = 0.0f;
	// ����Ļָ�ϵ��
	float restitution_ = 0.0f;

	//�������������
	~oeBody();
	//oeBody();

	//Circle���캯��
	oeBody(Shape shape, float radius_or_width, float* color,oeVec2 mass_center,float mass,bool state,float restitution,float inherent_static_friction_,float inherent_dynamic_friction_);

	//Polygon���캯�������غ���
	oeBody(Shape shape, oeVec2* vertices,int vertices_count, float* color, float mass, bool state, float restitution, float inherent_static_friction_, float inherent_dynamic_friction_);


	void Move(const oeVec2 v);
	void MoveTo(const oeVec2 v);
	void Rotation(const float angle);

	void SetVelocity(const oeVec2 v0);
	void SetAcceleration(const oeVec2 a0);
	void SetAngle(const float angle);
	void SetAngularVelocity(const float av0);

	float  GetArea() const;
	float  GetMass() const;
	float  GetDensity() const;
	float  GetVolume() const;
	float  GetAngle() const;
	float  GetAngularVelocity() const;
	float  GetRestitution()const;
	bool   GetBodyState() const;
	oeVec2 GetVelocity() const;
	oeVec2 GetAcceleration() const;

	
	



	void GetAABB();
	oeVec2 GetPolygonCentroid() const;


	void Update(float time,int iterations);
};


