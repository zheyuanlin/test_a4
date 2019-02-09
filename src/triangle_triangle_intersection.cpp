#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
    const Eigen::RowVector3d &A0,
    const Eigen::RowVector3d &A1,
    const Eigen::RowVector3d &A2,
    const Eigen::RowVector3d &B0,
    const Eigen::RowVector3d &B1,
    const Eigen::RowVector3d &B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  double t_;
  Ray r_A0 = Ray(A0, A1 - A0);
  Ray r_A1 = Ray(A1, A2 - A1);
  Ray r_A2 = Ray(A2, A0 - A2);
  Ray r_B0 = Ray(B0, B1 - B0);
  Ray r_B1 = Ray(B1, B2 - B1);
  Ray r_B2 = Ray(B2, B0 - B2);
  bool test_A0 = ray_intersect_triangle(r_A0, B0, B1, B2, 0, 1, t_);
  bool test_A1 = ray_intersect_triangle(r_A1, B0, B1, B2, 0, 1, t_);
  bool test_A2 = ray_intersect_triangle(r_A2, B0, B1, B2, 0, 1, t_);
  bool test_B0 = ray_intersect_triangle(r_B0, A0, A1, A2, 0, 1, t_);
  bool test_B1 = ray_intersect_triangle(r_B1, A0, A1, A2, 0, 1, t_);
  bool test_B2 = ray_intersect_triangle(r_B2, A0, A1, A2, 0, 1, t_);

  // if none of the tests pass, return false
  if (!test_A0 && !test_A1 && !test_A2 && !test_B0 && !test_B1 && !test_B2)
  {
    return false;
  }
  else
  {
    return true;
  }
}
