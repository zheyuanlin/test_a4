#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>

void find_all_intersecting_pairs_using_AABBTrees(
    const std::shared_ptr<AABBTree> &rootA,
    const std::shared_ptr<AABBTree> &rootB,
    std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> &
        leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  std::list<std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>>> Q;
  if (box_box_intersect(rootA->box, rootB->box))
  {
    Q.emplace_back(rootA, rootB);
  }
  while (!Q.empty())
  {
    std::shared_ptr<AABBTree> node_A = Q.front().first;
    std::shared_ptr<AABBTree> node_B = Q.front().second;
    Q.pop_front();

    if (node_A->num_leaves < 3 && node_B->num_leaves < 3)
    {
      // both A and B are leaves

      if (node_A->left && node_B->left)
      {
        if (box_box_intersect(node_A->left->box, node_B->left->box))
        {
          leaf_pairs.emplace_back(node_A->left, node_B->left);
        }
      }
      if (node_A->right && node_B->left)
      {
        if (box_box_intersect(node_A->right->box, node_B->left->box))
        {
          leaf_pairs.emplace_back(node_A->right, node_B->left);
        }
      }
      if (node_A->left && node_B->right)
      {
        if (box_box_intersect(node_A->left->box, node_B->right->box))
        {
          leaf_pairs.emplace_back(node_A->left, node_B->right);
        }
      }
      if (node_A->right && node_B->right)
      {
        if (box_box_intersect(node_A->right->box, node_B->right->box))
        {
          leaf_pairs.emplace_back(node_A->right, node_B->right);
        }
      }
    }
    else if (node_A->num_leaves < 3)
    {
      // A is a leaf
      if (box_box_intersect(node_A->box, node_B->left->box))
      {
        Q.emplace_back(node_A, std::static_pointer_cast<AABBTree>(node_B->left));
      }
      if (box_box_intersect(node_A->box, node_B->right->box))
      {
        Q.emplace_back(node_A, std::static_pointer_cast<AABBTree>(node_B->right));
      }
    }
    else if (node_B->num_leaves < 3)
    {
      // B is a leaf
      if (box_box_intersect(node_A->left->box, node_B->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->left), node_B);
      }
      if (box_box_intersect(node_A->right->box, node_B->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->right), node_B);
      }
    }
    else
    {
      if (box_box_intersect(node_A->left->box, node_B->left->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->left), std::static_pointer_cast<AABBTree>(node_B->left));
      }
      if (box_box_intersect(node_A->right->box, node_B->left->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->right), std::static_pointer_cast<AABBTree>(node_B->left));
      }
      if (box_box_intersect(node_A->left->box, node_B->right->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->left), std::static_pointer_cast<AABBTree>(node_B->right));
      }
      if (box_box_intersect(node_A->right->box, node_B->right->box))
      {
        Q.emplace_back(std::static_pointer_cast<AABBTree>(node_A->right), std::static_pointer_cast<AABBTree>(node_B->right));
      }
    }
  }
}
