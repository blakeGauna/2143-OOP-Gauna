/*Blake Gauna
  CMPS-2433

  Description: This program will take your input and find the 
  maximum activities you can do in that time period.
*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//struct to help store data
struct Schedule{
  int s_time;
  int f_time;
  int length;
};

//prototypes
void openFiles(ifstream& infile, ofstream& ofile);
void insertionSort(Schedule table[], int n);
void print(Schedule table[], int a, ofstream& outfile);
void compare(Schedule table[], int a);

int main() {
  int act,n,m= 0;
  int q = 0;
  ifstream infile;
  ofstream ofile;
  
  openFiles(infile, ofile);
  infile>>act;                      //reading # of activities

  Schedule table[act];              //making arrays of type schedule
  Schedule newSch[5];
  
  for(int i = 0; i < act; i++){
    infile>>n;
    infile>>m;
    table[i].s_time = n;            //calculating end times
    table[i].length = m;
    table[i].f_time = table[i].s_time + table[i].length;
  }
  
  insertionSort(table, act);        //calling sort
  compare(table, act);
  while(table[q].f_time < table[q+1].f_time){   //comparing final times to 
    newSch[q].s_time = table[q].s_time;         //compute which ones to print
    newSch[q].length = table[q].length;
    newSch[q].f_time = table[q].f_time;
    q++;
  }
  print(newSch, q, ofile);
  return  0; 
  infile.close();
  ofile.close(); 
} 

void openFiles(ifstream& infile, ofstream& ofile){  //standard openFiles function
  string inFileName;
  string outFileName;

  cout << "Enter the input file name: ";
  cin>>inFileName;
  infile.open(inFileName);

  cout << "\nEnter the output file name: ";
  cin >> inFileName;
  ofile.open(outFileName);
}

void compare(Schedule table[], int a){
  Schedule newSch[5];
  int min;
  int m = 0;
  newSch[0].s_time = table[0].s_time;         //we sorted the list, so the first
  newSch[0].length = table[0].length;         //element should be "initialized"
  newSch[0].f_time = table[0].f_time;
  for(int i = 1; i <= a; i++){
    if(table[i].s_time >= newSch[m].f_time){  //pushing the values to a new
      newSch[m+1].s_time = table[i].s_time;   //array
      newSch[m+1].length = table[i].length;
      newSch[m+1].f_time = table[i].f_time;
      m++;
    }
  }
  
  for(int i = 0; i <= m + 1 ; i++){
    table[i].s_time = newSch[i].s_time;       //making the old array equal the 
    table[i].length = newSch[i].length;       //new values of the new array
    table[i].f_time= newSch[i].f_time;
  }

}

void print(Schedule table[], int a, ofstream &ofile){
    cout << "\n\nBlake Gauna\n";
    cout << "Program 3: Greedy Algorithms/Sorting Problem\n\n";
    cout << "Start Time    Length    Finish Time\n";
    ofile << "\n\nBlake Gauna\n";
    ofile << "Program 3: Greedy Algorithms/Sorting Problem\n\n";
    ofile << "Start Time    Length    Finish Time\n";
  for(int i = 0; i < a; i++){
    cout << left << setw(14) <<  table[i].s_time << left << setw(10) << table[i].length << left << setw(10) << table[i].f_time << endl;
    ofile << left << setw(14) <<  table[i].s_time << left << setw(10) << table[i].length << left << setw(10) << table[i].f_time << endl;
  }
  cout << "\nMaximum number of activities scheduled is " << a << endl;
  ofile << "\nMaximum number of activities scheduled is " << a << endl;
}


void insertionSort(Schedule table[], int n){
  int i, key, j;
  for (i = 1; i < n; i++){
    key = table[i].f_time;
    j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
    while (j >= 0 && table[j].f_time > key)
      {
        swap(table[j + 1],table[j]);
        j = j - 1;

            
      }
     table[j + 1].f_time = key;
  }
  
}
