/*
	by yangjunjie,website http://beisent.com
*/

#pragma once
#include <vector>
#include "math.h"
#include <iostream>
#include "forcegenerator.h"
#include "Constraint.h"
const int the_maximum_vertices = 8;

//��״
enum Shape {
	NONE,		//����״һ�����ڳ�ʼ�������Ѿ����ٵ�����
	CIRCLE,		//Բ��
	POLYGON		//�����
};


//AABB
struct oeAABB
{
	bool draw_state = false;	//�Ƿ����AABB
	oeVec2 max;					//���ϽǶ�������
	oeVec2 min;					//���½Ƕ�������
};



//������
//���ܣ��Ǳ����������������Ԫ�أ� ���е����嶼��Body�࣬ͨ������ֱ�ӵ���Body�Ĺ��캯���������壬��Ҫͨ��BodyManager��CreateBody��������������
//�ܴ�������Σ�Բ��������״����������������˻�������������
class oeBody {

private:
	float density_ = 0.1f;						//�ܶ�

	float volume_ = 1.0f;						//���
		
	float area_ = 1.0f;							//���
public:
	float angle_ = 0.0f;						//������ת�ĽǶ�

	oeVec2 force_ = oeVec2::Zero();				//����
	
	oeVec2 constant_force_ = oeVec2::Zero();	//����

	float angular_velocity_ = 0.0f;				//����Ľ��ٶ�

	oeVec2 velocity_ = { 0.0f,0.0f };			//��������ٶ�	

	oeVec2 acceleration_ = { 0.0f,0.0f };		//����ļ��ٶ�

	int body_id_ = -1;							//�����id�������ڱ�ʾΪ-1

	Shape shape_ = NONE;						//�������״

	float radius_ = 0.0f;						//����İ뾶

					  /*r g b a*/
	float color_[4] = { 0,0,0,0 };				//�������ɫ�ֱ��Ӧ��

	oeVec2 mass_center_ = { 0.0f,0.0f };		//�����λ��

	oeVec2 vertices_[the_maximum_vertices] = {};//polygon��״ר������

	int vertices_count_ = 0;					//������

	oeAABB aabb_;								//aabb��Χ�еĶ���

	float aabb_color_[4] = { 0,0,0,0 };			//aabb��Χ�е���ɫ

	float mass_ = 0.0f;							//����

	float inverse_mass_ = 0.0f;					//���������ĵ���

	bool stationary_ = false;					//�Ƿ��Ǿ�ֹ����

	float inherent_static_friction_ = 0.5f;		//�̶���Ħ����

	float inherent_dynamic_friction_ = 0.3f;	//�̶���Ħ����

	float rotational_inertia_ = 0.0f;			//ת������
	
	float inverse_rotational_inertia_ = 0.0f;	//ת�������ĵ���
	
	float restitution_ = 0.0f;					//����Ļָ�ϵ��

	//�������������
	~oeBody();
	//oeBody();

	//Circle���캯��
	oeBody(Shape shape, float radius_or_width, float* color,oeVec2 mass_center,float mass,bool state,float restitution,float inherent_static_friction_,float inherent_dynamic_friction_);

	//Polygon���캯�������غ���
	oeBody(Shape shape, oeVec2* vertices,int vertices_count, float* color, float mass, bool state, float restitution, float inherent_static_friction_, float inherent_dynamic_friction_);
	
	//��ȡAABB��Χ��
	void GetAABB();
	
	//�������ƶ�v
	void Move(const oeVec2 v);

	//�������ƶ���v��
	void MoveTo(const oeVec2 v);
	
	//��������תradian�ȵ�λ�ǻ���
	void Rotation(const float radian);

	//����������ٶ�
	void SetVelocity(const oeVec2 v0);

	//��������ļ��ٶ�
	void SetAcceleration(const oeVec2 a0);

	//��������Ľ��ٶ�
	void SetAngularVelocity(const float av0);

	//float  GetArea() const;
	//float  GetMass() const;
	//float  GetDensity() const;
	//float  GetVolume() const;
	//float  GetAngle() const;

	float  GetAngularVelocity() const;
	float  GetRestitution()const;
	bool   GetBodyState() const;
	oeVec2 GetVelocity() const;
	oeVec2 GetAcceleration() const;

	//��ö���ε���������
	oeVec2 GetPolygonCentroid() const;

	void Update(float time,int iterations, std::vector<Constraint*>& globalConstraints);
};


