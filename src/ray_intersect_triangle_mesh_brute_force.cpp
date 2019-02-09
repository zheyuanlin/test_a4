#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
    const Ray &ray,
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    const double min_t,
    const double max_t,
    double &hit_t,
    int &hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////

  double closest_hit = max_t + 1.0;
  int triangle_of_closest_hit = -1;
  for (int i = 0; i < F.rows(); i++)
  {
    double test_t;
    bool did_intersect = ray_intersect_triangle(ray, V.row(F(i, 0)),
                                                V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, test_t);
    if (did_intersect)
    {
      if (closest_hit == max_t + 1.0)
      {
        closest_hit = test_t;
        triangle_of_closest_hit = i;
      }
      else
      {
        if (test_t < closest_hit)
        {
          closest_hit = test_t;
          triangle_of_closest_hit = i;
        }
      }
    }
  }
  if (triangle_of_closest_hit != -1 && closest_hit != max_t + 1.0)
  {
    hit_t = closest_hit;
    hit_f = triangle_of_closest_hit;
    return true;
  }

  return false;
}
