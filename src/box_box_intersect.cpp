#include "box_box_intersect.h"
bool box_box_intersect(
    const BoundingBox &A,
    const BoundingBox &B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  bool amin_bmax = (A.min_corner(0) < B.max_corner(0));
  amin_bmax = amin_bmax && (A.min_corner(1) < B.max_corner(1));
  amin_bmax = amin_bmax && (A.min_corner(2) < B.max_corner(2));

  bool bmin_amax = (B.min_corner(0) < A.max_corner(0));
  bmin_amax = bmin_amax && (B.min_corner(1) < A.max_corner(1));
  bmin_amax = bmin_amax && (B.min_corner(2) < A.max_corner(2));

  return amin_bmax && bmin_amax;
}
