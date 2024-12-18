#pragma once
#include <memory>
#include <array>
#include "body.h"
#include <unordered_map>
class Constraint {
public:
    virtual ~Constraint() = default;

    // Ӧ��Լ��
    virtual void Apply(const std::vector<oeBody*>& bodies, float timeStep) = 0;

    // ��ȡԼ���漰�ĸ���
    const std::vector<oeBody*>& GetBodies() const {
        return bodies_;
    }

protected:
    std::vector<oeBody*> bodies_; // �洢Լ���漰�ĸ���
};



class ContactConstraint : public Constraint {
public:
    ContactConstraint(oeBody* bodyA, oeBody* bodyB, const oeVec2& contactPoint, const oeVec2& normal, float bias)
        : bodyA_(bodyA), bodyB_(bodyB), contactPoint_(contactPoint), normal_(normal), bias(bias), accumulatedImpulse(0.0f) {
        rA_ = contactPoint_ - bodyA_->mass_center_;
        rB_ = contactPoint_ - bodyB_->mass_center_;
        bodies_.push_back(bodyA_);
        bodies_.push_back(bodyB_);
    }

    void Apply(const std::vector<oeBody*>& bodies, float timeStep) override {
        WarmStart(); // Ӧ���ۻ�����
       // SolveVelocityConstraints(bodies, timeStep); // ����ٶ�Լ��
        std::cout << 1;
    }

private:
    void WarmStart() {
        // Ӧ���ۻ�����
        oeVec2 warmStartImpulse = normal_ * accumulatedImpulse;
        if (bodyA_->inverse_mass_ > 0.0f) {
            bodyA_->velocity_ -= bodyA_->inverse_mass_ * warmStartImpulse;
            bodyA_->angular_velocity_ -= bodyA_->inverse_rotational_inertia_ * oeVec2::cross(rA_, warmStartImpulse);
        }
        if (bodyB_->inverse_mass_ > 0.0f) {
            bodyB_->velocity_ += bodyB_->inverse_mass_ * warmStartImpulse;
            bodyB_->angular_velocity_ += bodyB_->inverse_rotational_inertia_ * oeVec2::cross(rB_, warmStartImpulse);
        }
    }

    void SolveVelocityConstraints(const std::vector<oeBody*>& bodies, float timeStep) {
        // ��������ٶ�
        oeVec2 relativeVelocity = bodyB_->velocity_ +
            oeVec2(-rB_.y, rB_.x) * bodyB_->angular_velocity_ -
            (bodyA_->velocity_ +
                oeVec2(-rA_.y, rA_.x) * bodyA_->angular_velocity_);

        // �����ٶ��ط��߷���ķ���
        float velocityAlongNormal = oeVec2::dot(relativeVelocity, normal_);

        // �������ٶ��ط��߷���Ϊ����˵���������ڷ��룬����Ҫʩ��Լ��
        if (velocityAlongNormal > 0.0f) return;

        // �����ſɱȾ���
        J = { -normal_.x, -normal_.y, -oeVec2::cross(rA_, normal_),
              normal_.x, normal_.y, oeVec2::cross(rB_, normal_) };

        // ������Ч����
        float effectiveMass = 0.0f;
        if (bodyA_->inverse_mass_ > 0.0f) {
            effectiveMass += J[0] * J[0] * bodyA_->inverse_mass_ +
                J[1] * J[1] * bodyA_->inverse_mass_ +
                J[2] * J[2] * bodyA_->inverse_rotational_inertia_;
        }
        if (bodyB_->inverse_mass_ > 0.0f) {
            effectiveMass += J[3] * J[3] * bodyB_->inverse_mass_ +
                J[4] * J[4] * bodyB_->inverse_mass_ +
                J[5] * J[5] * bodyB_->inverse_rotational_inertia_;
        }

        // �����������ճ���
        lambda = (-velocityAlongNormal - bias) / effectiveMass;

        // �����ۻ�����
        accumulatedImpulse += lambda;

        // Ӧ�ó���
        oeVec2 impulse = normal_ * lambda;
        if (bodyA_->inverse_mass_ > 0.0f) {
            bodyA_->velocity_ -= bodyA_->inverse_mass_ * impulse;
            bodyA_->angular_velocity_ -= bodyA_->inverse_rotational_inertia_ * oeVec2::cross(rA_, impulse);
        }
        if (bodyB_->inverse_mass_ > 0.0f) {
            bodyB_->velocity_ += bodyB_->inverse_mass_ * impulse;
            bodyB_->angular_velocity_ += bodyB_->inverse_rotational_inertia_ * oeVec2::cross(rB_, impulse);
        }
    }

private:
    oeBody* bodyA_;
    oeBody* bodyB_;
    oeVec2 contactPoint_;
    oeVec2 normal_;
    float bias;
    float lambda = 0.0f;
    std::array<float, 6> J{};
    oeVec2 rA_; // ��ײ�㵽����A���ĵ�����
    oeVec2 rB_; // ��ײ�㵽����B���ĵ�����
    float accumulatedImpulse; // �ۻ�����
};


class ConstraintSolver {
public:
    void AddConstraint(std::shared_ptr<Constraint> constraint) {
        constraints_.push_back(constraint);
        for (auto& body : constraint->GetBodies()) {
            bodyToConstraints_[body].push_back(constraint);
        }
    }

    void RemoveConstraint(std::shared_ptr<Constraint> constraint) {
        constraints_.erase(std::remove(constraints_.begin(), constraints_.end(), constraint), constraints_.end());
        for (auto& body : constraint->GetBodies()) {
            auto& bodyConstraints = bodyToConstraints_[body];
            bodyConstraints.erase(std::remove(bodyConstraints.begin(), bodyConstraints.end(), constraint), bodyConstraints.end());
        }
    }

    void ClearConstraints() {
        constraints_.clear();
        bodyToConstraints_.clear();
    }

    void Solve(std::vector<oeBody*>& bodies, float timeStep) {
        for (int i = 0; i < iterations_; ++i) {
            for (auto& body : bodies) {
                for (auto& constraint : bodyToConstraints_[body]) {
                    constraint->Apply(bodies, timeStep);
                }
            }
        }
    }

    void SetIterations(int iterations) {
        iterations_ = iterations;
    }

private:
    std::vector<std::shared_ptr<Constraint>> constraints_;
    int iterations_ = 10; // Ĭ�ϵ�������
    std::unordered_map<oeBody*, std::vector<std::shared_ptr<Constraint>>> bodyToConstraints_; // ���嵽Լ����ӳ��
};