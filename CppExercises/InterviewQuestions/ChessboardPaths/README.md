Suppose we are given a grid of cells. </br >
On this grid each cell can be indexed by a pair of integers i and j (the i axis points rightwards, while the j axis points upwards). </br >

In this grid we need to move from a point A (ia, ja) to a point B (ib, jb), where ia <= ib and ja <= jb. </br>
Moreover, we cannot move diagonally but only up/down/left/right and we want to travel for the minimum number of steps.

The goal is to compute how many distinct paths exists which cover the minimum distance between A and B.



Solution:

  - We know that the minimum distance between A and B on a grid with no diagonal movements is dist = abs(ib - ia) + abs(jb - ja) </br >
  - Regardless of the path we choose, we need to move </br >
    - dI = abs(ib - ia) steps along the i axis </br >
    - dJ = abs(jb - ja) steps along the j axis </br >

    -> So the total number of distincts paths from A to B can be computed by counting all the possible ways of choosing dI (resp. dJ) steps out of dI + dJ steps without replacement. 
    -> Mathematically: #paths = binomial_coefficient(dI + dJ, dI) = binomial_coefficient(dI + dJ, dJ)