/**
@details The Board class manages all of the Vehicle objects within it, which does so by
modifying an array and moving the car around by changing their row and column
positions. The Vehicles inside of the Board class act as a Linked List, and
whenever a function such as <em>moveForward()</em> is called, it will perform the
method on the car that the cursor pointer is pointing to.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <vector>
using namespace std;

//Vechicle Prototype
class Board
{
    public:
    class Vehicle
    {
        public:
            Vehicle(int length_set, char orient_set, int row_set, int col_set) {
                length = length_set;
                orient = orient_set;
                row = row_set;
                col = col_set;
            }
//            moveForward(int carIndex)
 //           {

  //          }

            int length;
            char orient;
            int row;
            int col;
    };
    /**
     * Default constructor for board.
     *
     * Simply initalizes the board. Sets grid elements to 0 and sets pointers.
     *
     * @pre   The board will not be initialized.
     * @post  The board will be declared, and the grid be ready to have data to be
     *        written to it.
     */
    Board()
    {
        initBoard();
        //carVector
    }
    /**
     * Copy constructor for board.
     *
     * Simply initalizes the board. Sets grid elements to 0 and sets pointers.
     *
     * @pre   The board will not be initialized.
     * @post  The board will be declared, and the grid be ready to have data to be
     *        written to it.
     */
    Board(const Board& other)
    {
        initBoard();
        for (int i=0; i< 8; i++)
        {
            for (int j=0; j<8;j++)
            {
                lot[i][j]=other.lot[i][j];
            }
        }
        //moveNum=other.moveNum;
        carVector = other.carVector;
        updateBoard();
    }
    /**
     * Destructor for board.
     *
     * Simply initalizes the board. Sets grid elements to 0 and sets pointers.
     *
     * @pre   The board will have a list of Vehicle objects.
     * @post  All of the Vehicles will be deallocated from memory, and the List
     *        will be deleted from memory.
     */
    ~Board()
    {
        carVector.clear();
    }
    Board& operator=(const Board& other)
    {
        if (this == &other)
          return *this;

        carVector.clear();
        for (int i=0; i< 8; i++)
        {
            for (int j=0; j<8;j++)
            {
                lot[i][j]=other.lot[i][j];
            }
        }       initBoard();
        //moveNum=other.moveNum;
        carVector = other.carVector;
        updateBoard();
        return *this;
    }
    /**
     * read input of board inupt
     * Reads in the board input given by the user
     *
     * @pre board not read into array
     * @post All of the input is read into the array
     */
    void readInput(int car_num)
    {
        if (car_num > 0)
        {
            int length, row, col;
            char orient;
            for (int i = 0; i < car_num; i++)
            {
                /// Create variables that will read in data, which will then be inserted.
                cin >> length;
                cin >> orient;
                cin >> row;
                cin >> col;
                orient=toupper(orient);
                Vehicle tempCar(length,orient,++row,++col);
                /// Insert car based on stats.
                carVector.push_back(tempCar);
            }
        }
        updateBoard();
    }
    /**
     * Print Board
     * Sets all elements of parking lot to 0, otherwise known as "empty."
     *
     * @pre   Lot will have cars occupying spaces.
     * @post  The lot will be empty.
     */
    void printBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << lot[i][j] << " ";
            }
            cout << endl;
        }
    }
    /**
     * init board
     * Initializes the board to all 9s to make the boarder then all 0s for real board
     *
     * @pre board not initalized
     * @post board initalized
     */
    void initBoard()
    {
        /// Set entire board to all zeros
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                lot[i][j] = 9;
        for (int i = 1; i < 7; i++)
            for (int j = 1; j < 7; j++)
                lot[i][j] = 0;
    }
    /**
     * isSolved
     * Checks if the board is solved or not
     *
     * @pre the board is not checked if it is a solution
     * @post checked if the board is a solution to the puzzle
     * @return bool if the board is a solution
     */
    bool isSolved()
    {
        return (carVector.at(0).col == 6 - (carVector.at(0).length - 1));
    }
    /**
     * Update Board
     * Updates the board with new row and col positions from the car vector
     * @pre the board hasn't been updated with new locations
     * @post the board has been updated with new locations
     * @return void
     */
    void updateBoard()
    {
        for (vector<Vehicle>::iterator it = carVector.begin(); it != carVector.end(); it++)
        {
            for (int i = 0; i < it-> length; i++)
            {
                if (it->orient == 'H')
                    lot[it->row][it->col + i] = 1;
                else if (it->orient == 'V')
                    lot[it->row+i][it->col] = 1;
                else
                    cout << "INVALID ORIENTATION!" << endl;
            }
        }
    }
    /**
     * Board to string
     * Board to string convertor
     * @pre the board has not been translated
     * @post the board has been translated
     */
    string boardToString()
    {
        string s1="";
        for(int j = 1; j < 7; j++)
        {
            for(int i = 1; i < 7; i++)
            {
                char c = '0' + lot[j][i];
                s1.push_back(c);
            }
        }
        return s1;
    }

    /**
     * @param   int i
     * @pre     Called by the RushHour.cpp
     * @post    Returns a bool
     * @note    Checks if there is a collision then moves the car forward
    **/
    bool moveForward(int i)
    {
        if(carVector.at(i).orient == 'H' && isCollision(true, i) == false)
        {
            carVector.at(i).col++;
            initBoard();
            updateBoard();

            return true;
        }

        if(carVector.at(i).orient == 'V' && isCollision(true, i) == false)
        {
            carVector.at(i).row++;
            initBoard();
            updateBoard();
            return true;
        }
        return false;
    }

    /**
     * @param   int i
     * @pre     Called by
     * @post    Returns a bool
     * @note    Checks if there is a collision then moves the car back
    **/
    bool moveBackward(int i)
    {
        if(carVector.at(i).orient == 'H' && isCollision(false, i) == false)
        {
            carVector.at(i).col--;
            initBoard();
            updateBoard();

            return true;
        }

        if(carVector.at(i).orient == 'V' && isCollision(false, i) == false)
        {
            carVector.at(i).row--;
            initBoard();
            updateBoard();
            return true;
        }
            return false;
    }

    /**
     * @param   bool flag
     * @param   int i
     * @pre     Callled by the move methods
     * @post    Returns a bool
     * @note    Checks if there is a collision
    **/
    bool isCollision(bool flag, int i)
    {
        if(carVector.at(i).length==2)
        {
            if(carVector.at(i).orient == 'V')
            {
                if(flag)  // move forward
                {
                    if(carVector.at(i).row+2 < 7 && lot[carVector.at(i).row+2][carVector.at(i).col] == 0)
                        return false;
                    else
                        return true;
                } // move backward
                else if(carVector.at(i).row-1 >= 1 && lot[carVector.at(i).row-1][carVector.at(i).col] == 0)
                    return false;
                else
                    return true;
            }
            if(carVector.at(i).orient == 'H')
            {
                if(flag)
                {
                    if(carVector.at(i).col+2 < 7 && lot[carVector.at(i).row][carVector.at(i).col+2] == 0)
                        return false;
                    else
                        return true;
                }
                else if(carVector.at(i).col-1 >= 1 && lot[carVector.at(i).row][carVector.at(i).col-1] == 0)
                    return false;
                else
                    return true;
            }

        }
        if(carVector.at(i).length==3)
        {
            if(carVector.at(i).orient == 'V')
            {
                if(flag)
                {
                    if(carVector.at(i).row+3 < 7 && lot[carVector.at(i).row+3][carVector.at(i).col] == 0)
                        return false;
                    else
                        return true;
                }
                else if(carVector.at(i).row-1 >= 1 && lot[carVector.at(i).row-1][carVector.at(i).col] == 0)
                    return false;
                else
                    return true;
            }
            if(carVector.at(i).orient == 'H')
            {
                if(flag)
                {
                    if(carVector.at(i).col+3 < 7 && lot[carVector.at(i).row][carVector.at(i).col+3] == 0)
                        return false;
                    else
                        return true;
                }
                else if(carVector.at(i).col-1 >= 1 && lot[carVector.at(i).row][carVector.at(i).col-1] == 0)
                    return false;
                else
                    return true;
            }

        }
        return false;
    }

    int lot[8][8];
    vector<Vehicle> carVector;
};
