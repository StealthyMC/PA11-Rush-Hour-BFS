
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
whenever a function such as <em>moveForward(i)</em> is called, it will perform the
method on the car i is set to.
*/


#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "Traffic.h"

using namespace std;

int SolveIt(int car_num)
{
  int move_num = 0;

  /// Initiate a move counter to keep track of the number of moves.
  Board board;
  /// Create a queue of possible solutions to taste.
  queue<Board> board_queue;
  /// Create a map to keep track of the moves that were already made.
  map<string, int> board_map;
  /// Read and set the cars' information.
  board.readInput(car_num);
  
  /// Push the first state of the board onto the queue.
  board_queue.push(board);
  /// Insert the default state of the board into the map, which marks it.
  board_map.insert(pair<string, int>(board.boardToString(), 0));

  /// While the queue is not empty, try different solutions.
  while (board_queue.empty() == false)
  {
    /// Set the board to the state of the front of the queue.
    board = board_queue.front();
    /// Pop the possible solution off of the board.
    board_queue.pop();
    /// Set the move number to the number of moves on the current state.
    move_num = (*board_map.find(board.boardToString())).second;
    /// If the board is solved, return the number of moves in the current state.
    if (board.isSolved() == true)
      return move_num;
    /// Otherwise, increment the number of moves.
    move_num++;
    /** If the board is not solved, for each car in the vector, try to move them forward
    and backward and store the states in the board if they haven't been "visited" before. */
    for(int i = 0 ; i < car_num ; i++)
        {
          /// Try a move forward.
          if(board.moveForward(i))
          {
            /// And insert into the board if it hasn't been seen before.
            if(board_map.find(board.boardToString()) == board_map.end())
            {
              /// Push the current board state onto the queue, which marks it as a possible solution.
              board_queue.push(board);
              /// Insert into the map now that we've seen this board before.
              board_map.insert(pair<string, int>(board.boardToString(), move_num));
            }
            /// Move in the opposite direction to fix the board.
            board.moveBackward(i);
          }
          /// Repeat the same few moves in the opposite direction.
          if(board.moveBackward(i))
          {
            if(board_map.find(board.boardToString()) == board_map.end())
            {
              board_queue.push(board);
              board_map.insert(pair<string, int>(board.boardToString(), move_num));
            }
            board.moveForward(i);
          }
        }
  }
  /// Finally return the amount of moves needed.
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
