/*Blake Gauna
  2143 Discrete Mathematics
  Program 2: Squares
  
  
  This program will calculate the amount of squares there are on
a n x n grid of squares.


*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int Closed(int &num);                                        //closed form solution
int RecSoln(int num);                                        //unfinished recursive solution
int LoopSum(int &num);                                       //loop sum function
void openFiles(ifstream& infile, ofstream& ofile);           //print function
void heading(ofstream& ofile);                               //heading function


int main() {
  ifstream infile;
  ofstream ofile;
  int k;
  int c = 0;
  int num;
  int num2;
  int n, m, o, p = 0;
  
  int arr[] = {10, 1, 2, 3 ,7, 14};
  int *arr2 = new int[5];

  openFiles(infile, ofile);
  heading(ofile);

  while(infile >> k){                      //reads from the file and stores in array
   arr2[c] = k;
   c++;
 }
 
  for(int i = 0; i < 5; i++){             //for loop in main for input file
    o = arr2[i];
    p = arr2[i];
    cout << left << setw(6) << o;         //iomanip
    ofile << left << setw(6) << o;        //iomanip
    LoopSum(p); 
    cout << left << setw(6) << p << "     ";        //iomanip
    ofile << left << setw(6) << p << "     ";       //iomanip
    Closed(o);
    cout << o << endl;
    ofile << o << endl;
  }

cout << endl;
ofile << endl;

  for(int i = 0; i < 6; i++){             //for loop for our regular test cases
    n = arr[i];
    m = arr[i]; 
    cout << left << setw(6) << n;         //iomanip
    ofile << left << setw(6) << n;        //iomanip
    LoopSum(m);  
    cout << left << setw(6) << m << "     ";     //iomanip
    ofile << left << setw(6) << m << "     ";    //iomanip
    Closed(n);
    cout << n << endl;
    ofile << n << endl;
  }

  ofile.close();
  return 0;
}

void heading(ofstream& ofile){
  cout << endl << "Blake Gauna\n";
  cout << "Program 2: Squares\n\n";
  cout << "N" << "   " << "LoopSum" << "     " << "Closed\n";
  ofile << endl << "Blake Gauna\n";
  ofile << "Program 2: Squares\n\n";
  ofile << "N" << "   " << "LoopSum" << "     " << "Closed\n";
}

void openFiles(ifstream& infile, ofstream& ofile){   
  string inFileName;
  string outFileName;

  cout << "Enter the name of the input file: ";
  cin >> inFileName;
  infile.open(inFileName);

  cout << endl << "Enter the name of the output file: ";
  cin >> outFileName;
  ofile.open(outFileName);
}

int LoopSum(int &num){
  int x = num;
  num = 0;
  for(int i = 1; i <= x; i++){   //We start at 1
    num += (i*i);                //For num = 3, num = (3 x 3) +
                                 // (2 x 2) + (1 x 1) = 14
  }
  return num;
};

int RecSoln(int num){
  int result = num;
  if (num == 1){
    return 1;
  }
  else{
    
    return result * RecSoln(result - 1);
  }
  
}

int Closed(int &num){
  int x = num;
  num = ((x*(x+1)*(2*(x)+1)))/6;  //closed form solution
  return num;
};