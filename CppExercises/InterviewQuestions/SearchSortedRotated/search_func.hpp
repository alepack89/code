#ifndef _SEARCH_ROTATED_ARRAY_FUNCS_H
#define _SEARCH_ROTATED_ARRAY_FUNCS_H

//Include standard libraries
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>



//Template function used to retrieve array size at compile time
template<typename T, int N>
constexpr int size(T (&)[N])
{
  return N;
}

//Recursive search function
//Returns the index of the key inside the array (if present), -1 otherwise
template<typename T>
int findKeyInArray(const T* inArray, int lft, int rgt, T key)
{
  //Check if interval is valid
  if (lft > rgt)
    return -1;

  //Compute midpoint and check if the key can be found at that location
  int mid = (lft + rgt) / 2;
  if (inArray[mid] == key)
    return mid;

  //Check if left side of the array is sorted
  if ((mid > lft) && (inArray[lft] <= inArray[mid-1]))
  {
    //Check if the requested key is within this range
    if ((key >= inArray[lft]) && (key <= inArray[mid-1]))
      return findKeyInArray(inArray, lft, mid-1, key);

    //Search the right side
    return findKeyInArray(inArray, mid+1, rgt, key);
  }

  //So the right side must be sorted
  if ((key >= inArray[mid+1]) && (key <= inArray[rgt]))
    return findKeyInArray(inArray, mid+1, rgt, key);

  //Search the left side
  return findKeyInArray(inArray, lft, mid-1, key);
}

//We can do the same thing using pointers
//Recursive search function
//Returns a pointer to the key inside the array (if present), nullptr otherwise
//Note: end points to the past-the-end element in the input container
template<typename T>
T* findKeyInArrayPtr(T* begin, T* end, T key)
{
  //Check if interval is valid
  if (    (begin == nullptr) 
       || (end   == nullptr) 
       || (begin >= end)     ) 
    return nullptr;

  //Compute midpoint and check if the key can be found at that location
  T* mid = begin + ((end - begin) / 2);
  if (*mid == key)
    return mid;

  T* midPrev = mid - 1;
  T* midNext = mid + 1;

  //Check if left side of the array is sorted
  if ((mid > begin) && (*begin <= *midPrev))
  {
    //Check if the requested key is within this range
    if ((key >= *begin) && (key <= *midPrev))
      return findKeyInArrayPtr(begin, mid, key);

    //Search the right side
    return findKeyInArrayPtr(midNext, end, key);
  }

  //So the right side must be sorted
  if ((key >= *midNext) && (key <= *end))
    return findKeyInArrayPtr(midNext, end, key);

  //Search the left side
  return findKeyInArrayPtr(begin, mid, key);
}

//Or we can do it >= C++11 style using iterators
//Recursive search function
//Returns an iterator to the key inside the container (if present), end() otherwise
//Note: end points to the past-the-end element in the input container
template<typename IterType>
IterType findKeyInArrayIter(IterType begin, IterType end, typename std::iterator_traits<IterType>::value_type key)
{
  //Initially store the end iterator as a "Not found" marker
  static const IterType NotFoundIter = end;

  //Check if input range is valid
  if (begin >= end)
    return NotFoundIter;

  //Compute midpoint and check if the key can be found at that location
  typename std::iterator_traits<IterType>::difference_type len = std::distance(begin, end);
  IterType mid = std::next(begin, len / 2);
  if (*mid == key)
    return mid;

  IterType midPrev = std::prev(mid);
  IterType midNext = std::next(mid);

  //Check if the left side of the array is sorted
  if ((std::distance(begin, mid) > 0) && (*begin < *midPrev))
  {
    //Check if the requested key is within this range
    if ((key >= *begin) && (key <= *midPrev))
      return findKeyInArrayIter(begin, mid, key);

    //Search the right side
    return findKeyInArrayIter(midNext, end, key);
  }

  //So the right side must be sorted
  if ((key >= *midNext) && (key <= *end))
    return findKeyInArrayIter(midNext, end, key);

  //Search the left side
  return findKeyInArrayIter(begin, mid, key);
}

#endif