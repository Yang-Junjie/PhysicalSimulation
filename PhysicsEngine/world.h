#pragma once
#include "math.h"
#include "body.h"
#include <vector>
#include "type.h"
#include "Renderer.h"
#include "collision.h"

class oeWorld {
private:
	Renderer* renderer_;										//��Ⱦ��
	int id_count = -1;											//�������±��0��1��2������������n
	std::vector<oeBody*> bodys_list_;							//�����б�
	std::vector<std::pair<oeBody*, oeBody*>> contact_body_;		//�Ӵ������
	
	
	void SepareteBodies(oeBody& body_a, oeBody& body_b, oeVec2& separation_vector); //����Ӵ�����
	void BroadPhase();																
	void NarrowPhase(float dt);
public:
	
	oeWorld(Renderer* renderer);
	~oeWorld();
	
	
	oeBody* CreatCircle(CircleType type_data, Property prop_data);
	oeBody* CreatPolygon(PolygonType type_data,Property prop_data);
	void ClearBodys();


	void RenderBody();
	void RenderAABB();

	int GetBodyNum() const;
	oeBody* FindBody(const int id);
	std::vector<oeBody*>* GetBodysList();

	//��������
	void Interation(float time,int iterations);

	
};

