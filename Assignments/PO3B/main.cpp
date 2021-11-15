/*****************************************************************************
*                    
*  Author:           Blake Gauna, Joshua Beaty, ALexander Ryan, Aohdan Shaw
*  Email:            blakegauna@yahoo.com
*  Label:            PO3B
*  Title:            Fight Club
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*         This program creates the appropriate number of characters based on the input  and proceeds to manage battles between attackers and defenders choosing the appropriate character to fight based on the above rules. It uses run time polymorphism to switch between attacking characters and defending characters. When the attacking or defending queues become empty, the battle is over and the side with characters remaining wins.
*        
*  Usage: 
*       - Input file if wanted
*       
*  Files:            
*       main.cpp     : driver program 
        dice.hpp     : rolls die based on which dice
        fighter.hpp  : file to hold our fighters
        helpers.hpp  : way to split our string into array indicies
        weapon.hpp   : file to hold our weapons
        input        : input file with attackers
        output       : output file with final stats
        debug        : debug mode
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>
#include <algorithm>
#include "fighter.hpp"
#include "dice.hpp"
#include "helpers.hpp"
#include "weapon.hpp"

using namespace std;

//SET TO TRUE TO USE AN INPUT FILE FROM THE COMMAND LINE
//When true, processes battle based on an input file.
bool commandLineProcessing = false;

//When true, outputs extra info to debug file.
bool debugMode = true;

//Initialize global file processors
ofstream debug;
ofstream fout;

struct BattleStats{
  int roundCount;
  int attWin;
  int defWin;
  int totalAttackers;
  int totalDefenders;
  vector<BaseFighter*> attackers;
  vector<BaseFighter*> defenders;
  vector<BaseFighter*> expired;

  BattleStats(){
    if(debugMode)
      if(debug.is_open())
        debug << "==Battle Stats struct created==\n";
    int roundCount = 0;
    int attWin = 0;
    int defWin = 0;
    int totalAttackers = 0;
    int totalDefenders = 0; 
  }
};



//Function Prototypes
void updateBar();
double calculatePercentage(double t, double b);
void processDamage();
void processHeal();
void generateSides();
void generateDefenders();
BaseFighter* pickClass(int);
BaseFighter* pickClass(string);
void swapChar();
void finalScreen();
void lowerCase(string);
void finalArt();
void battleArt();
BattleStats stats;


//Main driver of battle simulator
//NOTE: commandLineProcessing must be TRUE to read input from a file
//otherwise attacker list size will be prompted 
//and unit type will be auto generated
int main() {
  //open files
  fout.open("output");
  debug.open("debug.out");

  //initialize variables
  int screenUpdate = 25;

  //seed the random
  srand(time(0));

  //read file or prompt user
  if(commandLineProcessing){
    if(debugMode)
      debug << "==cmd processing = true==\n";
    string input;
    //read every line from the input file
    while(cin >> input){
      //create temp for base fighter
      BaseFighter* tempFighter;
      //string to lower
      transform(input.begin(), input.end(), input.begin(), ::tolower);;
      //set temp fighter
      tempFighter = pickClass(input);
      //add to attacker list
      stats.attackers.push_back(tempFighter);
      //increase totalAttackers
      stats.totalAttackers++;
    }
    //generate 1 of each defend for every 100 attackers
    generateDefenders();
  }
  else{
    if(debugMode)
      debug << "==cmd processing = false==\n";
  cout << "How many attackers would you like? " << endl;
  cin >> stats.totalAttackers;
  generateSides();
  }

  if(debugMode){
    debug << "==Attackers and Defenders list generated==\n";
    debug << "\tAttackers.size(): " << stats.attackers.size() << '\n';
    debug << "\tAttackers: " << stats.totalAttackers << '\n';
    debug << "\tDefenders.size(): " << stats.defenders.size() << '\n';
    debug << "\tDefenders: " << stats.totalDefenders << '\n';
  }

  // GAME LOOP
  while(stats.attackers.size() && stats.defenders.size()){
    if(debugMode)
      debug << "==Main Game Loop Started==\n";
    //sub game loop
    while(stats.attackers.back()->alive() && stats.defenders.back()->alive()){
      if(debugMode)
        debug << "\t==Round " << stats.roundCount << " Started==\n";
      this_thread::sleep_for(chrono::milliseconds(screenUpdate));
      system("clear");
      updateBar();
      processDamage();
      battleArt();
      processHeal();
      if (stats.defenders.back()->getCurrenthp() < (stats.defenders.back()->getMaxhp()%2)) {
        swapChar();
      }
      stats.roundCount++; 
    }
    if(!stats.attackers.back()->alive()){
      BaseFighter* temp = stats.attackers.back();
      stats.attackers.pop_back();
      stats.expired.push_back(temp);
      stats.defWin++;
    }
    if(!stats.defenders.back()->alive()){
      BaseFighter* temp = stats.defenders.back();
      stats.defenders.pop_back();
      stats.expired.push_back(temp);
      stats.attWin++;
    }
    
  }
  system("clear");
  finalScreen();
  fout.close();
  debug.close();
} 

//Function prints out a ascii status bar based on
//the remaining fighters of each side.
void updateBar(){
  if(debugMode)
      debug << "\t\tUpdate Bar\n";
  int a = (20*calculatePercentage(stats.attackers.size(), stats.totalAttackers));
  int d = (20*calculatePercentage(stats.defenders.size(), stats.totalDefenders));

  cout << left << setw(23) << "Attackers: " << left << setw(20) << "Defenders: " << '\n';
  cout << left << setw(20) << string(a+1, '@') << " - " << right << setw(20) << string(d+1, '&') << '\n';
}


//function takes in 2 ints and returns a double
double calculatePercentage(double t, double b){
  double rtn = t/b;
  if(debugMode)
      debug << "\t\t\tCalculate Percentage: " << setprecision(2) << rtn << "\n";
  return rtn;
}

void processDamage(){
  if(debugMode)
      debug << "\t\tprocessDamage\n";
  stats.defenders.back()->takeDamage(stats.attackers.back()->attack());
  //this line prevents lots of repeated cout lines.
  int defendDamage = stats.defenders.back()->attack();
  if(debugMode)
      debug << "\t\t\tDefender Damage: " << defendDamage << "\n";
  //if defender's weapon attacks everyone, damage all attackers
  if(stats.defenders.back()->weapon->damageAll)
    //for every attacker in the list
    for(BaseFighter* attacker : stats.attackers)
      //attacker takes the damage.
      attacker->takeDamage(defendDamage);
  else
    stats.attackers.back()->takeDamage(defendDamage);
}

//Function processes regen for current attacker and all defenders.
//Also processes a heal action for the current defender.
void processHeal(){
  //process regen for every defender
  for (int i = 0; i < (stats.defenders.size()-1); i++){
    stats.defenders[i]->regen();
  }
  //process regen for current attacker.
  stats.attackers.back()->regen();
  //process heal action for current defender
  stats.defenders.back()->heal();
}

//Function swaps current defender with another
//defender of the same class.
void swapChar() {
  for (int a = 0; a < stats.defenders.size()-1; a++){
    if(stats.defenders[a]->name == stats.defenders.back()->name) {
    BaseFighter* temp = stats.defenders.back();
    stats.defenders.back() = stats.defenders[a];
    stats.defenders[a] = temp;
    break;
    }
  }
}

//Function takes a number of attackers, a list to put
//the attackers in and a list to put the defenders in.
void generateSides(){
  if(debugMode){
      debug << "\t\tGenerate Sides\n";
  }
  stats.totalDefenders = (stats.totalAttackers/100)*5;

  //randomly generate attackers, every 100 attackers
  //create 1 of every class for defenders
  for(int i = 0; i < stats.totalAttackers; i++){
    //generate temporary fighter
    BaseFighter* temp = pickClass(rand() % 5);
    //then push back
    stats.attackers.push_back(temp);
    if(debugMode){
      debug << "\t\t\tAttackers pushback: " << temp->name << "\n";
    } 
  }
  generateDefenders();
}

void generateDefenders(){
  if(debugMode){
      debug << "\t\tGenerate Defenders\n";
  }
  if(!stats.totalDefenders)
    stats.totalDefenders = 5;

  //generate 1 of each defender for every 100 attackers
  for(int j = 0; j < stats.totalDefenders; j++){
    //generate defender
    BaseFighter* tempDef = pickClass(j%5);
    tempDef->upgradeWeapon();
    //then push back
    stats.defenders.push_back(tempDef);
  }
}


//Function takes a number and returns the basefighter result.
BaseFighter* pickClass(int r){
  BaseFighter* temp;
    if(r == 0){
      temp = new Wizard;
    }
    else if(r == 1){
      temp = new Archer;
    }
    else if(r == 2){
      temp = new Dragonborn;
    }
    else if(r == 3){
      temp = new Warrior;
    }
    else if(r == 4){
      temp = new Elf;
    }
  return temp;
}

BaseFighter* pickClass(string s){
  BaseFighter* temp;
  if(s == "wizard")
    temp = new Wizard;
  else if(s == "warrior")
    temp = new Warrior;
  else if(s == "elf")
    temp = new Elf;
  else if(s == "dragonborn")
    temp = new Dragonborn;
  else if(s == "archer")
    temp = new Archer;

  return temp;
}

void finalScreen(){
  if(stats.attackers.size() > stats.defenders.size()){
    cout << "Attackers Win!" << '\n';
    fout << "Attackers Win!" << '\n';
    cout << "Final Attack: Enemy " << stats.attackers.back()->name << stats.attackers.back()->weapon->weaponDesc << '\n';
    fout << "Final Attack: Enemy " << stats.attackers.back()->name << stats.attackers.back()->weapon->weaponDesc << '\n';
  }
  else{
    cout << "Defenders Win!" << '\n';
    fout << "Defenders Win!" << '\n';
    cout << "Final Attack: Defending " << stats.defenders.back()->name << stats.defenders.back()->weapon->weaponDesc << '\n';
    fout << "Final Attack: Defending " << stats.defenders.back()->name << stats.defenders.back()->weapon->weaponDesc << '\n';
  }
  cout << "Total Numbers of Attackers: " << stats.totalAttackers << '\n';
  fout << "Total Numbers of Attackers: " << stats.totalAttackers << '\n';
  cout << "Total Numbers of Defenders: " << stats.totalDefenders << '\n';
  fout << "Total Numbers of Defenders: " << stats.totalDefenders << '\n';
  cout << "Defenders Remaining: " << stats.defenders.size() << '\n';
  fout << "Defenders Remaining: " << stats.defenders.size() << '\n';
  cout << "Attackers Remaining: " << stats.attackers.size() << '\n';
  fout << "Attackers Remaining: " << stats.attackers.size() << '\n';
  cout << "Number of Rounds Completed: " << stats.roundCount << '\n';
  fout << "Number of Rounds Completed: " << stats.roundCount << '\n';
  cout << "Attackers killed " << stats.attWin << " defenders." << '\n';
  fout << "Attackers killed " << stats.attWin << " defenders." << '\n';
  cout << "Defenders killed " << stats.defWin << " attackers." << '\n';
  fout << "Defenders killed " << stats.defWin << " attackers." << '\n';
  
  //function call for art
  finalArt();                     
}

void lowerCase(string s){
  locale loc;
  for(char c : s){
    if(!islower(c))
      tolower(c,loc);
  }
}

void battleArt(){
      std::cout << R"(                            
             ///~`     |\\_                      =\\\\         . .
            ,  |='  ,))\_| ~-_                    _)  \      _/_/|
           / ,' ,;((((((    ~ \                `~~~\-~-_ /~ (_/\
         /' -~/~)))))))'\_   _/'                      \_  /'  D   |
        (       (((((( ~-/ ~-/                          ~-;  /    \--_
         ~~--|   ))''    ')  `                            `~~\_    \   )
             :        (_  ~\           ,                    /~~-     ./
              \        \_   )--__  /(_/)                   |    )    )|
    ___       |_     \__/~-__    ~~   ,'      /,_;,   __--(   _/      |
  //~~\`\    /' ~~~----|     ~~~~~~~~'        \-  ((~~    __-~        |
((()   `\`\_(_     _-~~-\                      ``~~ ~~~~~~   \_      /
 )))     ~----'(   /      \                                  )       )
  (         ;`~--'        :                                _-    ,;;(
            |    `\       |                             _-~    ,;;;;)
            |    /'`\     ;                          _-~          _/
           /~   /    |    )                         /;;;''  ,;;:-~
          |    /     / | /                         |;;'   ,''
          /   /     |  \\|                         |   ,;(    
        _/  /'       \  \_)                   .---__\_    \,--._______
       ( )|'         (~-_|                   (;;'  ;;;~~~/' `;;|  `;;;\
        ) `\_         |-_;;--__               ~~~----__/'    /'_______/
        `----'       (___`~--_ ~~~;;------------~~~~~ ;;;'_/'
                     `~~~~~~~~'~~~-----....___;;;____---~~     
)" << '\n';
}

void finalArt()
{
    cout << R"(                       
                           ,--.
                          {  / }
                          K,   }
                         /  `Y`
                    _   /   /
                   {_'-K.__/
                     `/-.__L._
                     /  ' /`\_}
                    /  ' /     
            ____   /  ' /
     ,-'~~~~    ~~/  ' /_
   ,'             ``~~~%%',
  (                     %  Y
 {                      %% I
{      -                 %  `.
|       ',                %  )
|        |   ,..__      __. Y
|    .,_./  Y ' / ^Y   J   )|
\           |' /   |   |   ||
 \          L_/    . _ (_,.'(
  \,   ,      ^^""' / |      )
    \_  \          /,L]     /
      '-_`-,       ` `   ./`
         `-(_    |  |  | )
             ^^\.|__|,..-`
)" << '\n';
}