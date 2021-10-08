#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

class Hands {
  public:
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;
    
    string arr[5] = {ROCK2, PAPER2, SCISSORS2, LIZARD2, SPOCK2};

    static string Rock() {
        return ROCK2;
    }
    static string Paper() {
        return PAPER2;
    }
    static string Scissors() {
        return SCISSORS2;
    }
    static string Lizard() {
        return LIZARD2;
    }
    static string Spock() {
        return SPOCK2;
    }
    
    string RandHand(){
      return arr[rand()%5];
    }
};

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
    // other possible methods
};
