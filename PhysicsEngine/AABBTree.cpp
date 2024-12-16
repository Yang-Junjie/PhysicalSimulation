// AABBTree.cpp
#include "AABBTree.h"
#include <limits>
#include <algorithm>
#include "collision.h"

void AABBTree::Insert(const oeAABB& aabb, int id) {
    if (root_ == nullptr) {
        root_ = new AABBTreeNode(aabb, id);
        return;
    }

    root_ = InsertRecursive(root_, aabb, id);
}

AABBTreeNode* AABBTree::InsertRecursive(AABBTreeNode* node, const oeAABB& aabb, int id) {
    if (node == nullptr) {
        return new AABBTreeNode(aabb, id);
    }

    // ѡ����뵽��������������
    if (aabb.min.x < node->aabb.min.x || (aabb.min.x == node->aabb.min.x && aabb.min.y < node->aabb.min.y)) {
        node->left = InsertRecursive(node->left, aabb, id);
    }
    else {
        node->right = InsertRecursive(node->right, aabb, id);
    }

    // ���µ�ǰ�ڵ��AABB
    node->aabb = MergeAABB(node->aabb, aabb);

    return node;
}

void AABBTree::Remove(int id) {
    if (root_ == nullptr) {
        return;
    }

    root_ = RemoveRecursive(root_, id);
}

AABBTreeNode* AABBTree::RemoveRecursive(AABBTreeNode* node, int id) {
    if (node == nullptr) {
        return nullptr;
    }

    if (id == node->body_id) {
        // �ҵ�Ŀ��ڵ㣬�Ƴ���
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            AABBTreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            AABBTreeNode* temp = node->left;
            delete node;
            return temp;
        }
        else {
            // �ҵ�����������С�Ľڵ���Ϊ���
            AABBTreeNode* min_node = node->right;
            while (min_node->left != nullptr) {
                min_node = min_node->left;
            }
            node->aabb = min_node->aabb;
            node->body_id = min_node->body_id;
            node->right = RemoveRecursive(node->right, min_node->body_id);
        }
    }
    else if (id < node->body_id) {
        node->left = RemoveRecursive(node->left, id);
    }
    else {
        node->right = RemoveRecursive(node->right, id);
    }

    // ���µ�ǰ�ڵ��AABB
    if (node->left == nullptr && node->right == nullptr) {
        node->aabb = node->aabb;
    }
    else if (node->left == nullptr) {
        node->aabb = MergeAABB(node->aabb, node->right->aabb);
    }
    else if (node->right == nullptr) {
        node->aabb = MergeAABB(node->aabb, node->left->aabb);
    }
    else {
        node->aabb = MergeAABB(node->left->aabb, node->right->aabb);
    }

    return node;
}

void AABBTree::Query(const oeAABB& aabb, std::vector<int>& potential_contacts) {
    if (root_ == nullptr) {
        return;
    }

    QueryRecursive(root_, aabb, potential_contacts);
}

void AABBTree::QueryRecursive(const AABBTreeNode* node, const oeAABB& aabb, std::vector<int>& potential_contacts) {
    if (node == nullptr) {
        return;
    }

    // ��鵱ǰ�ڵ��AABB�Ƿ����ѯ��AABB�ཻ
    if (Intersect::IntersectAABB(node->aabb, aabb)) {
        // �����Ҷ�ӽڵ㣬�������ID
        if (node->left == nullptr && node->right == nullptr) {
            potential_contacts.push_back(node->body_id);
        } else {
            // �ݹ��ѯ��������
            QueryRecursive(node->left, aabb, potential_contacts);
            QueryRecursive(node->right, aabb, potential_contacts);
        }
    }
}


oeAABB AABBTree::MergeAABB(const oeAABB& aabb1, const oeAABB& aabb2) {
    oeAABB merged_aabb;
    merged_aabb.min.x = std::min(aabb1.min.x, aabb2.min.x);
    merged_aabb.max.x = std::max(aabb1.max.x, aabb2.max.x);
    merged_aabb.min.y = std::min(aabb1.min.y, aabb2.min.y);
    merged_aabb.max.y = std::max(aabb1.max.y, aabb2.max.y);
    return merged_aabb;
}