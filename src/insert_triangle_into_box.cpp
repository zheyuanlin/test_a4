#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
    const Eigen::RowVector3d &a,
    const Eigen::RowVector3d &b,
    const Eigen::RowVector3d &c,
    BoundingBox &B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 3; i++)
  {
    double max_coordinate = fmax(a(i), fmax(b(i), c(i)));
    double min_coordinate = fmin(a(i), fmin(b(i), c(i)));
    if (B.max_corner(i) < max_coordinate)
    {
      B.max_corner(i) = max_coordinate;
    }
    if (B.min_corner(i) > min_coordinate)
    {
      B.min_corner(i) = min_coordinate;
    }
  }
}
