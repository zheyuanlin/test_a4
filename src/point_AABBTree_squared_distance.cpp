#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

// custom comparator for pq
bool Compare(std::pair<std::shared_ptr<AABBTree>, double> a, std::pair<std::shared_ptr<AABBTree>, double> b)
{
  return a.second > b.second;
}

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d &query,
    const std::shared_ptr<AABBTree> &root,
    const double min_sqrd,
    const double max_sqrd,
    double &sqrd,
    std::shared_ptr<Object> &descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  ////////////////////////////////////////////////////////////////////////////
  std::priority_queue<std::pair<std::shared_ptr<AABBTree>, double>,
                      std::vector<std::pair<std::shared_ptr<AABBTree>, double>>,
                      std::function<bool(std::pair<std::shared_ptr<AABBTree>,
                                                   double>,
                                         std::pair<std::shared_ptr<AABBTree>,
                                                   double>)>>
      pq(Compare);

  sqrd = std::numeric_limits<double>::infinity();
  pq.emplace(root, point_box_squared_distance(query, root->box));

  while (!pq.empty())
  {
    std::shared_ptr<AABBTree> curr = pq.top().first;
    double d_s = pq.top().second;
    pq.pop();

    if (d_s < sqrd)
    {

      if (curr->num_leaves < 3)
      {
        double left_sqrd, right_sqrd;
        std::shared_ptr<Object> curr_descendant;
        // look at left and right child, update sqrd if needed
        if (curr->left != NULL)
        {
          if (curr->left->point_squared_distance(query, min_sqrd, max_sqrd, left_sqrd, curr_descendant))
          {
            if (left_sqrd < sqrd)
            {
              sqrd = left_sqrd;
              descendant = curr->left;
            }
          }
        }
        if (curr->right != NULL)
        {
          if (curr->right->point_squared_distance(query, min_sqrd, max_sqrd, right_sqrd, curr_descendant))
          {
            if (right_sqrd < sqrd)
            {
              sqrd = right_sqrd;
              descendant = curr->right;
            }
          }
        }
      }

      // curr is not a leaf
      else
      {
        pq.emplace(std::static_pointer_cast<AABBTree>(curr->left), point_box_squared_distance(query, curr->left->box));
        pq.emplace(std::static_pointer_cast<AABBTree>(curr->right), point_box_squared_distance(query, curr->right->box));
      }
    }
  }
  return descendant != NULL;
}