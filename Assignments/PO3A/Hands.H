#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//defining strings to be emojis 
#define ROCK      u8"\U0001F5FB"
#define PAPER     u8"\U0001F4C3"
#define SCISSORS  u8"\U0001F52A"
#define LIZARD    u8"\U0001F438"
#define SPOCK     u8"\U0001F596"

////////////////////////////////////////
//  Class Hands:
//      Defines different options for
//      the player to have as weapons
//      then turns them into emojis.
//      Also randomly generates a random
//      hand.
////////////////////////////////////////

class Hands {
  public:
    const string rock = ROCK;        //The different options for the hands
    const string paper = PAPER;
    const string scissors = SCISSORS;
    const string lizard = LIZARD;
    const string spock = SPOCK;
    
    std::string arr[5] = {ROCK, PAPER, SCISSORS, LIZARD, SPOCK}; //loads the choices into an 
                                                                 //array so that we can use rand
    static std::string Rock() {
        return ROCK;
    }
    static std::string Paper() {
        return PAPER;
    }
    static std::string Scissors() {
        return SCISSORS;
    }
    static std::string Lizard() {
        return LIZARD;
    }
    static std::string Spock() {
        return SPOCK;
    }

    
     /**
     * Public :         RandHand
     * 
     * Description:
     *                  Returns a random emoji
     * 
     * Params:          
     *                  None
     * 
     * Returns:
     *                  a random number 0 - 5
     */
     
    string RandHand(){
      return arr[rand()%5];
    }
    
     /**
     * Public :         Heading
     * 
     * Description:
     *                  Prints heading to console
     * 
     * Params:          None     
     * 
     * Returns:
     *                  None
     */

    void heading(){
      std::cout << "Welcome to Rock Paper Scissors Lizard Spock!" << endl;
      std::cout << "--------------------------------------------" << endl;
      std::cout << "    " << "Player 1:" << "             " << "Player 2: " << endl;
    }
};

//////////////////////////////////////////////////////////////////////////////
//
// Class Name: Player
//         
// Description: This class is a child class to Hands and equips the player
//  with two "weapons" 
//          
// Private Members / Methods:
//  N/A  
//         
// Public Members / Methods:
// string weapon1
// string weapon2
// bool operator>(const Player other)
//      
//
//////////////////////////////////////////////////////////////////////////////

class Player : public Hands{
  public:
    string weapon1;
    string weapon2;
    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player(){
        weapon1 = RandHand();
        weapon2 = RandHand();

        while(weapon2==weapon1){
            weapon2 = Hands::RandHand();
        }
    }

  bool operator>(const Player other){
  //check first weapons return if result found
    if(this->weapon1 == ROCK){
      if(other.weapon1 == SCISSORS || other.weapon1 == LIZARD){
        //this wins
        return true;
      }
    }
    else if(this->weapon1 == PAPER){
      if(other.weapon1 == ROCK || other.weapon1 == SPOCK){
        //this wins
        return true;
      }
    }
    else if(this->weapon1 == SCISSORS){
      if(other.weapon1 == PAPER || other.weapon1 == LIZARD){
        //this wins
        return true;
      }
    }
    else if(this->weapon1 == LIZARD){
      if(other.weapon1 == SPOCK || other.weapon1 == PAPER){
        //this wins
        return true;
      }
    }
    else if(this->weapon1 == SPOCK){
      if(other.weapon1 == ROCK || other.weapon1 == SCISSORS){
        //this wins
        return true;
      }
    }
  
    //if this.weapon1 doesn't win, check this.weapon2
    if(this->weapon2 == ROCK){
      if(other.weapon2 == SCISSORS || other.weapon2 == LIZARD){
        //this wins
        return true;
      }
    }
    else if(this->weapon2 == PAPER){
      if(other.weapon2 == ROCK || other.weapon2 == SPOCK){
        //this wins
        return true;
      }
    }
    else if(this->weapon2 == SCISSORS){
      if(other.weapon2 == PAPER || other.weapon2 == LIZARD){
        //this wins
        return true;
      }
    }
    else if(this->weapon2 == LIZARD){
      if(other.weapon2 == SPOCK || other.weapon2 == PAPER){
        //this wins
        return true;
      }
    }
    else if(this->weapon2 == SPOCK){
      if(other.weapon2 == ROCK || other.weapon2 == SCISSORS){
        //this wins
        return true;
      }
    }
  
  //if we don't win either, return false
  return false;
  }
  
};
