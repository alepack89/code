/*
* Find the requested element inside an integer array 
* which has been sorted and rotated
* 
* Example:
*   array = {10, 12, 13, 15, 19, 32, 1, 4, 7, 9}
*   key   = 13
*
*   return = 2
*/

//Inlclude search functions
#include "search_func.hpp"

//Include everything from std namespace
using namespace std;

//Define data type to be used
using DType = double;

//Define string to key conversion function
auto parseKeyFromString = [](const string& keyStr) -> DType { return atof(keyStr.c_str()); };

//Main methods
int main(int argc, char* argv[])
{
  //Define input array (it works with vectors too)
  DType inArray[] = {10.0, 12.25, 13.7, 15.45, 19.12, 32.0, 1.12, 4.23, 7.41, 9.12};

  //Define the query key
  DType queryKey = (argc > 1) ? parseKeyFromString(argv[1]) : 4.0;
  cout << "Key to search for = " << queryKey << endl;

  //Search for the query key using pointers
  DType* keyPtr = findKeyInArrayPtr(begin(inArray), end(inArray), queryKey);

  if (keyPtr == nullptr)
    cout << "Cannot find query key inside the input array" << endl;
  else
    cout << "Query key found at index " << (keyPtr - &inArray[0]) << endl;

  //Or using C++11 code style and iterators
  auto keyIter = findKeyInArrayIter(begin(inArray), end(inArray), queryKey);

  if (keyIter == end(inArray))
    cout << "Cannot find query key inside the input array" << endl;
  else
    cout << "Query key found at index " << std::distance(begin(inArray), keyIter) << endl;


  //Program exited normally
  return 0;
}