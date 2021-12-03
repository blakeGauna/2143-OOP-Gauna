//Blake Gauna
//CMPS 2433
//Program 4 : Combinatorial Teams


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

//prototypes
void openFiles(ifstream&, ofstream&);
int factorial(int x);
void closeFiles(ifstream&, ofstream&);
int combination(int x, int y);
void total(int arr[], ostream& ofile);
void heading(ostream& ofile);


int main() {
  ifstream infile;
  ofstream ofile;
  openFiles(infile, ofile);
  
  string str;
  int arr[100] = {0};              //array to store input
  int i = 0;

  while(!infile.eof()){            //loops while the file hasnt
    infile >> arr[i];              //ended
    i++;
  }

  //cout << factorial(8);         //testing factorial function
  //cout << combination(5,3);       //testing combination function
  heading(ofile);
  total(arr, ofile);
  closeFiles(infile, ofile);
  return 0;
} 

//heading function
void heading(ostream& ofile){
  cout << "Blake Gauna" << endl;
  cout << "Program 4: Combinatorial Teams" << endl;
  ofile << "Blake Gauna" << endl;
  ofile << "Program 4: Combinatorial Teams" << endl;

}

void openFiles(ifstream& infile, ofstream& ofile){  //standard openFiles function
  string inFileName;
  string outFileName;

  cout << "Enter the input file name: ";
  cin>>inFileName;
  infile.open(inFileName);

  cout << "\nEnter the output file name: ";
  cin >> outFileName;
  ofile.open(outFileName);
  cout << endl;
}

//iterative factorial function
int factorial(int x){
  unsigned long long int fact = 1;
  for(int i=1; i<=x; i++){   //loops and multiplies as many times
    fact = fact * i;         //as big as the number is and works
  }                          //just as a factorial works
  return fact;
}

//close file function
void closeFiles(ifstream& infile, ofstream& ofile){
  infile.close();
  ofile.close();
}


int combination(int x, int y){
  int m = 0;
  m = x - y;
  int total = 0;
  //combination formula
  total = (factorial(x)/((factorial(y))*(factorial(m))));
  return total;
}

void total(int arr[], ostream& ofile){
  int n = 0;      //we need these to access 4 numbers
  int a = 1; 
  int b = 2; 
  int d = 3;
  unsigned long long int total = 0;
  int totalArr[7] = {0};
  
  for(int i = 0; i < 7; i++){
   total = (combination(arr[n], arr[a])) * (pow(combination(arr[b], arr[d]), arr[a]));                 //C(n,a)*(C(b,d)^a)
   if (total > 100000){     
     total = total % (1000000007);    //used to get last value
   }
   cout << total << endl;
   ofile << total << endl;
   n += 4;
   a += 4;
   b += 4;
   d += 4;
  }
}