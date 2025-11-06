#include "character.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using std::endl; using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::map; using std::multimap;
using std::unordered_map;
using std::ofstream;
using std::pair; using std::make_pair;

using std::for_each;
using std::generate;

void Character::setID(const string& name, const string& race, const string& pClass, const string& alignment, const int& LVL, const int& EXP) {
    name_ = name;
    race_ = race;
    pClass_ = pClass;
    alignment_ = alignment;
    LVL_ = LVL;
    EXP_ = EXP;
}

void Character::setAbilities(const unordered_map<string, int>& values) {
    // goes in order STR, DEX, CON, INT, WIS, CHA
    for_each(values.begin(), values.end(), [&](pair<string, int> v) {
        // calculates ability modifier
        int mod;
        if (v.second <= 3) {
            mod = -4;
        }
        else if (v.second > 3 && v.second <= 5) {
            mod = -3;
        }
        else if (v.second > 5 && v.second <= 7) {
            mod = -2;
        }
        else if (v.second > 7 && v.second <= 9) {
            mod = -1;
        }
        else if (v.second > 9 && v.second <= 11) {
            mod = 0;
        }
        else if (v.second > 11 && v.second <= 13) {
            mod = 1;
        }
        else if (v.second > 13 && v.second <= 15) {
            mod = 2;
        }
        else if (v.second > 15 && v.second <= 17) {
            mod = 3;
        }
        else if (v.second > 17 && v.second <= 19) {
            mod = 4;
        }
        else if (v.second >= 20) {
            mod = 5;
        }

        abilityScores_.insert(make_pair(v.first, make_pair(v.second, mod)));
    });
}

void Character::setAttributes() {
    // do something with this later
}

void Character::addWeapon(Weapon* w) {weaponInv_.push_back(*w);}
void Character::addSpell(Spell* s) {
    spells_.push_back(*s);
    // need to change this later
    slots_.insert(make_pair(s->getLevel(), 5));
}
void Character::addArmor(Armor* a) {armor_ = *a;}
void Character::addEquipment(Equipment* e) {inv_.push_back(*e);}

bool Character::printFile() {
    // creates character sheet
    ofstream sheet("character.txt");
    
    // make sure its open!!!!!
    if (!sheet.is_open()) {
        cout << "could not write to character.txt" << endl;
        return false;
    }

    // print ID
    sheet << "Character Name: " << name_ << endl;
    sheet << "Race: " << race_ << endl;
    sheet << "Class: " << pClass_ << " " << LVL_ << endl;
    sheet << "Alignment: " << alignment_ << endl; 
    sheet << "Background: " << background_ << endl;
    sheet << "Experience Points: " << EXP_ << endl;
    sheet << endl;

    // attributes
    sheet << "HP: " << HP_ << endl;
    sheet << "AC: " << AC_ << endl;
    sheet << "Initiative: " << INIT_ << endl;
    sheet << endl;

    // ability scores
    sheet << "Abilities: " << endl;
    for_each(abilityScores_.begin(), abilityScores_.end(), [&](pair<string, pair<int, int>> ab) {
        sheet << ab.first << ": " << ab.second.first << " (Modifier: ";
        if (ab.second.second > 0) {
            sheet << "+" << ab.second.second << ")" << endl;
        }
        else {
            sheet << ab.second.second << ")" << endl;
        }
    });
    sheet << endl;

    // weapons
    sheet << "Weapons: " << endl;
    for_each(weaponInv_.begin(), weaponInv_.end(), [&](Weapon w){ sheet << w.print() << endl;});
    sheet << endl;

    // armor
    // TODO:
    // checks for shield
    sheet << "Armor Equipped: " << endl;
    sheet << armor_.print() << endl;
    sheet << endl;

    // spells
    if (castsMagic_) {
        // actual spells
        sheet << "Spells: " << endl;
        for_each(spells_.begin(), spells_.end(), [&](Spell s) {sheet << s.print() << endl;});
        sheet << endl;

        // spell slots
        sheet << "Spell Slots: " << endl;
        for_each(slots_.begin(), slots_.end(), [&](pair<int, int> w) {
            sheet << "Level " << w.first << ": " << w.second << endl;
        });
        sheet << endl;
    }

    // inventory
    sheet << "Inventory: " << endl;
    for_each(inv_.begin(), inv_.end(), [&](Equipment e) {sheet << e.print() << endl;});
    sheet << endl;
    return true;
}

void Character::printConsole() {
    cout << "hello" << endl;
}

string Character::getClass() const {
    return pClass_;
}

bool Character::magicAptitude(const string& classType) {
    if (classType == "Barbarian" || classType == "Fighter" || classType == "Rogue" || classType == "Monk") {
        castsMagic_ = false;
        return false;
    }
    castsMagic_ = true;
    return true;
}

vector<Weapon>* compatibleWeapons(const Character& c) {
    return nullptr;
}

void Character::generateWeapons(Character& c) {
    string classType = c.getClass();
    int numOfWeapons = (rand() % 2) + 1;
    cout << "Gets " << numOfWeapons << " weapon(s)." << endl;
}

void Character::generateArmor(Character& c) {
    string classType = c.getClass();
    if (classType == "Monk" || classType == "Sorcerer" || classType == "Wizard") {
        cout << "No armor." << endl;
        c.addArmor(new Armor("None", "None", 10));
    }
    else {
        if (classType == "Bard" || classType == "Rogue" || classType == "Warlock") {
            cout << "Light Armor only." << endl;
        }
        else {
            if (classType == "Barbarian" || classType == "Cleric" || classType == "Druid" || classType == "Ranger") {
                cout << "Light/Medium Armor + Shields" << endl;
            }
            else {
                cout << "Any Armor + Shields" << endl;
            }
        }
    }
}

void Character::generateSpells(Character& c) {
    string classType = c.getClass();
    // magic types: Arcane, Nature, Divine, Pact
    // Arcane:
    if (classType == "Bard" || classType == "Sorcerer" || classType == "Wizard") {
        cout << "uses Arcane magic." << endl;
    }
    // Divine
    else if (classType == "Cleric" || classType == "Paladin") {
        cout << "uses Divine magic." << endl;
    }
    // Nature
    else if (classType == "Druid" || classType == "Ranger") {
        cout << "uses Nature magic." << endl;
    }
    // Pact
    else if (classType == "Warlock") {
        cout << "uses Pact magic." << endl;
    }
}

// print functions for the different item types

string Weapon::print() {
    string message = name_ + "\n\t- Hit Dice: " + std::to_string(numOfDice_) + "d" + std::to_string(hitDice_);
    if (extraDamage_ > 0) {
        message = message + "+" + std::to_string(extraDamage_);
    }
    else if (extraDamage_ < 0) {
        message = message + std::to_string(extraDamage_);
    }
    return message;
}

string Spell::print() {
    string message = name_ + " [Level: " + std::to_string(level_) + "]" + "\n\t- " + desc_; 
    if (hitDice_ != 0 && numOfDice_ != 0) {
        message = message + "\n\t- Damage: " + std::to_string(numOfDice_) + "d" + std::to_string(hitDice_);
    }
    return message;
}

string Armor::print() {
    string message = name_;
    if (type_ != "None") {
        message = message + "\n\t- " + type_ + "\n\t- AC: " + std::to_string(AC_);
    }
    return message;
}

string Equipment::print() {
    string message = name_ + " (Count: " + std::to_string(count_) + ")"+ "\n\t- " + desc_;
    return message;
}
