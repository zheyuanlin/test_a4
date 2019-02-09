#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
    const std::vector<std::shared_ptr<Object>> &objects,
    int a_depth) : depth(std::move(a_depth)),
                   num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  int n = objects.size();
  this->left = NULL;
  this->right = NULL;

  if (n == 1)
  {
    this->left = objects[0];
    insert_box_into_box(this->left->box, this->box);
  }
  else if (n == 2)
  {
    this->left = objects[0];
    insert_box_into_box(this->left->box, this->box);
    this->right = objects[1];
    insert_box_into_box(this->right->box, this->box);
  }
  else if (n > 2)
  {
    // use midpoint of AXIS technique in page 285
    for (int i = 0; i < n; i++)
    {
      insert_box_into_box(objects[i]->box, this->box);
    }
    // find AXIS
    int AXIS;
    (this->box.max_corner - this->box.min_corner).maxCoeff(&AXIS);
    // find midpoint
    double m = (box.max_corner(AXIS) + box.min_corner(AXIS)) / 2.0;
    // partition objects into lists surrounding m
    std::vector<std::shared_ptr<Object>> left_of_m, right_of_m;
    for (int j = 0; j < n; j++)
    {
      if (objects[j]->box.center()(AXIS) < m)
      {
        left_of_m.push_back(objects[j]);
      }
      else
      {
        right_of_m.push_back(objects[j]);
      }
    }

    // re-balance if needed
    if (right_of_m.size() == 0)
    {
      right_of_m.push_back(left_of_m.back());
      left_of_m.pop_back();
    }
    else if (left_of_m.size() == 0)
    {
      left_of_m.push_back(right_of_m.back());
      right_of_m.pop_back();
    }

    this->left = std::make_shared<AABBTree>(left_of_m, a_depth + 1);
    this->right = std::make_shared<AABBTree>(right_of_m, a_depth + 1);
  }
}

bool AABBTree::ray_intersect(
    const Ray &ray,
    const double min_t,
    const double max_t,
    double &t,
    std::shared_ptr<Object> &descendant) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////

  // following textbook page 284
  bool intersects_bbox = ray_intersect_box(ray, this->box, min_t, max_t);
  if (intersects_bbox == false)
  {
    return false;
  }
  else
  {
    double lrec, rrec;
    std::shared_ptr<Object> left_desc, right_desc;
    bool left_hit = (this->left != NULL) && (this->left->ray_intersect(ray, min_t, max_t, lrec, left_desc));
    bool right_hit = (this->right != NULL) && (this->right->ray_intersect(ray, min_t, max_t, rrec, right_desc));
    if (left_hit == true && right_hit == true)
    {
      left_desc = (left_desc == NULL) ? this->left : left_desc;
      right_desc = (right_desc == NULL) ? this->right : right_desc;
      if (lrec < rrec)
      {
        t = lrec;
        descendant = left_desc;
        return true;
      }
      else
      {
        t = rrec;
        descendant = right_desc;
        return true;
      }
    }
    else if (left_hit == true)
    {
      left_desc = (left_desc == NULL) ? this->left : left_desc;
      t = lrec;
      descendant = left_desc;
      return true;
    }
    else if (right_hit == true)
    {
      right_desc = (right_desc == NULL) ? this->right : right_desc;
      t = rrec;
      descendant = right_desc;
      return true;
    }
    else
    {
      return false;
    }
    return false;
  }
}
