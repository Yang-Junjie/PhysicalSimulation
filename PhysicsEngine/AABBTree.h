// AABBTree.h
#pragma once
#include <vector>
#include "AABBTreeNode.h"
#include "body.h"
class AABBTree {
public:
    // ����һ���µ����嵽����
    void Insert(const oeAABB& aabb, int id);

    // �������Ƴ�һ������
    void Remove(int id);

    // ��ѯ�����AABB�ཻ����������ID
    void Query(const oeAABB& aabb, std::vector<int>& potential_contacts);

    // ����ƽ��������ѡ��
  //  void Rebalance();

private:
    AABBTreeNode* root_ = nullptr;  // ���ĸ��ڵ�

    // �����������ݹ����ڵ�
    AABBTreeNode* InsertRecursive(AABBTreeNode* node, const oeAABB& aabb, int id);

    // �����������ݹ��Ƴ��ڵ�
    AABBTreeNode* RemoveRecursive(AABBTreeNode* node, int id);

    // �����������ݹ��ѯ
    void QueryRecursive(const AABBTreeNode* node, const oeAABB& aabb, std::vector<int>& potential_contacts);

    // ������������������AABB�ĺϲ�AABB
    oeAABB MergeAABB(const oeAABB& aabb1, const oeAABB& aabb2);
};