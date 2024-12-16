#include <vector>
#include <memory>
#include <array>

// ���� Constraint
class Constraint {
public:
    virtual ~Constraint() = default;
    virtual void Apply(oeBody& bodyA, oeBody& bodyB, float timeStep) = 0;
};

// ����� ContactConstraint ��
class ContactConstraint : public Constraint {
public:
    // ���캯����������Ա����ʡ��...

    void Apply(oeBody& bodyA, oeBody& bodyB, float timeStep) override {
        // �������λ������
        oeVec2 rA = contactPoint_ - bodyA.mass_center_;
        oeVec2 rB = contactPoint_ - bodyB.mass_center_;

        // ��������ٶ�
        oeVec2 relativeVelocity = bodyB.velocity_ +
            oeVec2(-rB.y, rB.x) * bodyB.angular_velocity_ -
            (bodyA.velocity_ +
                oeVec2(-rA.y, rA.x) * bodyA.angular_velocity_);

        // �����ٶ�Լ��
        float velocityAlongNormal = oeVec2::dot(relativeVelocity, normal_);

        // �������ٶ��ط��߷���Ϊ����˵���������ڷ��룬����Ҫʩ��Լ��
        if (velocityAlongNormal > 0.0f) return;

        // �����ſɱȾ���
        J = { -normal_.x, -normal_.y, -oeVec2::cross(rA, normal_),
              normal_.x, normal_.y, oeVec2::cross(rB, normal_) };

        // ������Ч����
        float effectiveMass = 0.0f;
        if (bodyA.inverse_mass_ > 0.0f) {
            effectiveMass += J[0] * J[0] * bodyA.inverse_mass_ +
                J[1] * J[1] * bodyA.inverse_mass_ +
                J[2] * J[2] * bodyA.inverse_rotational_inertia_;
        }
        if (bodyB.inverse_mass_ > 0.0f) {
            effectiveMass += J[3] * J[3] * bodyB.inverse_mass_ +
                J[4] * J[4] * bodyB.inverse_mass_ +
                J[5] * J[5] * bodyB.inverse_rotational_inertia_;
        }

        // �����������ճ���
        lambda = (-velocityAlongNormal - bias) / effectiveMass;

        // Ӧ�ó���
        oeVec2 impulse = normal_ * lambda;
        if (bodyA.inverse_mass_ > 0.0f) {
            bodyA.velocity_ -= bodyA.inverse_mass_ * impulse;
            bodyA.angular_velocity_ -= bodyA.inverse_rotational_inertia_ * oeVec2::cross(rA, impulse);
        }
        if (bodyB.inverse_mass_ > 0.0f) {
            bodyB.velocity_ += bodyB.inverse_mass_ * impulse;
            bodyB.angular_velocity_ += bodyB.inverse_rotational_inertia_ * oeVec2::cross(rB, impulse);
        }
    }

private:
    oeBody* bodyA_;
    oeBody* bodyB_;
    oeVec2 contactPoint_;
    oeVec2 normal_;
    float bias;
    float lambda;
    std::array<float, 6> J;
};

// Լ���������
class ConstraintSolver {
public:
    void AddConstraint(std::shared_ptr<Constraint> constraint) {
        constraints_.push_back(constraint);
    }

    void Solve(std::vector<oeBody*>& bodies, float timeStep) {
        for (int i = 0; i < iterations_; ++i) {
            for (auto& constraint : constraints_) {
                // ֱ�ӵ���Լ���� Apply ��������������ת��
                constraint->Apply(*bodies[0], *bodies[1], timeStep); // �������ÿ��Լ��ֻ�漰��������
            }
        }
    }

    void SetIterations(int iterations) {
        iterations_ = iterations;
    }

private:
    std::vector<std::shared_ptr<Constraint>> constraints_;
    int iterations_ = 10; // Ĭ�ϵ�������
};