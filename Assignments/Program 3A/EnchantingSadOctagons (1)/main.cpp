//////////////////////////////////////////////////////////////////////////////
//
// Author:           Aodhan Shaw, Alex Ryan, Blake Gauna, Joshua Beaty
// Title:            P03A
// Course:           2143
// Semester:         Fall 2021
//
// Description:
//    Program that play RPSLS by using a parent class "hands" and child class
//    "player" to randomly pick the different options of the game 25 times
//
//////////////////////////////////////////////////////////////////////////////


#include "Hands.H"
#include <fstream>
//prototype for compare
void compare(Player, Player, ofstream& outfile);

int main() {
ofstream outfile;
outfile.open("output.txt");

  srand(time(0));
  Hands h;
  h.heading();

for (int i = 0; i < 30; i++){
  Player p1; 
  Player p2;
  cout << endl;   
  cout << "    " << "Player 1:" << "             " << "Player 2: " << endl;
  cout << "      " << p1.weapon1 << "                   " << p2.weapon1 << endl;
  cout << "      " << p1.weapon2 << "                   " << p2.weapon2 << endl;

  outfile << endl;   
  outfile << "    " << "Player 1:" << "             " << "Player 2: " << endl;
  outfile << "      " << p1.weapon1 << "                   " << p2.weapon1 << endl;
  outfile << "      " << p1.weapon2 << "                   " << p2.weapon2 << endl;

  compare(p1, p2, outfile);
}

  return 0;
}

    /**
     * Public : compare
     * 
     * Description:
     *      compares 2 emojies as if it were a rock, paper, scissors game
     * 
     * Params:
     *      Player    :  p1
     *      Player    :  p2
     *      ofstream& :  outfile
     * 
     * Returns:
     *      None
     */
void compare(Player p1, Player p2, ofstream& outfile) {
      //if weapons aren't equal check the comparisons   
    if(p1.weapon1 != p2.weapon1){
      //doweapons aren't equal, compare p1 to p2, if p1 wins at all, print out the output.     
      if(p1>p2){
        cout << "Player 1's " << p1.weapon1 << " or " << p1.weapon2 << " beats Player 2's " << p2.weapon1 << " or " << p2.weapon2 << '\n';
        outfile << "Player 1's " << p1.weapon1 << " or " << p1.weapon2 << " beats Player 2's " << p2.weapon1 << " or " << p2.weapon2 << '\n';
      }
      else if(p2>p1){
        cout << "Player 2's " << p2.weapon1 << " or " << p2.weapon2 << " beats Player 1's " << p1.weapon1 << " or " << p1.weapon2 << '\n';
        outfile << "Player 2's " << p2.weapon1 << " or " << p2.weapon2 << " beats Player 1's " << p1.weapon1 << " or " << p1.weapon2 << '\n';
      }
      else {
        cout << "error, weird case found\n";
        outfile << "error, weird case found\n";
      }
    }
    else {
      //they're equal
      if(p1.weapon2 != p2.weapon2){
        //2nd weapons not equal declare winner
        if(p1>p2){
          cout << "Player 1's " << p1.weapon2 << " beats Player 2's " << p2.weapon2 << '\n';
          outfile << "Player 1's " << p1.weapon2 << " beats Player 2's " << p2.weapon2 << '\n';
        }
        else if(p2>p1){
          cout << "Player 2's " << p2.weapon2 << " beats Player 1's " << p1.weapon2 << '\n';
          outfile << "Player 2's " << p2.weapon2 << " beats Player 1's " << p1.weapon2 << '\n';
        }
        else{ 
          cout << "error, weird case found\n";
          outfile << "error, weird case found\n";
        }
      } 

      else
        cout << "It's a tie!\n";   //they're equal again
        outfile << "It's a tie!\n";
    }
}


