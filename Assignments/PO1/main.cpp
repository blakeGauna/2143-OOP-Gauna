/**
*                    
*  Author:           Blake Gauna
*  Title:            Linked List Example
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        This class will be a basic container type of integers that can grow or shrink easily without the need to copy values over to newly allocated memory when resizing 
* 
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct node {
    int data;  // data value (could be a lot more values)
    node* next;  // we always need a "link" in a linked list
    node* prev;  // another link

    node(int x) {  // constructor to make adding values easy
        data = x;
        next = NULL;    
        prev = NULL;
    }
};
/**
 * myVector
 * 
 * Description:
 *      This class contains methods that act as a vector would. 
 *      it is a doubly linked list  
 * 
 * Public Methods:
 *      myVector() 
 *      myVector(int *arr, int s)
 *      myVector(string filename, int*& arr)
 * void pushFront(myVector V2)
 * void pushFront(int x)
 * void pushRear(int x)
 * void pushRear(myVector V2)
 * void popFront()
 * void popRear()    
 * void pushAt(int loc, int val)
 * void popAt(int val)
 * bool search(int x)
 * void print()
 *
 * Private Methods:
 *      int size;
 *      int* A;
 *      node* head;
 *      node* tail;
 * 
 * Usage: 
 *      Example:
 *
 *      myVector v1;
 *      v1.pushFront(3) 
 *      print.v1()
 *
 */
class myVector {
private:
  int size;    //holds the size of the array 
  node* head;  //reference to the front
  node* tail;  //reference to the back
public:
    /**
     * Public : myVector
     * 
     * Description:
     *      Initializes head and tail to NULL.
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      none.
     */
  myVector() {
      head = tail = NULL;
    }

    /**
     * Public : myVector
     * 
     * Description:
     *      Reads in array and put them in nodes.
     * 
     * Params:
     *      int *arr
     *      int s
     * Returns:
     *      none.
     */
  myVector(int *arr, int s) {
      head = tail = NULL;  
        for (int i = s-1; i > -1; i--) {
          head = new node(arr[i]); 
          if (head->next == NULL){
            tail = head;
          }
          else {
            head->next->prev = head;
          }
        }
    }
    
    /**
     * Public : myVector
     * 
     * Description:
     *      Reads in intergers from a file and stores.
     * 
     * Params:
     *      string filename
     *      int*&  arr
     * 
     * Returns:
     *      none.
     */
  myVector(string filename, int*& arr) {
      ifstream fin;         // stream reference
                          
      fin.open(filename);   // open the file
                          
      arr = new int[33];  // allocate new array of correct size
                          
      int i = 0;            // need an array index for our while loop
                          
      // Can also use for loop since we know the exact count in file.
      // eof = end of file flag
      // `!fin.eof()` evaulates to true when we hit end of file.
      while (!fin.eof()) {
        fin >> arr[i];  // read file value straight into array
                        // at index i
        i++;            // increment array index
    }
}
/**
     * Public : pushFront
     * 
     * Description:
     *      adds entire other.list to front of this.list
     * 
     * Params:
     *      myVector V2
     * 
     * Returns:
     *      none.
     */
  void pushFront(myVector V2) {
    node *temp = V2.tail;
    while (temp){
         pushFront(temp->data);
         temp = temp->next;
    }
}
/**
     * Public : pushFront
     * 
     * Description:
     *      adds single value to front of this.list
     * 
     * Params:
     *      int x
     * 
     * Returns:
     *      none.
     */
  void pushFront(int x) {
        node* tempPtr = new node(x);  // create a new int and
                                      // add data to it

        if (!head) {  // `!head` implies empty list  // So does `head == NULL`
            head = tail = tempPtr;  // tempPtr in head (points head to tempPtr)
                             
        } else {                   // list not empty
            tempPtr->next = head;
            head->prev = tempPtr;  // point tempPtr's next to what head points to
            head = tempPtr;        // now point head to tempPtr
        }
    }
/**
     * Public : pushRear
     * 
     * Description:
     *      adds single value to back of this.list
     * 
     * Params:
     *      int x
     * 
     * Returns:
     *      none.
     */
  void pushRear(int x){
      
      node* tempPtr = new node(x);
      
      if (!head){
        head = tail = tempPtr;
      }
      
      else {
        tempPtr->prev = tail;
        tail->next = tempPtr;
        tail = tempPtr;
      }

    }
  /**
     * Public : pushRear
     * 
     * Description:
     *      adds entire other.list to back of this.list
     * 
     * Params:
     *      myVector V2
     * 
     * Returns:
     *      none.
     */
  void pushRear(myVector V2) {
    node *temp = V2.head;
    while (temp){
         pushRear(temp->data);
         temp = temp->next;
    }
}
/**
     * Public : popFront
     * 
     * Description:
     *      removes single value from front of list
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      none.
     */
  void popFront(){
      node* temp = head;
      head = temp->next;
      delete temp;
    }
/**
     * Public : popRear
     * 
     * Description:
     *      removes single value from rear of list
     * 
     * Params:
     *      none
     * 
     * Returns:
     *      none.
     */
  void popRear(){
      if (head == NULL)
        return;
    if (head->next == NULL) {
        delete head;
        return;
    }
    // Find the second last node
    node* second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;
    // Delete last node
    delete (second_last->next);
    // Change next of second last
    second_last->next = NULL;
    return;
    }

/**
     * Public : pushAt
     * 
     * Description:
     *      pushes a value at a certain indice
     * 
     * Params:
     *      int loc
     *      int val
     * 
     * Returns:
     *      none.
     */
  // void pushAt(int loc, int val){
  //     A[loc] = val;
  //   }
      
/**
     * Public : popAt
     * 
     * Description:
     *      removes single value from an indexed location
     *   if index between 0 and size of list -1
     * 
     * Params:
     *      
     *      int val
     * 
     * Returns:
     *      none.
     */
  // void popAt(int val){
      
  //   }
    
/**
     * Public : find
     * 
     * Description:
     *      find location of item (index) if it exists
     * 
     * Params:
     *      
     *      int x
     * 
     * Returns:
     *      bool (true or false)
     */
  // bool find(int x){ 
  //   node* current = head; // Initialize current 
  //   while (current != NULL) 
  //   { 
  //       if (current->data == x) 
  //           return true; 
  //       current = current->next; 
  //   } 
  //   return false; 
  //   } 
  /**
     * Public : print
     * 
     * Description:
     *      prints the linked list to the terminal
     *      and to an output file
     * 
     * Params:
     *      
     *    none
     * 
     * Returns:
     *      none
     */
  void print() {  
    ofstream ofile;
    ofile.open("test.out");
    ofile << "Blake Gauna \n";
    ofile << "9/10/21\n";
    ofile << "Fall 2143\n\n";
    cout << "[";
    ofile << '[';
    node* temp = head; // temp pointer copies head
    while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`
      ofile << temp->data;
      cout << temp->data;  // print data from node
      if (temp->next) {
           cout << ", ";
           ofile << ", ";
      }
      temp = temp->next;  // move to next node
    }
    cout << ']';
    ofile << ']';
   cout << endl << endl;
   ofile << endl << endl;
  }
};

//Main was used to test our methods in out myVector class

int main() {
int x = 0;   
myVector v1;          //defining v1 to be of class myVector
v1.pushFront(18);     //pushing 18 to the front of v1
v1.pushFront(20);     //pushing 20 to the front of v1 
v1.pushFront(25);     //pushing 25 to the front of v1
v1.pushRear(18);      //pushing 18 to the front of v1
v1.pushRear(20);      //pushing 20 to the front of v1
v1.pushRear(25);      //pushing 25 to the front of v1
// v1.pushAt(1,3);
v1.print();           //print v1

// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};  //defining an array that holds ints
myVector v2(A,5);            //passing A through my overloaded constructor
v2.print();                  //prints v2

//[11, 25, 33, 47, 51]

v2.pushFront(9);             //pushing 9 to the front of v2
//v2.inOrderPush(27);
v2.pushRear(63);             //pushing 63 to the back of v2
v2.print();                  //prints v2

//[9, 11, 25, 27, 33, 47, 51, 63]

v1.pushRear(v2);             //pushes the entirity of v2 to the back of v1
v1.print();                  //prints v1

// [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

//x = v1.popFront();
//x = v1.popFront();
//x = v1.popFront();

v1.print();                  //prints v1

// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

//cout<<x<<endl;
// 18

//x = v1.popRear();
//x = v1.popRear();
//x = v1.popRear();

v1.print();                  //prints v1

// [18, 20, 25, 9, 11, 25, 27, 33]

//cout<<x<<endl;
// 47

//x = v2.popAt(3);
v2.print();                  //prints v2

// [9, 11, 25, 33, 47, 51, 63]

//cout<<x<<endl;
// 27

//x = v2.find(51);
//cout<<x<<endl;
// 5

//x = v2.find(99);
//cout<<x<<endl;
// -1

myVector v3(v1);           //copies v1 into v3. 
v3.print();                //prints v3

// [18, 20, 25, 9, 11, 25, 27, 33]

//v3.pushFront(v2);
//v3.print();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

//myVector v4("input.dat");
//v4.pushRear(v3);
//v4.print();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
 return 0;
}