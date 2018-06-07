/*
* First code on the repository
* It should be a hello world program
*/

//Include standard library
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

//Import everything from standard namespace
using namespace std;

//Main method
int main(int argc, char* argv[])
{
  //Print hello world 
  vector<string> words = {"Hello", " ", "World", "\n"};

  for (auto& word : words)
    cout << word;

  //Program exited normally
  return 0;
}