#pragma once
#include <utility> // For std::pair
#include <cmath>   // For std::cos and std::sin
#include <iostream>

const float VerySmallAmount = 0.0000000000005f;

struct FlatTransform
{
    float cos;          // Cosine of the rotation angle
    float sin;          // Sine of the rotation angle
    float positionX;    // Translation along the X-axis
    float positionY;    // Translation along the Y-axis
};

struct oeVec2
{
    float x;
    float y;
    oeVec2() :x(0.0f), y(0.0f) {};
    oeVec2(float x, float y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const oeVec2& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os; // ����������Ա���ʽ����  
    }
    // �������
    oeVec2 operator+(const oeVec2& other) const
    {
        return { this->x + other.x, this->y + other.y };
    }

    // �������
    oeVec2 operator-(const oeVec2& other) const
    {
        return { this->x - other.x, this->y - other.y };
    }

    // ����ȡ����
    oeVec2 operator-() const
    {
        return { -this->x, -this->y };
    }

    // ����������
    oeVec2 operator*(float scalar) const
    {
        return { this->x * scalar, this->y * scalar };
    }

    // ����������
    friend oeVec2 operator*(float scalar, const oeVec2& vec)
    {
        return vec * scalar;
    }

    // ����������
    oeVec2 operator/(float scalar) const
    {
        return { this->x / scalar, this->y / scalar };
    }

    oeVec2& operator+=(const oeVec2& other) {
        this->x += other.x; // ����һ�������ֵ�ӵ���ǰ������
        this->y += other.y;
        return *this; // ���ص�ǰ���������
    }

    oeVec2& operator-=(const oeVec2& other) {
        this->x -= other.x; // ����һ�������ֵ�ӵ���ǰ������
        this->y -= other.y;
        return *this; // ���ص�ǰ���������
    }
    oeVec2& operator*=(const oeVec2& other) {
        this->x *= other.x; // ����һ�������ֵ�ӵ���ǰ������
        this->y *= other.y;
        return *this; // ���ص�ǰ���������
    }

    oeVec2& operator/=(const oeVec2& other) {
        this->x /= other.x; // ����һ�������ֵ�ӵ���ǰ������
        this->y /= other.y;
        return *this; // ���ص�ǰ���������
    }

    // ������ת
    static inline void Transform(float& x, float& y, const float radian)
    {
        float cos_angle = static_cast<float>(std::cos(radian));
        float sin_angle = static_cast<float>(std::sin(radian));
        float temp_x = cos_angle * x - sin_angle * y;
        y = sin_angle * x + cos_angle * y;
        x = temp_x;
    }

    static inline float AngleToRadian(float angle) {
        return static_cast<float>(angle * M_PI / 180.0f);
    }
    // �ж����������Ƿ����
    bool operator==(const oeVec2& other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    // �ж����������Ƿ����
    bool operator!=(const oeVec2& other) const
    {
        return !(*this == other);
    }

    // �ж����������Ƿ����
    bool equals(const oeVec2& other) const
    {
        return *this == other;
    }

    //����ȡģ
    float  len() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    //����ȡģ
    static inline float len(oeVec2& v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    //������һ��
    void normalize() {
        float length = sqrt(this->x * this->x + this->y * this->y);
        if (length > VerySmallAmount) {
            this->x /= length;
            this->y /= length;
        }
        else {
            this->x = 0.0f;
            this->y = 0.0f;
        }
    }

    //������һ��
    static oeVec2 normalize(oeVec2 v) {
        float length = oeVec2::len(v);
        if (length > VerySmallAmount) {
            v.x /= length;
            v.y /= length;
        }
        else {
            v.x = 0.0f;
            v.y = 0.0f;
        }
        return v;
    }

    //�����ĵ��
    float dot(const oeVec2& v) const {
        return this->x * v.x + this->y * v.y;
    }

    //�����ĵ��
    static inline float dot(const oeVec2& v1, const oeVec2& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    //�����Ĳ��
    float cross(const oeVec2& v) const {
        return this->x * v.y - this->y * v.x;
    }

    static inline float cross(const oeVec2& v1, const oeVec2& v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    //������ģ��ƽ��
    float LengthSquared() const {
        return this->x * this->x + this->y * this->y;
    }

    //������ģ��ƽ��
    static inline float LengthSquared(const oeVec2& v) {
        return v.x * v.x + v.y * v.y;
    }

    //���������ľ���
    static inline float Distance(const oeVec2 v1, const oeVec2 v2) {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        return sqrt(dx * dx + dy * dy);
    }

    //�������������ƽ��
    static inline float DistanceSquared(const oeVec2 v1, const oeVec2 v2) {
        return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
    }

    //�ǳ�С�ж�
    static inline bool NearlyEqualFv(const oeVec2 a, const oeVec2 b) {
        return oeVec2::DistanceSquared(a, b) < VerySmallAmount * VerySmallAmount;
    }

    //�ǳ�С�ж�
    static inline bool NearlyEqual(const float a, const float b) {
        return std::abs(a - b) < VerySmallAmount * VerySmallAmount;
    }
};