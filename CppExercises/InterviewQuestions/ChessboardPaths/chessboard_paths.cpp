//Implements two possible solutions for the 
//chessboard paths finding problem described in the readme file

//Include standard library
#include <cstdlib>
#include <iostream>

//Start and final point
#define START_I 2
#define START_J 5
#define END_I   7
#define END_J   9

//Import everything from std namespace
using namespace std;

//Useful type definitions
using CountType = unsigned int;

//Function used to implement recursive solution
CountType getPathCountRec(int startI, int startJ, int endI, int endJ)
{
  //Edge case: we are on the same col/row as the final point
  //We have only one way to reach it in this case (i.e. moving straight along the col/row)
  if ((startI == endI) || (startJ == endJ))
    return 1;

  //Otherwise we apply recursion 
  CountType stepAlongI = (endI >= startI) ? getPathCountRec(startI + 1,     startJ, endI, endJ) : getPathCountRec(startI - 1,     startJ, endI, endJ);
  CountType stepAlongJ = (endJ >= startJ) ? getPathCountRec(    startI, startJ + 1, endI, endJ) : getPathCountRec(    startI, startJ - 1, endI, endJ);

  return (stepAlongI + stepAlongJ);
}

//Function used to implement binomial coefficients solution
CountType getPathCountBinom(int startI, int startJ, int endI, int endJ)
{
  //Compute distances along the i and j axes
  int dI = abs(endI - startI);
  int dJ = abs(endJ - startJ);

  //Compute binomial coefficient
  CountType num = 1, den = 1;
  int k = min(dI, dJ);
  int n = dI + dJ;

  for (int i = 0; i < k; i++)
  {
    num *= (n - i);
    den *= (k - i);
  }

  return (num / den);
}

//Main method
int main(int argc, char* argv[])
{
  //Compute number of paths using recursive method
  cout << "Paths using recursion      = " <<   getPathCountRec(START_I, START_J, END_I, END_J) << endl;
  cout << "Paths using binomial coeff = " << getPathCountBinom(START_I, START_J, END_I, END_J) << endl;

  //Return success code
  return 0;
}