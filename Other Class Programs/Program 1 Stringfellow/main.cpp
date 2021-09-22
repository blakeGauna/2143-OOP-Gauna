/*****************************************************************************
*                    
*  Author:           Blake Gauna
*  Label:            Program 1
*  Course:           CMPS 2433
*  Semester:         Fall 2021
* 
*  Description:
*        Given a file of unsigned shorts, this program 
*        is goint to reverse the bits in each number, printing
*        out the original decimal version of the number and the 
*        decimal version of the result.
 
* 
*  Usage:
*        Enter the input file name
*        Enter the output file name
* 
*  Files:            
*        prog1Gauna.cpp
*        mydata.txt
*        prog1.dat
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Prototypes
void openFiles(ifstream&, ofstream&);
unsigned int reverseBits(unsigned int);
void print(int*,ofstream&);

int main() {
 unsigned int n;
 int* arr; //creating array
 int i = 0;
 arr = new int[9];  //initializing array to size 9
 ifstream infile;
 ofstream outfile;
 openFiles(infile, outfile);  //openFiles function call
 while(infile >> n){          //reads from the file
   arr[i] = n;
   i++;
 }
  print(arr, outfile);        //very own print function
  outfile.close();  
  infile.close();
}


/**
     * Public : openFiles
     * 
     * Description:
     *      Opens both the input and output file.
     * 
     * Params:
     *      ifstream&   infile
     *      ofstream&   outfile
     * 
     * Returns:
     *      Nothing
     */
void openFiles(ifstream& infile, ofstream& outfile){
  string inFileName;
  string outFileName;

  cout << "Enter the name of the input file: ";
  cin >> inFileName;
  infile.open(inFileName);

  cout << "Enter the name of the output file: ";
  cin >> outFileName;
  outfile.open(outFileName);
}

/**
     * Public : reverseBits
     * 
     * Description:
     *      Reverses the bits of the binary,
     *      shifts right 16 to correct, and returns it
     * 
     * Params:
     *     unsigned int    x
     * 
     * Returns:
     *      revNum, which is the reversed binary number.
     */
unsigned int reverseBits(unsigned int x) {
   unsigned int numBits = sizeof(x) * 8;  
   unsigned int revNum = 0;
   //we loop through the binary of x and find the position of the set bit.
   //then use ((numBits-1)-i) to calculate it.
   for (int i = 0; i < numBits; i++){
      if((x & (1 << i))) //compares x and the shifted i to the left 1
         revNum |= (1 << ((numBits - 1) - i)); //or operation with the bit in the inth pos. 
   }
   revNum = revNum >> 16;
   return revNum;
   }


/**
     * Public : print
     * 
     * Description:
     *      Prints our array of values 
     * 
     * Params:
     *      int*       arr
     *      ofstream   outfile
     * 
     * Returns:
     *      nothing
     */
void print(int* arr,ofstream& outfile){
 outfile << "Blake Gauna\n";
 outfile << "Program 1: Bitwise Operations\n\n";
 outfile << "Number        Reverse\n";
  for (int i = 0; i < 9; i++){
    outfile << " " << right << setw(5) << arr[i] <<  //making things look pretty
   "          " << right << setw(5) << reverseBits(arr[i]); //setw(5) bc our biggest
 /*                                                          number is 5 digits long*/
    outfile << endl;
}
}