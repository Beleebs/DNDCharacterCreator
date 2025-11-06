#ifndef DND_CHARACTER
#define DND_CHARACTER

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

using std::string; using std::multimap; using std::map; using std::vector; using std::pair;
using std::unordered_map;

enum WeaponProficiency {
    SIMPLE,
    MARTIAL
};

class Weapon {
public:
    Weapon(string name="test", int extraDamage=1, int hitDice=1, int numOfDice=1) : name_(name), extraDamage_(extraDamage), hitDice_(hitDice), numOfDice_(numOfDice) {}
    string print();

private:
    string name_;
    int extraDamage_;
    int hitDice_;
    int numOfDice_;
};

class Spell {
public:
    Spell(string name="test", string desc="this is a spell", int level=1, int hitDice=1, int numOfDice=1) : name_(name), desc_(desc), level_(level), hitDice_(hitDice), numOfDice_(numOfDice) {}
    string print();
    int getLevel() {return level_;}

private:
    string name_;
    string desc_;
    int level_;
    int hitDice_;
    int numOfDice_;
};

class Armor {
public:
    Armor(string name="test", string type="Light", int AC=12) : name_(name), type_(type), AC_(AC) {}
    string print();
    int getAC_() {return AC_;}

private:
    string name_;
    string type_;
    int AC_;
};

class Equipment {
public:
    Equipment(string name="test", string desc="this is an item", int count=1) : name_(name), desc_(desc), count_(count) {}
    string print();

private:
    string name_;
    string desc_;
    int count_;
};

class Character {
public:
    Character() : name_(""), race_(""), pClass_(""), alignment_(""), background_(""), LVL_(1), EXP_(0), HP_(0), AC_(0), INIT_(0), SDC_(0), castsMagic_(false) {}

    // identifiers
    void setID(const string& name, const string& race, const string& pClass, const string& alignment, const int& LVL, const int& EXP);
    // ability scores and modifiers
    void setAbilities(const unordered_map<string, int>& values);
    // hp, ac, advantage
    void setAttributes(); 
    // set spell manually
    void addSpell(Spell* s);
    // set weapons manually
    void addWeapon(Weapon* w);
    // set armor manually
    void addArmor(Armor* a);
    // set equipment manually
    void addEquipment(Equipment* e);

    // gets the classname
    // adds influence to ability scores (favors specific classes abilities over others)
    // additionally, determines magic aptitude
    string getClass() const;

    // determines magic aptitude
    bool magicAptitude(const string& classType);

    // generates weapon/armor equipment based on class type
    void generateWeapons(Character&);
    void generateArmor(Character&);
    void generateSpells(Character&);

    // prints to a file
    bool printFile();

    // prints to console
    void printConsole();

private:
    // Character Identification
    string name_;
    string race_;
    string pClass_;
    string alignment_;

    // Other Identification (used for skill modifiers)
    string background_;

    // Player Level, EXP, HP, Armor Class, Initiative, Spell DC
    int LVL_;
    int EXP_;
    int HP_;
    int AC_;
    int INIT_;
    int SDC_;
    
    // Character Special Abilities:
    // Can they cast magic? Can they use this weapon? etc.
    bool castsMagic_;

    // Ability scores
    // Ability <value, mod>
    unordered_map<string, pair<int, int>> abilityScores_;

    // Weapons
    // name & additional damage, damage dice & number of dice
    vector<Weapon> weaponInv_;

    // Armor
    // name, armor value
    Armor armor_;

    // Spells
    // name & level, damage dice & # of dice
    vector<Spell> spells_;

    // Spell Slots
    // level, number of slots
    map<int, int> slots_;

    // regular inventory
    // item name, desc, count
    vector<Equipment> inv_;
};



#endif