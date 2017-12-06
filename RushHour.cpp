/** @file RushHour.cpp
@author Jared Knutson,Ian Grant,Andrew McIntyre
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
#include <sstream>

#include "Game.h"

using namespace std;

int SolveIt(int car_num)
{
    int move_num=0;
  /*  ALGORITHM

  - perform moves on all cars

  (DO THIS FOR ALL CARS)
  - if move returns true
    true: insert into map and move in opposite direction
    false: don't
  (DO THIS FOR ALL CARS)

  - have we seen this board?
    no: enqueue
    yes: don't


  - run isSolved on board in queue

  */

  /// Set up the board based on input.
  Board board;
  board.readInput(car_num);
  /// Set up queue for boards to solve.
  queue<Board> board_queue;
  /// Set up a map so that duplicate boards can be checked.
  map<string, int> board_map;
  board_queue.push(board);

  while (board_queue.empty() == false)
  {
    for (int i = 0; i < car_num; i++)
    {
      /// Orient the cursor.
      board.setCursor(i);
      /** Attempt to move the car in both directions. If a certain move results
      in no collisions, the move is valid. If the move is valid, queue the current
      state of the board. */
      if (board.moveForward() == true)
      {
        if (board_map.count(board.a2d2string()) == 0)
        {
          move_num++;
          board.printBoard();
          board_queue.push(board);
          board_map[board.a2d2string()] = move_num;
          move_num--;
          board.moveBackward();
        }
      }
      if (board.moveBackward() == true)
      {
        if (board_map.count(board.a2d2string()) == 0)
        {
          move_num++;
          board.printBoard();
          board_queue.push(board);
          board_map[board.a2d2string()] = move_num;
          move_num--;
          board.moveForward();
        }
      }
    }
    if (board.isSolved())
    {
        return board_map[board.a2d2string()];
    }
    Board& temp = board_queue.front();
    cout << 1 << endl;
    board=temp;
    cout << 2 << endl;
    board_queue.pop();
  }
  cout << "EMPTY" << endl;
  //board.printBoard();
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
