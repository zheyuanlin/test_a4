#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
    const Ray &ray,
    const BoundingBox &box,
    const double min_t,
    const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  // Using textbook page 282

  // reciprocals
  double a = 1 / ray.direction(0);
  double b = 1 / ray.direction(1);
  double c = 1 / ray.direction(2);

  double tmin_x, tmax_x, tmin_y, tmax_y, tmin_z, tmax_z, tmin_overall, tmax_overall;
  // x
  if (a >= 0)
  {
    tmin_x = a * (box.min_corner(0) - ray.origin(0));
    tmax_x = a * (box.max_corner(0) - ray.origin(0));
  }
  else
  {
    tmin_x = a * (box.max_corner(0) - ray.origin(0));
    tmax_x = a * (box.min_corner(0) - ray.origin(0));
  }
  // y
  if (b >= 0)
  {
    tmin_y = b * (box.min_corner(1) - ray.origin(1));
    tmax_y = b * (box.max_corner(1) - ray.origin(1));
  }
  else
  {
    tmin_y = b * (box.max_corner(1) - ray.origin(1));
    tmax_y = b * (box.min_corner(1) - ray.origin(1));
  }
  // z
  if (c >= 0)
  {
    tmin_z = c * (box.min_corner(2) - ray.origin(2));
    tmax_z = c * (box.max_corner(2) - ray.origin(2));
  }
  else
  {
    tmin_z = c * (box.max_corner(2) - ray.origin(2));
    tmax_z = c * (box.min_corner(2) - ray.origin(2));
  }

  tmin_overall = fmax(tmin_x, fmax(tmin_y, tmin_z));
  tmax_overall = fmin(tmax_x, fmin(tmax_y, tmax_z));
  if (tmin_overall > tmax_overall)
    return false;
  tmin_overall = fmax(tmin_overall, min_t);
  tmax_overall = fmin(tmax_overall, max_t);
  if (tmin_overall > tmax_overall)
    return false;

  return true;
}
