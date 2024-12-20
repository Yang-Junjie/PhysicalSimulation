#include "world.h"
#include <map>

using std::vector;
using std::map;
using std::pair;

static void ResolveCollisionWithRotationAndFriction(Manifold& contact);
static void PreStep(Manifold* manifold_, float inv_dt);
static void ApplyImpulse(Manifold*);

oeWorld::oeWorld(Renderer* renderer)
	:renderer_(renderer)
{
	
}

oeWorld::~oeWorld()
{
	
	ClearBodys();
}

void oeWorld::CreatCircle(CircleType type_data, Property prop_data)
{
	oeBody* tmp = new oeBody(CIRCLE,type_data.radius, type_data.color, type_data.position, prop_data.mass_, prop_data.stationary_, prop_data.restitution_, prop_data.inherent_static_friction_, prop_data.inherent_dynamic_friction_);
	++id_count;
	tmp->body_id_ = id_count;
	tmp->constant_force_ = prop_data.constant_force;
	bodys_list_.push_back(tmp);
	//bodys_list_[id_count] = tmp;
	//AddBody(*FindBody(id_count));
}

void oeWorld::CreatPolygon(PolygonType type_data,Property prop_data)
{
	oeBody* tmp = new oeBody(POLYGON, type_data.vertices, type_data.vertces_count, type_data.color,prop_data.mass_,prop_data.stationary_, prop_data.restitution_, prop_data.inherent_static_friction_, prop_data.inherent_dynamic_friction_);
	++id_count;
	tmp->body_id_ = id_count;
	tmp->constant_force_ = prop_data.constant_force;
	bodys_list_.push_back(tmp);
	
	//bodys_list_[id_count] = tmp;
	//AddBody(*FindBody(id_count));
}

void oeWorld::ClearBodys()
{
	for (auto& body : bodys_list_) {
		delete body;
	}
}


oeBody* oeWorld::FindBody(const int id)
{
	if (bodys_list_[id]->body_id_ == -1) {
		return nullptr;
	}
	else {
		return bodys_list_[id];
	}
}

void oeWorld::RenderBody()
{
	for (auto& body : bodys_list_) {
		if (body->shape_ == CIRCLE) {
			
			renderer_->drawCircle(body->mass_center_.x, body->mass_center_.y, body->radius_, body->color_,36);
		}
		else if (body->shape_ == POLYGON) {
			renderer_->drawPolygon(body->vertices_, body->vertices_count_, body->color_);
		}
	}
}

void oeWorld::RenderAABB()
{
	
	for (auto& body : bodys_list_) {
		renderer_->drawAABB(body->aabb_,body->aabb_color_);
	}
}



void oeWorld::Interation(float dt,int iterations)
{
	float inv_dt = dt > 0.0f ? 1.0f / dt : 0.0f;
	//ÿ�ε���ǰ���aabb�ཻ������
	this->contact_body_.clear();
	BroadPhase();

	for (auto& body : bodys_list_) {
		if (!body->GetBodyState()) {
			body->Update(dt, iterations);
		}
	}
	NarrowPhase(dt);
	
}


int oeWorld::GetBodyNum() const
{
	return id_count+1;
}

std::vector<oeBody*>* oeWorld::GetBodysList()
{
	return &bodys_list_;
}


//��������
void oeWorld::SepareteBodies(oeBody& body_a, oeBody& body_b, oeVec2& separation_vector)
{
	if (body_a.GetBodyState()) {
		body_b.Move(separation_vector / 2);
	}
	else if (body_b.GetBodyState()) {
		body_a.Move(-separation_vector / 2);
	}
	else {
		body_a.Move(-separation_vector / 2);
		body_b.Move(separation_vector / 2);
	}
}

void oeWorld::BroadPhase() {
	// ����Ҫ��aabb��ɫ��������б��
	std::unordered_map<int, bool> colored;

	//����ȥ�أ�����circle��polygonǰ��ʱ���bug
	// ��ʼ�ж����������aabb�Ƿ��ཻ
	for (size_t i = 0; i < bodys_list_.size(); ++i) {
		auto& body_a = bodys_list_[i];
		body_a->GetAABB();

		for (size_t j = 0; j < bodys_list_.size(); ++j) {
			auto& body_b = bodys_list_[j];
			body_b->GetAABB();
			if (body_a->GetBodyState() && body_b->GetBodyState() || body_a->body_id_ == body_b->body_id_) {
				continue;
			}
			
			// ���
			bool intersect = Intersect::IntersectAABB(body_a->aabb_, body_b->aabb_);

			// ���û���ཻ�������һ������ļ��
			if (!intersect) {
				continue;
			}
			else {
				colored[body_a->body_id_] = true;
				colored[body_b->body_id_] = true;
				std::pair<oeBody*, oeBody*> pair_body(body_a, body_b);
				contact_body_.push_back(pair_body);



			}
		}
	}
	//�ٶԱ�ǹ��������aabb������ɫ
	for (auto& body : bodys_list_) {
		if (colored[body->body_id_]) {

			body->aabb_color_[0] = 1.0f;
			body->aabb_color_[1] = 1.0f;
			body->aabb_color_[2] = 1.0f;
			body->aabb_color_[3] = 1.0f;

		}
		else {
			body->aabb_color_[0] = 1.0f;
			body->aabb_color_[1] = 0.0f;
			body->aabb_color_[2] = 0.0f;
			body->aabb_color_[3] = 1.0f;
		}
	}
}


void oeWorld::NarrowPhase(float dt)
{
	//����AABB�ཻ������
	for (auto& pair : this->contact_body_) {

		//������������ʹ����ײ��⣬�ж������������Ƿ�����ײ
		IntersectData intersect_data = Collide(*pair.first, *pair.second);
		
		//���������ײ��������������������������������
		if (intersect_data.Collision) {
			oeVec2 separation_vector = intersect_data.normal * intersect_data.depth;
			SepareteBodies(*pair.first, *pair.second, separation_vector);
			ContactData contact_data = FindContactPoints(*pair.first, *pair.second);
			Manifold manifold = { pair.first, pair.second,contact_data,intersect_data };
			ResolveCollisionWithRotationAndFriction(manifold);





			//	|
			// �Ӵ�Լ��
			// PreStep(&manifold,dt);
			// ApplyImpulse(&manifold);
		}

	}
}

static void PreStep(Manifold* manifold_,float inv_dt)
{
	const float k_allowedPenetration = 0.01f;
	float k_biasFactor = 0.2f; //World::positionCorrection ? 0.2f : 0.0f;
	oeBody* body1 = manifold_->body_a;
	oeBody* body2 = manifold_->body_b;
	for (int i = 0; i < manifold_->contact_data.contact_count; ++i)
	{
		

		oeVec2 r1 = manifold_->contact_data.contact1 - body1->mass_center_;
		oeVec2 r2 = manifold_->contact_data.contact1 - body2->mass_center_;

		// Precompute normal mass, tangent mass, and bias.
		float rn1 = oeVec2::dot(r1, manifold_->intersect_data.normal);
		float rn2 = oeVec2::dot(r2, manifold_->intersect_data.normal);
		float kNormal = body1->inverse_mass_ + body2->inverse_mass_;
		kNormal += body1->inverse_rotational_inertia_ * (oeVec2::dot(r1, r1) - rn1 * rn1) + body2->inverse_rotational_inertia_ * (oeVec2::dot(r2, r2) - rn2 * rn2);
		manifold_->massNormal = 1.0f / kNormal;

		oeVec2 tangent = oeVec2::cross(manifold_->intersect_data.normal, 1.0f);
		float rt1 = oeVec2::dot(r1, tangent);
		float rt2 = oeVec2::dot(r2, tangent);
		float kTangent = body1->inverse_mass_ + body2->inverse_mass_;
		kTangent += body1->inverse_rotational_inertia_ * (oeVec2::dot(r1, r1) - rt1 * rt1) + body2->inverse_rotational_inertia_ * (oeVec2::dot(r2, r2) - rt2 * rt2);
		manifold_->massTangent = 1.0f / kTangent;

		manifold_->bias = -k_biasFactor * inv_dt * Min(0.0f, manifold_->separation + k_allowedPenetration);

		/*if (World::accumulateImpulses)
		{*/
		// Apply normal + friction impulse
		oeVec2 P = manifold_->Pn * manifold_->intersect_data.normal + manifold_->Pt * tangent;

		body1->velocity_ -= body1->inverse_mass_ * P;
		body1->angular_velocity_ -= body1->inverse_rotational_inertia_ * oeVec2::cross(r1, P);

		body2->velocity_ += body2->inverse_mass_ * P;
		body2->angular_velocity_ += body2->inverse_rotational_inertia_ * oeVec2::cross(r2, P);
		//}
	}
}

static void ApplyImpulse(Manifold* manifold_)
{
	oeBody* b1 = manifold_->body_a;
	oeBody* b2 = manifold_->body_b;
	
		
	float friction = sqrtf(b1->inherent_dynamic_friction_*b2->inherent_dynamic_friction_);

	for (int i = 0; i < manifold_->contact_data.contact_count; ++i)
	{

		manifold_->r1 = manifold_->contact_data.contact1 - b1->mass_center_;
		manifold_->r2 = manifold_->contact_data.contact2 - b2->mass_center_;

		// Relative velocity at contact
		oeVec2 dv = b2->velocity_ + oeVec2::cross(b2->angular_velocity_, manifold_->r2) - b1->velocity_ - oeVec2::cross(b1->angular_velocity_, manifold_->r1);

		// Compute normal impulse
		float vn = oeVec2::dot(dv, manifold_->intersect_data.normal);

		float dPn = manifold_->massNormal * (-vn + manifold_->bias);

		/*if (World::accumulateImpulses)
		{*/
		// Clamp the accumulated impulse
		float Pn0 = manifold_->Pn;
		manifold_->Pn = std::max(Pn0 + dPn, 0.0f);
		dPn = manifold_->Pn - Pn0;
		/*}
		else
		{
			dPn = Max(dPn, 0.0f);
		}*/

		// Apply contact impulse
		oeVec2 Pn = dPn * manifold_->intersect_data.normal;

		b1->velocity_ -= b1->inverse_mass_ * Pn;
		b1->angular_velocity_ -= b1->inverse_rotational_inertia_ * oeVec2::cross(manifold_->r1, Pn);

		b2->velocity_ += b2->inverse_mass_ * Pn;
		b2->angular_velocity_ += b2->inverse_rotational_inertia_ * oeVec2::cross(manifold_->r2, Pn);

		// Relative velocity at contact
		dv = b2->velocity_ + oeVec2::cross(b2->angular_velocity_, manifold_->r2) - b1->velocity_ - oeVec2::cross(b1->angular_velocity_, manifold_->r1);

		oeVec2 tangent = oeVec2::cross(manifold_->intersect_data.normal, 1.0f);
		float vt = oeVec2::dot(dv, tangent);
		float dPt = manifold_->massTangent * (-vt);

		/*if (World::accumulateImpulses)
		{*/
		// Compute friction impulse
		float maxPt = friction * manifold_->Pn;

		// Clamp friction
		float oldTangentImpulse = manifold_->Pt;
		manifold_->Pt = Clamp(oldTangentImpulse + dPt, -maxPt, maxPt);
		dPt = manifold_->Pt - oldTangentImpulse;
		/*}
		else
		{
			float maxPt = friction * dPn;
			dPt = Clamp(dPt, -maxPt, maxPt);
		}*/

		// Apply contact impulse
		oeVec2 Pt = dPt * tangent;

		b1->velocity_ -= b1->inverse_mass_ * Pt;
		b1->angular_velocity_ -= b1->inverse_rotational_inertia_ * oeVec2::cross(manifold_->r1, Pt);

		b2->velocity_ += b2->inverse_mass_ * Pt;
		b2->angular_velocity_ += b2->inverse_rotational_inertia_ * oeVec2::cross(manifold_->r2, Pt);
	}
}

static void ResolveCollisionWithRotationAndFriction(Manifold& contact) {
	oeBody* bodyA = contact.body_a;
	oeBody* bodyB = contact.body_b;
	
	oeVec2 normal = contact.intersect_data.normal;
	oeVec2 contact1 = contact.contact_data.contact1;
	oeVec2 contact2 = contact.contact_data.contact2;

	const int contactCount = contact.contact_data.contact_count;

	float e = std::min(bodyA->restitution_, bodyB->restitution_); // ��ײ�ָ�ϵ��
	float sf = (bodyA->inherent_static_friction_ + bodyB->inherent_static_friction_) * 0.5f; // ��Ħ��ϵ��
	float df = (bodyA->inherent_dynamic_friction_ + bodyB->inherent_dynamic_friction_) * 0.5f; // ��Ħ��ϵ��

	std::vector<oeVec2> contactList(2, oeVec2(0, 0)); 

	std::vector<oeVec2> frictionImpulseList(contactCount, oeVec2(0, 0)); // Ħ�������б�
	std::vector<float> jList(contactCount, 0.0f); // ������С�б�
	std::vector<oeVec2> impulseList(contactCount, oeVec2(0, 0)); // ���������б�
	std::vector<oeVec2> raList(contactCount, oeVec2(0, 0)); // ��ײ�㵽����A���ĵ������б�
	std::vector<oeVec2> rbList(contactCount, oeVec2(0, 0)); // ��ײ�㵽����B���ĵ������б�

	contactList[0] = contact1;
	contactList[1] = contact2;

	// �������
	for (int i = 0; i < contactCount; ++i) {
		oeVec2 ra = contactList[i] - bodyA->mass_center_; // ��ײ�㵽����A���ĵ�����
		oeVec2 rb = contactList[i] - bodyB->mass_center_; // ��ײ�㵽����B���ĵ�����

		raList[i] = ra;
		rbList[i] = rb;

		oeVec2 raPerp(-ra.y, ra.x); // ra�����ķ�����
		oeVec2 rbPerp(-rb.y, rb.x); // rb�����ķ�����

		oeVec2 angularLinearVelocityA = raPerp * bodyA->GetAngularVelocity(); // ����A�Ľ��ٶȶ�raPerp�Ĺ���
		oeVec2 angularLinearVelocityB = rbPerp * bodyB->GetAngularVelocity(); // ����B�Ľ��ٶȶ�rbPerp�Ĺ���

		oeVec2 relativeVelocity = (bodyB->GetVelocity() + angularLinearVelocityB) - (bodyA->GetVelocity() + angularLinearVelocityA); // ����ٶ�

		float contactVelocityMag = oeVec2::dot(relativeVelocity, normal); // ����ٶ��ڷ��߷����ϵķ���

		if (contactVelocityMag > 0) {
			continue;
		}

		float raPerpDotN = oeVec2::dot(raPerp, normal); // raPerp�����뷨�������ĵ��
		float rbPerpDotN = oeVec2::dot(rbPerp, normal); // rbPerp�����뷨�������ĵ��

		float denom = bodyA->inverse_mass_ + bodyB->inverse_mass_ + (raPerpDotN * raPerpDotN) * bodyA->inverse_rotational_inertia_ + (rbPerpDotN * rbPerpDotN) * bodyB->inverse_rotational_inertia_; // ��������ķ�ĸ

		float j = -(1 + e) * contactVelocityMag / denom; // ������С

		jList[i] = j;
		impulseList[i] = j * normal; // ��������
	}

	// Ӧ�ó���
	for (int i = 0; i < contactCount; ++i) {
		oeVec2 impulse = impulseList[i];
		oeVec2 ra = raList[i];
		oeVec2 rb = rbList[i];
		bodyA->velocity_ += -impulse * bodyA->inverse_mass_;
		bodyA->angular_velocity_ += -oeVec2::cross(ra, impulse) * bodyA->inverse_rotational_inertia_;
		bodyB->velocity_ += impulse * bodyB->inverse_mass_;
		bodyB->angular_velocity_ += oeVec2::cross(rb, impulse) * bodyB->inverse_rotational_inertia_;
		
	}

	// ����Ħ������
	for (int i = 0; i < contactCount; ++i) {
		oeVec2 ra = contactList[i] - bodyA->mass_center_; // ��ײ�㵽����A���ĵ�����
		oeVec2 rb = contactList[i] - bodyB->mass_center_; // ��ײ�㵽����B���ĵ�����

		oeVec2 raPerp(-ra.y, ra.x); // ra�����ķ�����
		oeVec2 rbPerp(-rb.y, rb.x); // rb�����ķ�����

		oeVec2 angularLinearVelocityA = raPerp * bodyA->angular_velocity_; // ����A�Ľ��ٶȶ�raPerp�Ĺ���
		oeVec2 angularLinearVelocityB = rbPerp * bodyB->angular_velocity_; // ����B�Ľ��ٶȶ�rbPerp�Ĺ���

		oeVec2 relativeVelocity = (bodyB->velocity_ + angularLinearVelocityB) - (bodyA->velocity_ + angularLinearVelocityA); // ����ٶ�

		oeVec2 tangent = relativeVelocity - oeVec2::dot(relativeVelocity, normal) * normal; // ������
		if (tangent.LengthSquared() < 1e-6f) { // ����Ƿ�ӽ�������
			continue;
		}
		else {
			tangent.normalize(); // ��һ����������
		}

		float raPerpDotT = oeVec2::dot(raPerp, tangent); // raPerp���������������ĵ��
		float rbPerpDotT = oeVec2::dot(rbPerp, tangent); // rbPerp���������������ĵ��

		float denom = bodyA->inverse_mass_ + bodyB->inverse_mass_ + (raPerpDotT * raPerpDotT) * bodyA->inverse_rotational_inertia_ + (rbPerpDotT * rbPerpDotT) * bodyB->inverse_rotational_inertia_; // ��������ķ�ĸ

		float jt = -oeVec2::dot(relativeVelocity, tangent) / denom; // ���������С
		float j = jList[i]; // ���������С

		if (std::abs(jt) <= j * sf) { // ���ݾ�Ħ��ϵ���ж��Ƿ����㾲Ħ������
			frictionImpulseList[i] = jt * tangent; // ��Ħ������
		}
		else {
			frictionImpulseList[i] = -j * tangent * df; // ��Ħ������
		}
	}

	// Ӧ��Ħ������
	for (int i = 0; i < contactCount; ++i) {
		oeVec2 frictionImpulse = frictionImpulseList[i];
		oeVec2 ra = raList[i];
		oeVec2 rb = rbList[i];
		bodyA->velocity_ += -frictionImpulse * bodyA->inverse_mass_;
		bodyA->angular_velocity_ += -oeVec2::cross(ra, frictionImpulse) * bodyA->inverse_rotational_inertia_;
		bodyB->velocity_ += frictionImpulse * bodyB->inverse_mass_;
		bodyB->angular_velocity_ += oeVec2::cross(rb, frictionImpulse) * bodyB->inverse_rotational_inertia_;
	}
}


