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
#include <vector>
#include <string>

#include "Traffic.h"

using namespace std;

int main() {
    Board traffic;
    traffic.initBoard();
    traffic.printBoard();
    /// Initiate variable to fetch the number of cars.
    int car_num = 0;
    /// Set the scenario to start at scenario #1.
    int scenario = 1;
    /// Perform a tail read to fetch the number of cars.
    cin >> car_num;
    //while (car_num != 0)
    //{
        traffic.readInput();
        /// Print final message.
        //cout << "Scenario " << scenario << " requires " << moves << " moves" << endl;
        /** Once the number of moves is posted, increment the scenario variable to
          indicate the end of the scenario. */
        //scenario++;
        //cin >> car_num;
    //}
    return 0;
}
