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

// Prototype for vehicle class
class Vehicle;

#include <iostream>
using namespace std;

class Board
{
public:
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

    cursor = NULL;
    head = NULL;
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
    clear();
  }

  /**
  * Inserts a Vehicle into the board, based on passed parameters.
  *
  * Initalizes the board. Sets grid elements to 0 and sets pointers. Updates the
  * board with the new Vehicle that was just inserted.
  *
  * @param  length_set  The length of the car.
  * @param  orient_set  The orientation of the car.
  * @param  row_set     Row position of car.
  * @param  col_set     Column position of car.
  * @return This is a void function.
  *
  * @pre   Car data will be obtained and be ready to be passed.
  * @post  A new Vehicle object will be created, with the data that was passed
  *        into the method.
  */
  void insert(int length_set, char orient_set, int row_set, int col_set)
  {
    /// First, insert the car and its data into the linked list.
    if (isEmpty() == true)
      cursor = head = new Vehicle(length_set, orient_set, row_set, col_set, NULL);
    else
    {
      cursor->next = new Vehicle(length_set, orient_set, row_set, col_set, NULL);
      cursor = cursor->next;
    }
    /// Then, update the board with the newly inserted car.
    lot[cursor->row][cursor->col] = 1;
    for (int i = 0; i < cursor->length; i++)
    {
      if (cursor->orient == 'H')
        lot[cursor->row][cursor->col + i] = 1;
      else if (cursor->orient == 'V')
        lot[cursor->row + i][cursor->col] = 1;
      else
        cout << "INVALID ORIENTATION!" << endl;
    }
  }

  /**
  * Checks if the List is empty or not.
  *
  * Simply returns if head points to NULL or not.
  *
  * @pre   n/a.
  * @post  The status of the head pointer will be returned.
  */
  bool isEmpty() const  {return (head == NULL);}
  /**
  * Moves the cursor to the beginning.
  *
  * Sets the cursor to the head.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  Cursor will be pointing to the first Vehicle of the List.
  */
  void moveToBeginning() {cursor = head;}
  /**
  * Moves the cursor to the next Vehicle.
  *
  * The cursor will be set equal to its next pointer, which is of type Vehicle.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  Cursor will be pointing to the next Vehicle.
  */
  void gotoNext() {cursor = cursor->next;}
  /**
  * Moves cursor to the previous Vehicle.
  *
  * Sets a temp pointer that points to the head, and loops through the List
  * until the temp pointer sees that the next Vehicle is the one that the
  * cursor points to. The cursor is then assigned to the temp.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  Cursor will be pointing to the previous Vehicle.
  */
  void gotoPrior()
  {
    Vehicle* temp = head;
    while (temp->next != cursor)
      gotoNext();
    cursor = temp;
  }
  /**
  * Removes a Vehicle from the List.
  *
  * First checks if the cursor is at the head, and if so, move the cursor to the
  * next Vehicle and delete the head, as well as reassigning the head after.
  * Otherwise, set a temp cursor pointing to the Vehicle to delete. Move the
  * cursor backwards one, and then link the Vehicle to the Vehicle AFTER the
  * temp pointer. Then delete the pointer. If the cursor not at the end of the
  * List, move the cursor one Vehicle, otherwise, return the cursor to the head
  * of the List.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  Vehicle will be deleted and the cursor will be repositioned.
  */
  void remove()
  {
    if (isEmpty() == false)
    {
    	// beginning of list
    	if (cursor == head)
    	{
        gotoNext();
        delete head;
        head = cursor;
    	}
    	// middle/end of list
    	else
    	{
        Vehicle* temp = cursor;
  		   gotoPrior();
        cursor->next = cursor->next->next;
        delete temp;
        if (cursor->next != NULL)
          gotoNext();
        else
          moveToBeginning();
    	}
    }
  }
  /**
  * Removes all Vehicle objects from List.
  *
  * Loops through the List by setting the cursor to the head, and deleting the
  * head until the cursor is pointing to a nonexistent object.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  The List will be empty.
  */
  void clear()
  {
    moveToBeginning();
    while (cursor != NULL)
      remove();
  }
  /**
  * Sets the cursor to the number of a car.
  *
  * Takes in an integer, and then loops through the list until the counter is
  * one less than the passed integer.
  *
  * @pre   Cursor will be pointing at any Vehicle in the List.
  * @post  Cursor will be pointing at the Vehicle number passed.
  */
  void setCursor(int i)
  {
    int count = 0;
    cursor = head;
    while (count < i)
    {
      gotoNext();
      count++;
    }
  }
  /**
  * Sets all elements of parking lot to 0, otherwise known as "empty."
  *
  * @pre   Lot will have cars occupying spaces.
  * @post  The lot will be empty.
  */
  void initBoard()
  {
    /// Set entire board to all zeros
    for (int i = 0; i < 6; i++)
      for (int j = 0; j < 6; j++)
        lot[i][j] = 0;
  }

  /**
  * Moves the car forward (east/south).
  *
  * Moves the car based on orientation. For both horizontal and vertical
  * orientations, the car's head will check if the head + length of car is equal
  * to 0. This should work for any size car. It also checks if the column
  * position is less than the size of the grid minus the length of the car.
  *
  * If conditions are met, the row/column position will be iterated, and have its
  * new head spot in the grid to be set to 1. A loop is run, that for as long
  * as the iterator is less than the length, start filling ones to the
  * right/bottom of the Vehicle.
  *
  * @pre   Vehicle will be sitting in a certain position.
  * @post  Vehicle will be moved right/down one element.
  */
  bool moveForward()
  {
    switch (cursor->orient)
    {
      case 'H':
      {
        if (lot[cursor->row][cursor->col + (cursor->length)] == 0
          && (cursor->col < 6 - cursor->length))
        {
          cursor->col++;  /// Move head of car to the right

          lot[cursor->row][cursor->col] = 1;
          for (int i = 0; i < cursor->length; i++)
          {
            lot[cursor->row][cursor->col + i] = 1;
            lot[cursor->row][cursor->col - 1] = 0;  // Housekeeping!
          }

          /// Finally, return successful move.
          return true;
        }
        else
          return false;
      }
      break;
      case 'V':
      {
        if (lot[cursor->row + cursor->length][cursor->col] == 0
          && (cursor->row < 6 - cursor->length))
        {
          cursor->row++;  /// Move head of car down

          /// Then, update the board with the newly inserted car.
          lot[cursor->row][cursor->col] = 1;
          for (int i = 0; i < cursor->length; i++)
          {
            lot[cursor->row + i][cursor->col] = 1;
            lot[cursor->row - 1][cursor->col] = 0;  // Housekeeping!
          }

          /// Finally, return successful move.
          return true;
        }
        else
          return false;
      }
      break;
      default:
        cout << "NO ORIENTATION GIVEN." << endl;
        return false;
      break;
    }
  }
  /**
  * Moves the car backward (west/north).
  *
  * Moves the car based on orientation. For both horizontal and vertical
  * orientations, the car's head will check if the element behind the head of
  * the car is empty or not. It also checks if the column position is greater
  * than the boarders of the grid.
  *
  * If conditions are met, the row/column position will be decremented, and
  * have its new head spot in the grid to be set to 1.
  *
  * @pre   Vehicle will be sitting in a certain position.
  * @post  Vehicle will be moved left/up one element.
  */
  bool moveBackward()
  {
    switch (cursor->orient)
    {
      case 'H':
      {
        if (lot[cursor->row][cursor->col - 1] == 0
          && (cursor->col > 0))
        {
          cursor->col--;  /// Move head of car to the right
          lot[cursor->row][cursor->col] = 1;
          /// Erase previous tail position (clean up).
          lot[cursor->row][cursor->col + (cursor->length)] = 0;
          /// Finally, return successful move.
          return true;
        }
        else
          return false;
      }
      break;
      case 'V':
      {
        if (lot[cursor->row - 1][cursor->col] == 0
          && (cursor->row > 0))
        {
          cursor->row--;  /// Move head of car down
          lot[cursor->row][cursor->col] = 1;
          /// Erase previous tail position (clean up).
          lot[cursor->row + (cursor->length)][cursor->col] = 0;

          /// Finally, return successful move.
          return true;
        }
        else
          return false;
      }
      break;
      default:
        cout << "NO ORIENTATION GIVEN." << endl;
        return false;
      break;
    }
  }

  /**
  * Checks if the board is solved.
  *
  * Checks if the first Vehicle object's column position is 4, since that would
  * indicate that the Vehicle object made it across the grid succesfully.
  *
  * @pre   n/a.
  * @post  Status of solution will be returned.
  */
  bool isSolved() const
  {
    return (head->col == 4);
  }

  // Function made for testing. Unused in final verison.
  void printBoard()
  {
    for (int i = 0; i < 6; i++)
      for (int j = 0; j < 6; j++)
      {
        cout << lot[i][j] << " ";
        if (j == 5)
          cout << endl;
      }
    cout << endl;
  }

  void readInput(int car_num)
  {
    cout << "Hello" << endl;
    if (car_num > 0)
    {
      int length, row, col;
      char orient;
      for (int i = car_num; i > 0; i--)
      {
        /// Create variables that will read in data, which will then be inserted.
        cin >> length;
        cin >> orient;
        cin >> row;
        cin >> col;

        /// Insert car based on stats.
        insert(length, orient, row, col);
      }
    }
  }

private:
  class Vehicle
  {
  public:
    Vehicle(int length_set, char orient_set, int row_set, int col_set,
      Vehicle* next_set)
    {
      length = length_set;
      orient = orient_set;
      row = row_set;
      col = col_set;
      next = next_set;
    }

    int length;
    char orient;

    int row;
    int col;

    Vehicle* next;
  };

  Vehicle* cursor;
  Vehicle* head;  /// Head of list of Vehicle objects is the target car.

  bool lot[6][6];
};
