// Ben Leber
// 11/3/2025
// DND Character Creator using JSON format output
// Made while my friends were playing PlateUp, cus we needed to make dnd characters 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include "character.hpp"

using std::endl; using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::min_element; using std::accumulate; using std::generate; using std::for_each;
using std::map; using std::multimap;

int rollDice(const int&, const int&);

int main() {
    // RANDOM SEED!!!!
    srand(time(nullptr));
    int decision;
    string name;
    Character player;

    vector<string> pRace = {"Human", "Elf", "Dwarf", "Halfling", "High Elf", "Gnome", "Shadowkind", "Dragonborn", "Half Orc", "Tiefling"};
    vector<string> pClass = {"Wizard", "Barbarian", "Cleric", "Fighter", /*"Rogue",*/ "Bard", "Ranger", "Paladin", "Druid", "Warlock", "Sorcerer", "Monk"};
    vector<string> pAlignmentX = {"Lawful", "Neutral", "Chaotic"};
    vector<string> pAlignmentY = {"Good", "Neutral", "Evil"};

    // TODO: Create weapons
    // TODO: Create spells
    // TODO: Create armor

    cout << "Welcome to the Character Creator v0.1.2!!!! [ONESHOT EDITION]" << endl;
    cout << "How would you like your character created?" << endl;
    cout << "1. Do it for me twerp" << endl << "2. Manually" << endl << "3. Exit ts!!!" << endl;
    cout << "Your choice: ";
    cin >> decision;

    string race, newClass, alignment, influence;
    unordered_map<string, int> abilityTypes(6);
    vector<string> types = {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};

    // TEST WEAPONS, SPELLS, N WHAT NOT
    // Weapons
    Weapon a("Cool ass fucking sword", 300, 100, 3);
    Weapon b("Lame ass stupid unlovable fucking sword", 0, 4, 1);
    // Spells
    Spell c("Death spell", "Literally just kill your fucking opponent.", 18732, 100, 100);
    Spell d("Fart", "Whoops!!!!! Taco bell actin up!!!!!! EVERYONE LOOK OUT!! (Harmless)", 1, 0, 0);
    // Equipment
    Equipment e1("Buttplug", "its shoved up ur ass.", 1);
    Equipment e2("Stick");

    switch (decision) {
    // auto
    case 1:
        cout << "Please give your character a name before we start: ";
        cin >> name;

        // race, class, alignment
        race = pRace[rand() % pRace.size()];
        newClass = pClass[rand() % pClass.size()];
        alignment = pAlignmentX[rand() % pAlignmentX.size()] + " " + pAlignmentY[rand() % pAlignmentY.size()];
        player.setID(name, race, newClass, alignment, 1, 0);

        // ability scores
        for (int i = 0; i < types.size(); ++i) {
            // 4d6 drop lowest
            int valueSum = 0;
            vector<int> values(4);
            generate(values.begin(), values.end(), []() {return rollDice(6, 0);});
            values.erase(min_element(values.begin(), values.end()));
            valueSum = accumulate(values.begin(), values.end(), 0);

            abilityTypes.insert(std::make_pair(types[i], valueSum));
        }

        // background
        // needs to be done later

        // ill do this later
        // string influence = player.getClass();
        player.setAbilities(abilityTypes);

        // Spells / Spell slots
        // determines if the spells/slots shows up on the player sheet
        if (player.magicAptitude(player.getClass())) {
            player.generateSpells(player);
            player.addSpell(&c); player.addSpell(&d);
        }
 
        // equipment
        player.generateWeapons(player);
        player.addWeapon(&a); player.addWeapon(&b); 
        player.addEquipment(&e1); player.addEquipment(&e2);
        player.generateArmor(player);

        // HP, AC, Attacks
        player.setAttributes();

        // Proficiency

        // Saving Throws

        // Skill Mod

        if (!player.printFile()) {
            cout << "Failed to print to file." << endl;
            exit(1);
        }
        cout << "Output saved to character.txt" << endl;
        cout << "Make any adjustments that you would like!" << endl;
        break;

    // manual
    case 2:
        cout << "Please your character a name before we start: ";
        cin >> name;
        cout << "not ready yet." << endl;
        break;

    // exit
    case 3:
        cout << "Leaving..." << endl;
        exit(0);
        break; 

    default:
        cout << "THATS NOT A DECISION. Deleting C:/system32/..." << endl;
    }


}



int rollDice(const int& sides, const int& adv) {
    return (rand() % sides) + adv + 1;
}