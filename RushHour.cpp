Skip to content
Help save net neutrality! A free, open internet is once again at stake—and we need your help.
Learn more  Dismiss
This repository
Search
Pull requests
Issues
Marketplace
Explore
 @StealthyMC
 Sign out
 Watch 2
  Star 0  Fork 1 StealthyMC/PA11-Rush-Hour-BFS
 Code  Issues 0  Pull requests 0  Projects 0  Wiki  Insights  Settings
Tree: 2d811c7963 Find file Copy pathPA11-Rush-Hour-BFS/RushHour.cpp
2d811c7  a day ago
@StealthyMC StealthyMC Lan's algorithm mostly works. The class might be broken.
2 contributors @StealthyMC @Ian-Grant
RawBlameHistory      
106 lines (89 sloc)  2.76 KB
/** @file RushHour.cpp
@author Jared Knutson, Ian Grant, Andrew McIntyre
@version Revision 2.0
@brief This program will solve a traffic jam. The result will be the
solution with the smallest number of moves.
@details This is the class implementation of the board and the cars that
interact with it.
@date Monday, December 04, 2017
*/

/**
@mainpage
This short program contains a recursive solution to solving a game of Rush Hour
in the least possible amount of moves using breadth-first search.
The Board class manages all of the Vehicle objects within it, which does so by
modifying an array and moving the car around by changing their row and column
positions. The Vehicles inside of the Board class act as a Linked List, and
whenever a function such as <em>moveForward()</em> is called, it will perform the
method on the car that the cursor pointer is pointing to.
*/

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <map>
#include <queue>
#include <string>

#include "Game.h"

using namespace std;

int SolveIt(int car_num)
{
  int move_num = 0;

  Board board;
  queue<Board> board_queue;
  map<string, int> board_map;
  board.readInput(car_num);

  board_queue.push(board);
  board_map.insert(pair<string, int>(board.boardToString(), 0));

  while (board_queue.empty() == false)
  {
    board = board_queue.front();
    board_queue.pop();

    move_num = (*board_map.find(board.boardToString())).second;

    if (board.isSolved() == true)
      return move_num;
    move_num++;

    for (int i = 0; i < car_num; i++)
    {
      board.setCursor(i);
      if (board.moveForward() == true)
      {
        if (board_map.find(board.boardToString()) == board_map.end())
        {
          board_queue.push(board);
          board_map.insert(pair<string, int>(board.boardToString(), move_num));
        }
        board.moveBackward();
      }
      if (board.moveBackward() == true && board_map.find(board.boardToString()) == board_map.end())
      {
        if (board_map.find(board.boardToString()) == board_map.end())
        {
          board_queue.push(board);
          board_map.insert(pair<string, int>(board.boardToString(), move_num));
        }
        board.moveForward();
      }
    }
  }

  return move_num;
}

int main()
{
  /// Initiate variable to fetch the number of cars.
  int car_num = 0;
  /// Set the scenario to start at scenario #1.
  int scenario = 1;
  /// Perform a tail read to fetch the number of cars.
  cin >> car_num;
  while (car_num != 0)
  {
    int moves = SolveIt(car_num);
    /// Print final message.
    cout << "Scenario " << scenario << " requires " << moves << " moves" << endl;
    /** Once the number of moves is posted, increment the scenario variable to
    indicate the end of the scenario. */
    scenario++;
    cin >> car_num;
  }

  return 0;
}
© 2017 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
API
Training
Shop
Blog
About
