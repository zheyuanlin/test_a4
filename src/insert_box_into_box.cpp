#include "insert_box_into_box.h"

void insert_box_into_box(
    const BoundingBox &A,
    BoundingBox &B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 3; i++)
  {
    // increase B to include A
    if (B.max_corner(i) < A.max_corner(i))
    {
      B.max_corner(i) = A.max_corner(i);
    }
    if (B.min_corner(i) > A.min_corner(i))
    {
      B.min_corner(i) = A.min_corner(i);
    }
  }
}
