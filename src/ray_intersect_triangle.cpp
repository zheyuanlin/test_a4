#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
    const Ray &ray,
    const Eigen::RowVector3d &A,
    const Eigen::RowVector3d &B,
    const Eigen::RowVector3d &C,
    const double min_t,
    const double max_t,
    double &t)
{
  // from a2
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////

  // Using https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
  // to determine intersection
  Eigen::Vector3d At(A(0), A(1), A(2));
  Eigen::Vector3d Bt(B(0), B(1), B(2));
  Eigen::Vector3d Ct(C(0), C(1), C(2));

  Eigen::Vector3d t1 = Bt - At;
  Eigen::Vector3d t2 = Ct - At;
  Eigen::Vector3d h = ray.direction.cross(t2);
  double a = t1.dot(h);

  if (a > -0.0000001 && a < 0.0000001)
  {
    return false;
  }

  double f = 1.0 / a;

  Eigen::Vector3d s = ray.origin - At;
  double u = f * (s.dot(h));
  if (u < 0 || u > 1)
  {
    return false;
  }

  Eigen::Vector3d q = s.cross(t1);
  double v = f * ray.direction.dot(q);
  if (v < 0 || u + v > 1)
  {
    return false;
  }

  double t_ = f * t2.dot(q);
  if (t_ >= 0.0000001)
  {
    t = t_;
    return true;
  }
  return false;
}
