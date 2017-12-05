// Documentation/*{{{*/
/** @file rushhour.cpp
@author Jared Knutson,Ian Grant, Andrew McIntyre
@version Revision 1.0
@brief  This program will implement a solution to the rush hour programming challenge.

@details This program is the author's attempt at creating a solution to the rush
hour programming challenge. The input to the program will be provided through stdin.
The format of the input is one integer used to determine the amount of cars, each line,
after that will correspond with size of the vehicle, orientation of the vehicle, and the grid location
on the game board. This will then be stored in a linked list data structure.
@date Saturday, December 2, 2017
*/

// Program Description/Support /////////////////////////////////////////////////
/**
@mainpage This program requires a list class using a linked list
format with nodes called vehicles. It uses a solveIt function
 and a main loop. When compiling this program only include this file.
The fuctions used are solveIt(), and a class called List.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge. I have tested all of the functions
included in this file. All have passed the test cases and are working properly.
*/

/**
@param
 *
 * Programmer       : Student, Jared Knutson, Ian Grant, Andrew McIntrye
 * Project Number   : 11
 * Date Due         : 12/06/2017
 }}}*/

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <map>
#include <queue>
#include <string>
//test change
using namespace std;

const int MAXBOARDSIZE = 6;

class List {/*{{{*/
  public:
    /**
    @param      N/A
    @pre        No List Object
    @post       List object is instantiated.
    @exception  N/A
    @note       The Default Constructor initializes a new object.
    @return     N/A
    **/
    List() {
        head = cursor = NULL;
    }

    /**
    @param      const List& other:     Other list to copy.
    @pre        No List Object
    @post       List object is instantiated.
    @exception  N/A
    @note       The Copy Constructor creates a copy of the list passed as parameter.
    @return     N/A
    **/
    List( const List& other ) {
        // Grab each node from other
        Vehicle *next_ptr;
        Vehicle *other_ptr;

        // Copy head
        other_ptr = other.head;
        head = new Vehicle( other_ptr->m_size, other_ptr->m_orient, other_ptr->m_row, other_ptr->m_col, NULL );
        cursor = head;

        // Copy rest of list until end of other list
        while( other_ptr->next != NULL )
        {
            next_ptr = new Vehicle( other_ptr->m_size, other_ptr->m_orient, other_ptr->m_row, other_ptr->m_col, next_ptr );
            cursor = next_ptr;
            other_ptr = other_ptr->next;
        }
    }

    /**
    @param      N/A
    @pre        List object exists
    @post       List object is deleted.
    @exception  N/A
    @note       The Destructor clears the list a deletes each object.
    @return     N/A
    **/
    ~List() {
        clear();
    }

    /**
    @param      const List& other
    @pre        List to be copied.
    @post       List object is copied and returned.
    @exception  N/A
    @note       creates a copy of the object through assignment overload operator.
    @return     returns a list object.
    **/
    List& operator=( const List& other ) {
        // Grab each node from other
        Vehicle *next_ptr;
        Vehicle *other_ptr;

        other_ptr = other.head;
        this->head = new Vehicle( other_ptr->m_size, other_ptr->m_orient, other_ptr->m_row, other_ptr->m_col, NULL );
        cursor = head;

        while( other_ptr->next != NULL )
        {
            next_ptr = new Vehicle( other_ptr->m_size, other_ptr->m_orient, other_ptr->m_row, other_ptr->m_col, next_ptr );
            this->cursor = next_ptr;
            other_ptr = other_ptr->next;
        }
        return *this;
    }

    /**
    @param      const int i
    @pre        Before the method is called the cursor will not be in the correct position
    @post       moves the cursor to position i
    @exception  N/A
    @note       setCursor: sets the cursor to the value passed into the funtion.
    @return     N/A
    **/
    void setCursor(const int i) {
        gotoBeginning();
        for(int j = 0; j < i; j++) {
            gotoNext();
        }
    }

    /**
    @param      const int size
                const char orient
                const int row
                const int col
    @pre        requires the parameters listed above in order to insert data into a new
                dynamically allocated list.
    @post       After this method is called a new node will be inserted into the list.
    @exception  This method will throw a logic error if the list is full.
    @note       Insert method will insert a new Vehicle node into the list.
    @return     N/A
    **/
    void insert( const int size, const char orient, const int row, const int col ) throw ( logic_error ) {
      // If the list is full.
        if ( isFull() )
            throw logic_error ( "insert() full list" );
      // If the list is not full
        else if ( !isEmpty() )
        {
            Vehicle* new_ptr;
            new_ptr = new Vehicle(size, orient, row, col, cursor->next);
            cursor->next = new_ptr;
            cursor = new_ptr;
            gotoEnd();
            cursor->next = NULL;
            cursor = new_ptr;

        // If the list is empty
        } else
        {
            cursor = head = new Vehicle( size, orient, row, col, NULL );
        }
    }

    /**
    @param      N/A
    @pre        Before this method is called a Vehicle will exist.
    @post       After the method is called the vehicle at the cursor will be deleted.
    @exception  This method will throw a logic error if the list of cars is empty
    @note       This method will delete the vehicle at the cursor if it exists.
    @return     N/A
    **/
    void remove() throw ( logic_error ) {
        Vehicle* del_ptr;


        // if list is empty
        if ( isEmpty() )
        {
            throw logic_error( "remove() empty list" );
        // if head is only element left in list
        } else if ( head->next == NULL )
        {
          head = NULL;
          cursor = head;

        // if cursor is at beginning of list
        } else if ( head == cursor )
        {
          del_ptr = head;
          cursor = head->next;
          head = cursor;

        // if cursor is at the end of the list.
        } else if ( cursor->next == NULL )
        {
            del_ptr = cursor;
            gotoPrior();
            cursor->next = NULL;
            gotoBeginning();
            delete del_ptr;

        // if cursor is in the middle of the list
        } else
        {
            del_ptr = cursor;
            gotoPrior();
            cursor->next = del_ptr->next;
            cursor = cursor->next;
            delete del_ptr;
        }
    }

    /**
    @param      N/A
    @pre        N/A
    @post       Returns a boolean value depending upon if the list is empty or not
    @exception  N/A
    @note       This method checks if the list is empty by checking if the head pointer is pointing to an address in memory
    @return     This method returns a bool true if the list is empty and false
                if the list is non empty
    **/
    bool isEmpty() const {
        if ( head == NULL )
            return 1;
        else
            return 0;
    }

    /**
    @param      N/A
    @pre        N/A
    @post       This method returns false no matter what the list is.
    @exception  N/A
    @note       This method does not need to be used
    @return     This mathod returns false no matter the lists length
    **/
    bool isFull() const {
        return false;
    }



    bool insertBoard(string board)
    {
        cout << board << endl;
        bool ret = true;
        if(used[board])
            ret = false;
        return ret;
    }


    /**
    @param      N/A
    @pre        Before this method is called the cursor will be in a random location
    @post       After this method is called the cursor will be pointing to the head node
    @exception  This method will throw a logic error if the list is empty
    @note       This method will set the cursor to the head node.
    @return     N/A
    **/
    void gotoBeginning() throw ( logic_error ) {
        if ( isEmpty() ) {
            throw logic_error( "gotoBeginning() empty list" );
        }
        cursor = head;
    }

    /**
    @param      N/A
    @pre        Before this method is called the cusor will be in a random location
    @post       After this method is called the cursor will be at the end of the list
    @exception  This method will throw a logic error if the list is empty
    @note       This method sets the cursor to the end of the list
    @return     N/A
    **/
    void gotoEnd() throw ( logic_error ) {
        if ( isEmpty() )
            throw logic_error( "gotoEnd() empty list" );
        else
        {
            while( cursor->next != NULL )
            {
                cursor = cursor->next;
            }
        }
    }

    /**
    @param      N/A
    @pre        Before this method is called the cursor will be in a random location
    @post       After this method is called the cursor will be at the next node
    @exception  This method throws an exception if the list is empty
    @note       This method will move the cursor to the next node
    @return     N/A
    **/
    bool gotoNext() throw ( logic_error ) {
        if ( isEmpty() == 1 )
        {
            throw logic_error ( "gotoNext() empty list" );
            return 0;
        }
        else if ( cursor->next != NULL )
        {
            cursor = cursor->next;
            return 1;
        }
        else
            return 0;
    }

    /**
    @param      N/A
    @pre        Before this method is called the cursor will be in a random location
    @post       After this method is called the cursor will be at the previous node
    @exception  This method throws a logic error is the list is empty
    @note       This method will move the cursor to the previous node
    @return     This method returns a bool corresponding to if the move was successful
    **/
    bool gotoPrior() throw ( logic_error ) {
        if ( isEmpty() == 1 )
        {
            throw logic_error( "gotoPrior() empty list" );
            return 0;
        }

        else if ( cursor != head )
        {
            Vehicle* next_ptr;
            next_ptr = head;

            while( next_ptr->next != cursor )
            {
                next_ptr = next_ptr->next;
            }

            cursor = next_ptr;
            return 1;

        } else
            return 0;
    }

    /**
    @param      N/A
    @pre        Before this method is called the list will contain nodes
    @post       After this method is called the list will be empty
    @exception  N/A
    @note       This method clears the list so that it is empty upon completion
    @return     N/A
    **/
    void clear() {
        cursor = head;
        while( cursor != NULL )
        {
            cursor = cursor->next;
            delete( head );
            head = cursor;
        }
        head = NULL;
        cursor = head;
    }

    /**
    @param  int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]
    @pre        The board array passed to the function will not contain the current values of the nodes
    @post       The board array will be modified such that the current row and column will be current
    @exception  N/A
    @note       This method updates the board array with current values from the nodes in the list
    @return     N/A
    **/
    void updateBoard(int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]) {
        Vehicle * save_ptr = cursor;
        for(int i = 0; i<b_size; i++) {
            for(int j = 0; j<b_size; j++) {
                board[i][j] = 0;
            }
        }
        cursor = head;
        while(true) {
            if(cursor->m_size==3) {
                if(cursor->m_orient == 'H') {
                    board[cursor->m_row][cursor->m_col] = 1;
                    board[cursor->m_row][cursor->m_col+1] = 1;
                    board[cursor->m_row][cursor->m_col+2] = 1;
                }
                if(cursor->m_orient == 'V') {
                    board[cursor->m_row][cursor->m_col] = 1;
                    board[cursor->m_row+1][cursor->m_col] = 1;
                    board[cursor->m_row+2][cursor->m_col] = 1;
                }
            }
            else if(cursor->m_size==2) {
                if(cursor->m_orient == 'H') {
                    board[cursor->m_row][cursor->m_col] = 1;
                    board[cursor->m_row][cursor->m_col+1] = 1;
                }
                if(cursor->m_orient == 'V') {
                    board[cursor->m_row][cursor->m_col] = 1;
                    board[cursor->m_row+1][cursor->m_col] = 1;
                }
            }
            if(cursor->next != NULL)
                gotoNext();
            else {
                cursor = save_ptr;
                break;
            }
        }
    }

    /**
    @param      int board[MAXBOARDSIZE][MAXBOARDSIZE]
    @pre        N/A
    @post       This method will take the current layout of the board array and print it to the screen
    @exception  N/A
    @note       This method will take the current layout of the board and print it to the screen
    @return     N/A
    **/
    void printBoard(const int board[MAXBOARDSIZE][MAXBOARDSIZE]) {
        Vehicle * print = cursor;
        while(print->next != NULL) {
            cout << print->m_row << " " << print->m_col << endl;
            print = print->next;
        }
        for(int i = 0; i<MAXBOARDSIZE; i++ ) {
            for(int j = 0; j<MAXBOARDSIZE; j++ ) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
    @param      int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]
    @pre        Before this method is called the car will be in its initial position
    @post       After this method is called the car will be moved one space forward on the board
    @exception  N/A
    @note       This method will move the car at the cursor one position forward and then update the board
    @return     This method returns a bool value indicating success or failure
    **/
    bool moveForward(int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]) {
        if(!isCollision(board, true)) {
            if(cursor->m_orient == 'H') {
                cursor->m_col++;
            }
            else if(cursor->m_orient == 'V') {
                cursor->m_row++;
            }
            updateBoard(board);
            return true;
        }
        return false;
    }

    /**
    @param      int (&board)[6][6]
    @pre        Before this method is called the car will be in its initial position
    @post       After this method is called the car will have moved one space back
    @exception  N/A
    @note       This method moves the car at the cursor one space backward if there is no obstruction
    @return     This method returns a bool value indicating success or failure
    **/
    bool moveBackward(int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]) {
        if(!isCollision(board, false)) {
            if(cursor->m_orient == 'H') {
                cursor->m_col--;
            }
            else if(cursor->m_orient == 'V') {
                cursor->m_row--;
            }
            updateBoard(board);
            return true;
        }
        return false;
    }

    /**
    @param      int board[6][6]
                bool forward
    @pre        This method is called from the moveForward and moveBackward methods
    @post       This method will determine if there is an obstruction in the way of the car moving
    @exception  N/A
    @note       This method uses the node data for the vehicle at the cursor to determine if there is an obstruction in its path
    @return     This method returns a bool value success and failure
    **/
    bool isCollision(const int board[MAXBOARDSIZE][MAXBOARDSIZE], bool forward) {
        if(cursor->m_size==2) {
            if(cursor->m_orient == 'V') {
                if(forward) {
                    if(cursor->m_row+2 < b_size && board[cursor->m_row+2][cursor->m_col] == 0)
                        return false;
                    else
                        return true;
                } else {
                    if(cursor->m_row-1 >= 0 && board[cursor->m_row-1][cursor->m_col] == 0)
                        return false;
                    else
                        return true;
                }
            }
            if(cursor->m_orient == 'H') {
                if(forward) {
                    if(cursor->m_col+2 < b_size && board[cursor->m_row][cursor->m_col+2] == 0)
                        return false;
                    else
                        return true;
                } else {
                    if(cursor->m_col-1 >=0 && board[cursor->m_row][cursor->m_col-1] == 0)
                        return false;
                    else
                        return true;
                }
            }
        }
        if(cursor->m_size==3) {
            if(cursor->m_orient == 'V') {
                if(forward) {
                    if(cursor->m_row+3 < b_size && board[cursor->m_row+3][cursor->m_col] == 0)
                        return false;
                    else
                        return true;
                } else {
                    if(cursor->m_row-1 >= 0 && board[cursor->m_row-1][cursor->m_col] == 0)
                        return false;
                    else
                        return true;
                }
            }
            if(cursor->m_orient == 'H') {
                if(forward) {
                    if(cursor->m_col+3 < b_size && board[cursor->m_row][cursor->m_col+3] == 0)
                        return false;
                    else
                        return true;
                } else {
                    if(cursor->m_col-1 >= 0 &&board[cursor->m_row][cursor->m_col-1] == 0)
                        return false;
                    else
                        return true;
                }
            }
        }
    }

    /**
    @param      N/A
    @pre        N/A
    @post       This method checks if the first car is in grid square col 4
    @exception  N/A
    @note       If the first car is in grid location 4 then the method returns true
    @return     returns true if solved and false if failed to solve
    **/
    bool isSolved() {
        // if car 0 is all the way to the right in the board
        if (head->m_col == 4) {
            return true;
        }
        return false;
    }

    /**
    @param      N/A
    @pre        N/A
    @post       Gets the index value of the cursor
    @exception  N/A
    @note       This method gets the index value of the cursor
    @return     Returns an integer value corresponding to the index of the cursor
    **/
    int getCursor() {
        Vehicle* cur = head;
        int i = 0;
        while(cur != cursor) {
            cur = cur->next;
            i++;
        }
        return i;
    }
    /**
     * @param   int (&board)[MAXBOARDSIZE][MAXBOARDSIZE]
     * @pre     2d board is not converted to a string
     * @post    2d board is converted to a string
     * @exception N/A
     * @note    the chars after N designate the numofmoves
     */
    string a2d2string(int (&board)[MAXBOARDSIZE][MAXBOARDSIZE], int moveNum)
    {
        string s1="";
        for(int j = 0; j < MAXBOARDSIZE; j++)
        {
            for(int i = 0; i < MAXBOARDSIZE; i++)
            {
                char c = '0' + board[i][j];
                s1.push_back(c);
            }
        }
        if (moveNum < 10)
        {
            char n = '0' +moveNum;
            s1.push_back(n);
        }
        if (moveNum > 10)
        {
            char n1 = '0' + (moveNum/10);
            char n2 = '0' + (moveNum%10);
            s1.push_back(n1);
            s1.push_back(n2);
        }
        return s1;
    }
    int string2a2d(string input,int (&board)[MAXBOARDSIZE][MAXBOARDSIZE])
    {
        int c=0;
        int ret=1000;
        int r1,r2=0;
        for (int i=0;i<b_size;i++)
        {
            for (int j=0;j<b_size;j++)
            {
               board[i][j]=input[c]-48;
               c++;
            }
        }
        if (input[c]='N')
        {
            c++;
            r1=static_cast<int>(input[c])-48;
            c++;
            if (input[c]!='M')
            {
                r2=static_cast<int>(input[c])-48;
                r1=r1*10;
                r1+=r2;
            }
            else
                ret=r1;
        }
    }
    queue<string> GoodBoards;    //check

   private:
    class Vehicle {
        public:
            Vehicle( const int size, const char orient, const int row, const int col, Vehicle* nextPtr )
            {
                m_size = size;
                m_orient = orient;
                m_row = row;
                m_col = col;
                next = nextPtr;
            }

            int m_size;
            char m_orient;
            int m_row;
            int m_col;
            Vehicle* next;
    };
    int b_size;
    Vehicle* head;
    Vehicle* cursor;
    map<string,bool> used; //check
};/*}}}*/


void solveIt(List * carList, int moveNum, int numVehicles, bool& solved, int (&board)[MAXBOARDSIZE][MAXBOARDSIZE], int &cap);

int main ()
{
    int board[MAXBOARDSIZE][MAXBOARDSIZE] = {0};

    int count = 1;
    while(true) {
        bool solved = false;
        int numCars = -1, size, row, col, cap = 90, moves = 0;
        char orient;
        int board[MAXBOARDSIZE][MAXBOARDSIZE] = {0};

        // Get the number of cars
        cin >> numCars;
        if(numCars == 0)
            break;

        // Create a linked list to store the cars
        List * carList = new List;
        // Fill the Linked list with the cars
        for (int i = 0; i < numCars; i++ ) {
            cin >> size >> orient >> row >> col;
            carList->insert(size, orient, row, col);
        }
        carList->gotoBeginning();
        carList->updateBoard(board);
        carList->printBoard(board);
        solveIt(carList, moves, numCars, solved, board, cap);
        if(solved)
            cout << "Scenario " << count << " requires "  << cap << " moves"<< endl;
        else
            cout << "Scenario " << count << " can not be solved in the moves allowed" << endl;
        delete carList;
        count++;
    }
}


void solveIt(List * carList, int moveNum, int numVehicles, bool& solved, int (&board)[MAXBOARDSIZE][MAXBOARDSIZE], int &cap)
{
    for (int i = numVehicles; i > 0; i--)
    {
      for (int j = 0; j < 2; j++)
      {
        (j == 0) ? carList->moveForward(board) : carList->moveBackward(board);
        if (carList->isSolved() == true)
        {
          if (moveNum <= cap)
          {
            cap = moveNum;
            solved = true;
            return;
          }
          else
            return;
        }
        else
        {
            cout << 1 << endl;
          if (carList->insertBoard(carList->a2d2string(board,moveNum)) == true)
          {
              cout << 2 << endl;
              carList->GoodBoards.push(carList->a2d2string(board,moveNum));
              cout << 3 << endl;
          }
          cout << 4 << endl;
        }
      }
    }
    string newBoard = carList->GoodBoards.front();
    carList->GoodBoards.pop();
    carList->string2a2d(newBoard,board);
    solveIt(carList,moveNum,numVehicles,solved,board,cap);
}
