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
#include <vector>
using namespace std;

//Vechicle Prototype
class Board
{
    public:
    class Vehicle
    {
        public:
            Vehicle(int length_set, char orient_set, int row_set, int col_set)
            {
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
    }
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
                Vehicle tempCar(length,orient,++row,++col);
                /// Insert car based on stats.
                carVector.push_back(tempCar);
            }
        }
        updateBoard();
    }
    /**
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
    void updateBoard()
    {
        for (vector<Vehicle>::iterator it = carVector.begin(); it != carVector.end(); it++)
        {
            for (int i = 0; i < it-> length; i++)
            {
                if (it->orient == 'H' || it->orient == 'h')
                    lot[it->row][it->col + i] = 1;
                else if (it->orient == 'V' || it->orient == 'v')
                    lot[it->row+i][it->col] = 1;
                else
                    cout << "INVALID ORIENTATION!" << endl;
            }
        }
    }
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

    bool moveForward(int i)
    {
        if(carVector.at(i).orient == 'H' && lot[carVector.at(i).row][carVector.at(i).col + carVector.at(i).length] == 0 && carVector.at(i).col < 6 - carVector.at(i).length)
        {
            carVector.at(i).col++;

            lot[carVector.at(i).row][carVector.at(i).col] = 1;
            for (int i = 0; i < carVector.at(i).length; i++)
            {
                lot[carVector.at(i).row][carVector.at(i).col+i] = 1;
                lot[carVector.at(i).row][carVector.at(i).col-1] = 0;
            }
            return true;
        }
        else
            return false;
        if(carVector.at(i).orient == 'V' && lot[carVector.at(i).row + carVector.at(i).length][carVector.at(i).col] == 0 && carVector.at(i).row < 6 - carVector.at(i).length)
        {
            carVector.at(i).row++;

            lot[carVector.at(i).row][carVector.at(i).col] = 1;
            for (int i = 0; i < carVector.at(i).length; i++)
            {
                lot[carVector.at(i).row+i][carVector.at(i).col] = 1;
                lot[carVector.at(i).row-1][carVector.at(i).col] = 0;
            }
        }
        else
            return false;
    }

    int lot[8][8];
    vector<Vehicle> carVector;
};


