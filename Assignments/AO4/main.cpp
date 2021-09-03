
/*****************************************************************************
*                    
*  Author:           Blake Gauna
*  Email:            blakegauna@yahoo.com
*  Label:            AO4
*  Title:            Commenting
*  Course:           2143-OOP
*  Semester:         Fall 2021
* 
*  Description:
*        This code generates a circular array and fills the spots with
*        integers. These integets point at eachother, and we made
*        functions that allow us to push and pop items in the array.
* 
* 
*  Files:            main.cpp
*****************************************************************************/

#include <iostream>

using namespace std;


/**
 * CircularArrayQue
 * 
 * Description:
 *      My class contains methods that allow us to create a 
 *      circular queue. These methods include push, pop, two
 *      overloaded constructors, and a method that lets us be
 *      able to cout an object.
 *
 * Public Methods:
 *      -  CircularArrayQue()
 *      -  CircularArrayQue(int size)
 *      -  void      Push(int item)
 *      -  int       Pop()
 * 
 * Private Methods:
 *      - void       init(int size = 0)
 *      - bool       Full()
 * 
 * Usage: 
 *      - Push or Pop numbers in a ciruclar array
 *      that can be accessed through pointers. 
 *      
 */
class CircularArrayQue {                  //declaring a class
private:                                  
    int *Container;                       //integer pointer that will be used to navigate
    int Front;                            //front of the queue
    int Rear;                             //back of the queue
    int QueSize;                          //items in the queue
    int CurrentSize;                      //current size of the queue
    
    /**
     * Private : init
     * 
     * Description:
     *      initializes front, rear, and size to 0; updates quesize. 
     * 
     * Params:
     *      int     :  array size
     * 
     * Returns:
     *      Nothing
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0; 
        QueSize = size;
    }
    /**
     * Private : Full
     * 
     * Description:
     *      if the function is called and the queue is full, it returns
     *      the size.
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      Size of the queue
     */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    /**
     * Public : CircularArrayQue
     * 
     * Description:
     *      constructor for my class that hard-codes. 
     *      the size of the array to 10.
     * Params:
     *      None
     * 
     * Returns:
     *      Nothing
     */
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    /**
     * Public : CircularArrayQue(int size)
     * 
     * Description:
     *      overloaded constructor that passes the size
     *      of the array through a parameter
     * Params:
     *      int :   size        (size of the array)
     * 
     * Returns:
     *      Nothing
     */
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }
    /**
     * Public : void Push(int item)
     * 
     * Description:
     *      Pushes an int to the rear of the array and
     *      if the array is full, it lets the user know.
     *      When pushing an int, the rear is incremented by 1
     *      as well.
     *
     * Params:
     *      int :   item       (int you want to push)
     * 
     * Returns:
     *      Nothing
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }
    /**
     * Public : int Pop()
     * 
     * Description:
     *      Deletes elements from circular queue in 
     *      the acronym FIFO (First in First out) and then
     *      traverses the front + 1.
     * Params:
     *      none
     * 
     * Returns:
     *      integer temp, which is the front of the queue.
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    //Friending a function so it can overload an operator like I want it to.
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};
/**
     * Public : ostream    &operator
     * 
     * Description:
     *      Overloads the << operator to print objects,
     *      in this case, integers in our circular queue
     *      through a for-loop until we reach the end of the
     *      array.
     * Params:
     *      - ostream      &os
     *       - const       CircularArrayQue &other
     * 
     * Returns:
     *      os
     */
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;     
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);    //Declaring class with object C1 of size 5.

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);                //Pushing 1 in the the front of the array 
    C1.Push(2);                //Pushing 2 in the the front of the array
    C1.Push(3);                //Pushing 3 in the the front of the array
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;        //Printing 1 2 3

    //  C1.Push(1);
    //  C1.Push(2);
    //  C1.Push(3);

    cout << C1 << endl;        //Printing 1 2 3
}