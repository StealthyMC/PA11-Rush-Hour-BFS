/** @file RushHour.cpp
@author Andrew McIntyre
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
  int move_num = 0;

  /// Set up the board based on input.
  Board board;
  board.initBoard();
  board.readInput(car_num);
  /// Set up queue for boards to solve.
  queue<Board> board_queue;
  /// Set up a map so that duplicate boards can be checked.
  map<string, int> board_map;
  board_queue.push(board);

  /*  Psuedocode

  bfs(v: vertex)
  {
    q = a new empty queue

    // Add v to queue and mark it
    q.enqueue(v)
    Mark v as visited

    while (!q.empty())
    {
      q.dequeue(w)
      for (each unvisited vertex u adjacent to w)
      {
        Mark u as visited
        q.enqueue(u)
      }
    }
  }

  */
  /// Initialize variable to keep track of whether or not the board is solved.
  bool solved = false;
  /// Add default state of board to queue and mark it.
  board_queue.push(board); // adds board to board_queue
  Board& board_check = board_queue.front(); // fetches the board at the front
  board_map[board_check.boardToString()] = move_num; // marks board as visited

  while (board_queue.empty() == false && solved == false)
  {
    board_queue.pop();  // pop the board from queue

    int i = 0;
    // for each unvisited vertex
    while (board_map.count(board_check.boardToString()) == 0 && i < car_num)
    {
      board.setCursor(i); // orient the cursor
      if (board.moveForward() == true)
      {
        board_queue.push(board);  // add to queue
        board_check = board_queue.front();  // fetch the board
        board_map[board_check.boardToString()] = move_num; // marks board as visited
        solved = board_check.isSolved();
      }
      if (board.moveBackward() == true)
      {
        board_queue.push(board);  // add to queue
        board_check = board_queue.front();  // fetch the board
        board_map[board_check.boardToString()] = move_num; // marks board as visited
        solved = board_check.isSolved();
      }
      i++;
    }
  }
  // return the move_num stored in the map for the current board selected
  // from the queue
  return board_map[board_check.boardToString()];
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
