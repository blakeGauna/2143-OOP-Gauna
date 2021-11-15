#include <iostream>
#include <string>
#include <vector>

#include "dice.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

/**
 * class Weapon
 * 
 * Description:
 *      This class creates a default fist and feet weapon, or generates
        a weapon based on random.
 * 
 * Public Methods:
      string name
      Dice* die
      bool damageAll
      string weaponDesc
      Weapon()
      Weapon(vector< string > choices)
      double use()
      string selectDamage()
      string getName()

 * 
 * Private Methods:
 *      string damage  
 */
class Weapon {
protected:
    string damage;  // damage per roll or "use"
public:
    string name;    // name of weapon
    Dice*  die;
    bool damageAll; //weapon deals damage to every enemy.
    string weaponDesc;
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Weapon() {
        name = "Fists&Feet";
        damage = "1.d.4";
        die = new Dice(damage);
        weaponDesc = " used a weapon that shouldn't exist!";
    }
    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Weapon(vector< string > choices) {
        name = "Fists&Feet";
        damage = randomChoice(choices);
        die = new Dice(damage);
        
    }

    double use() {
        return die->roll();
    }

    string selectDamage(){
      return "";
    };

    friend ostream& operator<<(ostream& os, const Weapon& w) {
        return os << "[" << w.name << " , " << w.damage << "]";
    }

    string getName(){
      return name;
    }
};

/**
 * class Wand : public Weapon
 * 
 * Description:
 *      This class creates a Wand with random damage
 * 
 * Public Methods:
      Wand()
      string selectDamage()  
 */

//1.d.20 OR 2.d.10 OR 3.d.6 OR 5.d.4
class Wand : public Weapon{
  public:
    Wand() {
        name = "Wand";
        damage = selectDamage();
        die = new Dice(damage);
        weaponDesc = " electrocuted a poor soul using their WAND!";
    }
    string selectDamage(){
      string rtn;
      int r = rand()%4;

      switch(r){
        case 0:
          rtn = "1.d.20";
        break;
        case 1:
          rtn = "2.d.10";
        break;
        case 2:
          rtn = "3.d.6";
        break;
        case 3:
          rtn = "5.d.4";
        break;
      }

      return rtn;
    }
};

/**
 * class NapalmStaff : public Weapon
 * 
 * Description:
 *      This class creates a Napalm Staff with random damage
 * 
 * Public Methods:
      NapalmStaff()
      string selectDamage()  
 */

class NapalmStaff : public Weapon{
  public:
    NapalmStaff() {
        name = "Staff of Napalm";
        damage = "4.d.6";
        die = new Dice(damage);
        damageAll = true;
        weaponDesc = " incinerated the entire enemy team using their STAFF OF NAPALM!";
    }
    string selectDamage(){
      return "";
    }
};

/**
 * class Sword : public Weapon
 * 
 * Description:
 *      This class creates a Sword with random damage
 * 
 * Public Methods:
      Sword()
      string selectDamage()  
 */
class Sword : public Weapon{
  public:
    Sword() {
        name = "Sword";
        damage = selectDamage();
        die = new Dice(damage);
        weaponDesc = " slashed the enemy using their SWORD!";
    }
    //1.d.12 OR 2.d.6 OR 3.d.4
    string selectDamage(){
      string rtn;
      int r = rand()%3;

      switch(r){
        case 0:
          rtn = "1.d.12";
        break;
        case 1:
          rtn = "2.d.6";
        break;
        case 2:
          rtn = "3.d.4";
        break;
      }

      return rtn;
    }
};

/**
 * class Excalibur : public Weapon
 * 
 * Description:
 *      This class creates an Excalibur with random damage
 * 
 * Public Methods:
      Excalibur()
      string selectDamage()  
 */
class Excalibur : public Weapon{
  public:
    Excalibur() {
        name = "Excalibur";
        damage = "2.d.8";
        die = new Dice(damage);
        weaponDesc = " claimed glory using EXCALIBUR!";
    }
    string selectDamage(){
      return "";
    }
};

/**
 * class SneakyKnife : public Weapon
 * 
 * Description:
 *      This class creates a SneakyKnife with random damage
 * 
 * Public Methods:
      SneakyKnife()
      string selectDamage()  
 */
class SneakyKnife : public Weapon{
  public:
    SneakyKnife() {
        name = "Sneaky Knife";
        damage = selectDamage();
        die = new Dice(damage);
        weaponDesc = " sneakily stabbed with their SNEAKY KNIFE!";
    }
    //1.d.12 OR 2.d.6 OR 3.d.4
    string selectDamage(){
      string rtn;
      int r = rand()%3;

      switch(r){
        case 0:
          rtn = "1.d.12";
        break;
        case 1:
          rtn = "2.d.6";
        break;
        case 2:
          rtn = "3.d.4";
        break;
      }

      return rtn;
    }
};

/**
 * class MehrunesRazor : public Weapon
 * 
 * Description:
 *      This class creates a Mehrunes Razor with random damage
 * 
 * Public Methods:
      MehrunesRazor()
      string selectDamage()  
 */

class MehrunesRazor : public Weapon{
  public:
    MehrunesRazor() {
        name = "Mehrune's Razor";
        damage = "2.d.20";
        die = new Dice(damage);
        weaponDesc = " created a widow with MEHRUNE'S RAZOR!";
    }
    string selectDamage(){
      return "";
    }
};

/**
 * class Bow : public Weapon
 * 
 * Description:
 *      This class creates a Bow with random damage
 * 
 * Public Methods:
      Bow()
      string selectDamage()  
 */

//1.d.8 OR 2.d.4 OR 1.d.10
class Bow : public Weapon{
  public:
    Bow() {
        name = "Bow";
        damage = selectDamage();
        die = new Dice(damage);
        weaponDesc = " 360 no scoped their foe with their BOW";
    }
    string selectDamage(){
      string rtn;
      int r = rand()%3;

      switch(r){
        case 0:
          rtn = "1.d.8";
        break;
        case 1:
          rtn = "2.d.4";
        break;
        case 2:
          rtn = "1.d.10";
        break;
      }

      return rtn;
    }
};

/**
 * class KillerBow : public Weapon
 * 
 * Description:
 *  class is used for archer upgraded attack
 * 
 * Public Methods:
 *    KillerBow()
 *    string selectDamage()   
 * 
 * Private Methods:
 *     
 *    
 */

class KillerBow : public Weapon{
  public:
    KillerBow() {
        name = "KillerBow";
        damage = selectDamage();
        die = new Dice(damage);
        damageAll = true;
        weaponDesc = " buried the entire enemy team under a volley of arrows using KILLER BOW!";
    }
    string selectDamage(){
      string rtn;
      int r = rand()%3;

      switch(r){
        case 0:
          rtn = "1.d.8";
        break;
        case 1:
          rtn = "2.d.4";
        break;
        case 2:
          rtn = "1.d.10";
        break;
      }

      return rtn;
    }
};

/**
 * class Breath : public Weapon
 * 
 * Description:
 *  class is used for dragonborn standard attack
 * 
 * Public Methods:
 *    Breath()
 *    string selectDamage()   
 * 
 * Private Methods:
 *     
 *    
 */

class Breath : public Weapon{
  public:
    Breath() {
        name = "Breath";
        damage = selectDamage();
        die = new Dice(damage);
        weaponDesc = " breathed a gout of flame disintegrating the enemy with their BREATH!";
    }
    string selectDamage(){
      string rtn;
      int r = rand()%2;
      switch(r){
        case 0:
          rtn = "1.d.6";
        break;
        case 1:
          rtn = "1.d.8";
        break;
      }

      return rtn;
    }
};

/**
 * class Shout : public Weapon
 * 
 * Description:
 *  class is used for dragonborn upgraded attack
 * 
 * Public Methods:
 *    Shout()
 *    string selectDamage()   
 * 
 * Private Methods:
 *      
 *    
 */

class Shout : public Weapon{
  public:
    Shout() {
        name = "Shout";
        damage = selectDamage();
        die = new Dice(damage);
        damageAll = true;
        weaponDesc = " unrelenting force knocked out the entire enemy team using their SHOUT";
    }
    string selectDamage(){
      string rtn;
      int r = rand()%2;
      switch(r){
        case 0:
          rtn = "1.d.6";
        break;
        case 1:
          rtn = "1.d.8";
        break;
      }

      return rtn;
    }
};

/**
 * class Magic : public Weapon
 * 
 * Description:
 *  class is used to add damage to each attacker and defender
 * 
 * Public Methods:
 *    Magic()
 *    string selectDamage()
 *  
 * 
 * Private Methods:
 *     
 *    
 */

class Magic : public Weapon{
  public:
    Magic() {
        name = "Magic";
        damage = selectDamage();
        die = new Dice(damage);
        damageAll = true;
    }
    string selectDamage(){
      string rtn;
      int r = rand()%2;

      switch(r){
        case 0:
          rtn = "1.d.4";
        break;
        case 1:
          rtn = "1.d.6";
        break;
      }

      return rtn;
    }
};