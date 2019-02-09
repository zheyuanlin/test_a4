#include "point_box_squared_distance.h"

double point_box_squared_distance(
    const Eigen::RowVector3d &query,
    const BoundingBox &box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  ////////////////////////////////////////////////////////////////////////////
  double x1 = box.min_corner(0) - query(0);
  double x2 = query(0) - box.max_corner(0);
  double x_distance = (x1 < x2) ? x2 : x1;

  double y1 = box.min_corner(1) - query(1);
  double y2 = query(1) - box.max_corner(1);
  double y_distance = (y1 < y2) ? y2 : y1;

  double z1 = box.min_corner(2) - query(2);
  double z2 = query(2) - box.max_corner(2);
  double z_distance = (z1 < z2) ? z2 : z1;

  if (x_distance < 0)
  {
    x_distance = 0;
  }
  if (y_distance < 0)
  {
    y_distance = 0;
  }
  if (z_distance < 0)
  {
    z_distance = 0;
  }

  // return the squared total
  return x_distance * x_distance + y_distance * y_distance + z_distance * z_distance;
}
