**Problem**: Maximum Binary Tree  
Given an input array of values, create and display a tree with the following rules
   - The root is the maximum nunber in the array
   - The left subtree is the maximum tree constructed from the sub-array on the left of the maximum value
   - The right subtree is the maximum tree constructed from the sub-array on the right of the maximum value

> e.g. Array = [0, -1, 5, 3, 9, 2, 6]  
> Output:  
>
>             9  
>         /       \
>        5         6
>      /   \      /
>     0     3    2
>      \
>       -1

**Note**: The tree need not to be displayed vertically