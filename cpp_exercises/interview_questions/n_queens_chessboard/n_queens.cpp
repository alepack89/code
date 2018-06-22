/*
* Compute the number of ways we can place N queens 
* on a NxN chessboard without threatening each other
*/

//Include standard libraries
#include <cstdlib>
#include <iostream>
#include <vector>

//Import everything from standard namespace
using namespace std;

//Function used to check if current board configuration is valid
bool isValidConfiguration(const vector<int>& board)
{
  //Get last queen position
  int currRow = board.size() - 1;
  int currCol = board.back();

  //Check if the configuration is valid
  //Valid configuration => two queens are not on the same
  //row, column or diagonal
  for (int rowIdx = 0; rowIdx < currRow; rowIdx++)
  {
    int rowDiff = abs(currRow - rowIdx);
    int colDiff = abs(currCol - board[rowIdx]);

    if ((colDiff == 0) || (rowDiff == colDiff))
      return false;
  }

  //Configuration is valid 
  return true;
}

//Recursive function
size_t countPossibleConfigurations(int boardSize, vector<int>& board)
{
  //Check if we have placed all the queens
  if (board.size() >= boardSize)
    return 1;

  //Try to place a queen on each column of the current row 
  //Note: the i-th element of the list represents the index of the column,
  //along row i, in which we have places the i-th queen
  size_t dispCount = 0;

  for (int colIdx = 0; colIdx < boardSize; colIdx++)
  {
    //Let's place a queen on column "colIdx" along current row
    //and check if the obtained configuration is valid
    //If the configuration is valid -> continue down the current path
    board.push_back(colIdx);
    if (isValidConfiguration(board) == true)
      dispCount += countPossibleConfigurations(boardSize, board);
    
    //After evaluating this configuration, let's try another one by placing the
    //queen in a new column along the same row
    board.pop_back();
  }

  //Return the computed number of configurations
  return dispCount;
}

//Implementation-agnostic wrapper to be called by the main method
size_t countPossibleConfigurations(int boardSize)
{
  //Create an empty board
  vector<int> board{};

  //Compute configurations via backtracking
  return countPossibleConfigurations(boardSize, board);
}

//Main method
int main(int argc, char* argv[])
{
  //Read board size from input arguments
  int boardSize = 10;
  if (argc > 1)
    boardSize = atoi(argv[1]);

  cout << "Using board size = " << boardSize << endl;

  //Compute the number of ways of placing the queens
  //for all the board sizes up to the requested one
  for (int i = 1; i <= boardSize; i++)
    cout << "Board size = " << i << " - Possibilities = " << countPossibleConfigurations(i) << endl;

  //Code exited normally
  return 0;
}