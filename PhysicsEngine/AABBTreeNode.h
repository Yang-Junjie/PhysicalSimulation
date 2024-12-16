#pragma once
#include "body.h"


struct AABBTreeNode {
    oeAABB aabb;
    int body_id; // -1 for internal nodes, valid ID for leaf nodes
    AABBTreeNode* left = nullptr;
    AABBTreeNode* right = nullptr;
    AABBTreeNode* parent = nullptr; // ���parentָ��

    AABBTreeNode(const oeAABB& aabb, int body_id) : aabb(aabb), body_id(body_id), left(nullptr), right(nullptr), parent(nullptr) {}

    // �����������ϲ�����AABB
    void Merge(const AABBTreeNode* other) {
        this->aabb.min.x = std::min(this->aabb.min.x, other->aabb.min.x);
        this->aabb.min.y = std::min(this->aabb.min.y, other->aabb.min.y);
        this->aabb.max.x = std::max(this->aabb.max.x, other->aabb.max.x);
        this->aabb.max.y = std::max(this->aabb.max.y, other->aabb.max.y);
    }

    // ��������������ڵ�����
    float Area() const {
        return (aabb.max.x - aabb.min.x) * (aabb.max.y - aabb.min.y);
    }
};