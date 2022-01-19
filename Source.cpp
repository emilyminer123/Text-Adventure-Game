#include <iostream>
#include <string>
#include <fstream> 
#include <windows.h>
#include <cstdlib>

using namespace std;

void changeColor(int desiredColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

const int MAX_ITEMS_IN_LOCATION = 5;
const int MAX_ITEMS_ON_CHARACTER = 5;
const string directions[] = { "n","N","s","S","w","W","e","E" };
const string retreat[] = { "e", "east","East","retreat","no" };
const int MAX_Y_COORDINATE = 3;
const int MAX_X_COORDINATE = 3;
const int RED_TEXT_COLOR = 12;
const int BLUE_TEXT_COLOR = 11;
const int WHITE_TEXT_COLOR = 7;


class Item {
public:
	string name;
	string description;
	string lookupName;
};

class Monster {
public:
	string name;
	string description;
	string lookupName;
	int health;

	Monster () {
		health = 10;
	}

	void attack(int health) {
		switch (health) {
		case 9:
			cout << "The harpy looks as though she has taken no damage from your attack." << endl;
			break;
		case 8:
			cout << "The harpy appears unscathed." << endl;
			break;
		case 7:
			cout << "You graze the harpy with your sword." << endl;
			break;
		case 6:
			cout << "You stab her as she flies towards you." << endl;
			break;
		case 5:
			cout << "You cut off some of her talons, but she continues to fight with the ones she has left." << endl;
			break;
		case 4:
			cout << "You manage to strike the harpy's wing. She howls in pain and strikes back." << endl;
			break;
		case 3:
			cout << "The harpies movements are not as fast as they were before, she seems to be severily injured." << endl;
			break;
		case 2:
			cout << "You stab her with your sword as she charges toward you. Your blood is dripping with green blood, but she is not dead yet." << endl;
			break;
		case 1:
			cout << "The harpy looks disheveled, green blood oozes from an unseen wound. She can barely fly." << endl;
			break;
		case 0:
			cout << "With one last slash of your blade you slay the harpy. May the many souls that rest here finally have peace." << endl;
			break;
		}
	}

};

class Location {
public:
	string name;
	string description;
	Item items[MAX_ITEMS_IN_LOCATION];
	Monster monsters;

	Location() {
		Item empty;
		empty.name = "EMPTY";
		for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
			items[i] = empty;
		}
	}

	bool addItem(Item item) {
		bool addedSuccessfully = false;

		for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
			if (items[i].name == "EMPTY") {
				items[i] = item;
				addedSuccessfully = true;
				break;
			}
		}
		if (!addedSuccessfully) {
			cout << "This location is too crowded. It cannot hold anymore items." << endl;
		}
		return addedSuccessfully;
	}

	void addMonster(Monster monster) {
		monsters = monster;
	}

	void killMonster() {
		Monster empty;
		empty.name = "EMPTY";
		monsters = empty;
	}

	void removeItem(Item item) {
		Item empty;
		empty.name = "EMPTY";

		for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
			if (items[i].name == item.name) {
				items[i] = empty;
				break;
			}
		}
	}


	void display() {
		cout << "\n" << name << endl;
		cout << description << endl;

		Item empty;
		empty.name = "EMPTY";

		for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
			if (items[i].name != empty.name) {
				cout << items[i].description << endl;
			}
		}
		if (monsters.name != "EMPTY") {
			cout << monsters.description << endl;
		}
	}
};

class Character {
public:
	int yCoordinate;
	int xCoordinate;
	int characterHealth;
	Item possesions[MAX_ITEMS_ON_CHARACTER];

	Character() {
		Item empty;
		empty.name = "EMPTY";
		for (int i = 0; i < MAX_ITEMS_ON_CHARACTER; i++) {
			possesions[i] = empty;
		}
		characterHealth = 10;
	}
	
	bool addItem(Item item) {
		bool addedSuccessfully = false;

		for (int i = 0; i < MAX_ITEMS_ON_CHARACTER; i++) {
			if (possesions[i].name == "EMPTY") {
				possesions[i] = item;
				addedSuccessfully = true;
				cout << "Taken!\n" << endl;
				break;
			}
		}
		if (!addedSuccessfully) {
			cout << "Your pockets are already full. If you want to pick this item up you will have to drop something." << endl;
		}
		return addedSuccessfully;
	}

	void removefromInventory(Item item) {
		Item empty;
		empty.name = "EMPTY";

		for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
			if (possesions[i].name == item.name) {
				possesions[i] = empty;
				break;
			}
		}
	}

	void inventory() {
		cout << "Inventory: " << endl;
		for (int i = 0; i < MAX_ITEMS_ON_CHARACTER; i++) {
			if (possesions[i].name != "EMPTY") {
				cout << possesions[i].name << "\n"<< endl;
			}
		}
	}

	void battle(int characterHealth) {

		switch (characterHealth) {
		case 9:
			cout << "\nYour shoulder is grazed by the harpies wing, but other than that you manage to deflect her attack." << endl;
			break;
		case 8:
			cout << "\nHer claws bite into your shoulder." << endl;
			break;
		case 7:
			cout << "\nHer sword slashes your leg and you briefly lose your footing, you can no longer defend yourself from her attacks as effectively" << endl;
			break;
		case 6:
			cout << "\nYou are thrown across her lair, although disoriented you get up with your sword in hand." << endl;
			break;
		case 5:
			cout << "\nYou are stabbed in the leg and fall down to one knee. You use your sword to regain your footing." << endl;
			break;
		case 4:
			cout << "\nYour strength is leaving you as you find it harder and harder to hold your sword upright." << endl;
			break;
		case 3:
			cout << "\nYou are stabbed in the stomach with a dagger. If you do not win this battle soon you will die." << endl;
			break;
		case 2:
			cout << "\nHer claws continue to hit you try to strike her with your sword. You are so disoriented from blood loss that you do not know which one of her to hit." << endl;
			break;
		case 1:
			cout << "\nYou can barely stand, let alone fight. Another attack would be suicide." << endl;
			break;
		case 0:
			cout << "\nYour vision is fading as you stumble backwards. The harpy grabs both shoulders with her powerful talens and flies up into the sky. She drops you from a great hight. As you fall to your death you can see the Village of Pegana in the distance." << endl;
			break;
		}
	}

	void move(string input) {

		if (input == "E" || input == "e") {
			if (xCoordinate == MAX_X_COORDINATE - 1) {
				cout << "You may not go that way" << endl;
			}
			else {
				xCoordinate = xCoordinate + 1;
			}
		}
		else if (input == "W" || input == "w") {
			if (xCoordinate == 0) {
				cout << "You may not go that way" << endl;
			}
			else {
				xCoordinate = xCoordinate - 1;
			}
		}
		if (input == "N" || input == "n") {
			if (yCoordinate == 0) {
				cout << "You may not go that way" << endl;
			}
			else {
				yCoordinate = yCoordinate - 1;
			}
		}
		else if (input == "S" || input == "s") {
			if (yCoordinate == MAX_Y_COORDINATE - 1) {
				cout << "You may not go that way" << endl;
			}
			else {
				yCoordinate = yCoordinate + 1;
			}
		}
	}
};


int main(){
	string substring, substring2;
	int characterDamage;
	int monsterDamage;
	bool fled = false;
	
	Character character;
	character.yCoordinate = 1;
	character.xCoordinate = 2;
	character.characterHealth;

	Location clearing;
	clearing.name = "Clearing";
	clearing.description = "Everything is silent. You are standing in a clearing, to your East are mountains too treacherous to climb.\nTo the west there appears to be the remains of a ship. On all other sides there is a jungle as far as the eye can see.";
	
	Location jungle;
	jungle.name = "Jungle";
	jungle.description = "Everything is dimly lit, the thick canopy overhead lets in only small patches of light. \nYou hear the sound of someone singing an indiscernible melody coming from the west.";

	Location lookoutTree;
	lookoutTree.name = "Jungle";
	lookoutTree.description = "There is a large tree in front of you. Upon climbing it you are able to see a valley \nand what appears to be a village to the north.\nEverything else is covered by a canopy of trees and the mountains.";

	Location ship;
	ship.name = "Ship";
	ship.description = "There is the wreckage of an old ship. Tucked away under one of the floor boards is a weathered roll of papyrus. Upon carefully opening it you reveal musical notes and lyrics that read:\nPraise Skarl and his drum. Praise the world as was created once before! May Mana sleep for a million years more!";

	Location temple;
	temple.name = "Temple";
	temple.description = "The ruins of an ancient civilization are around you. Nature had almost entirely reclaimed this once flourishing area.\nYou move away some vines to reveal text on a stone tablet, it reads: \n\n\nWhen Mana-Yood-Sushai had made the gods and Skarl, \nSkarl made a drum, and began to beat upon it that he might drum for ever.\nThen because he was weary after the making of the gods, and because of the drumming of Skarl, \ndid Mana-Yood-Sushai grow drowsy and fall asleep. And there fell a hush upon the gods when they saw that Mana rested, \nand there was silence on Pegana save for the drumming of Skarl.\n\n-Lord Dunsany";

	Location valley;
	valley.name = "Valley";
	valley.description = "Water once ran through the stone walls that now surround you.";

	Location village;
	village.name = "Village of Pegana";
	village.description = "A village looms before you, moving aside some dead leafs reveals stone lettering on the ground that reads:\nThe Village of Pegana\nYou quickly notice that everything in the village is empty, it appears to have been abandoned quite recently.\nThe houses appear to be made from the stone walls that surround them.";

	Location caveEntrance;
	caveEntrance.name = "Cave Entrance";
	caveEntrance.description = "You are now on the outskirts of the village, in front of you is the entrance to a cave. It appears to continue on for a short while to the south, from this direction you can see a flickering light.";
	
	Location cave;
	cave.name = "Cave";
	cave.description = "Water drips around you. The beating of the drum starts again upon your entrance. \n\nSitting in the center of the cave is Skarl and his drum.\nAs you look at the drum you feel your eyelids start to get heavy. You begin to step forward to meet Skarl,\nbut he starts begging you not to take his drum. \nHe mutters about the life that has left Pegana since you awoken.";

	Item sword;
	sword.name = "sword";
	sword.description = "A SWORD with rubies embeded in its handle lies on the ground.";
	sword.lookupName = "sword";

	Item drum;
	drum.name = "drum";
	drum.description = "Skarl's drum lays on the ground, it appears older than time itself.";
	drum.lookupName = "drum";

	Item statue;
	statue.name = "statue";
	statue.description = "A small wooden STATUE of a sleeping person lies on the ground. Carved into it are the words: Mana's Slumber";
	statue.lookupName = "statue";

	Monster harpy;
	harpy.name = "Harpy";
	harpy.description = "\nA HARPY blocks your way. Half-bird, half-human, they are one of the most loathed magical creatures in Pegana.\nHuman and animal kelektons litter her layer.\nYou try to retreat, but her eyes flutter open and she flies forward and barely misses hitting you.";
	harpy.health;
	harpy.lookupName = "harpy";

	//Assigning locations.
	jungle.addItem(sword);
	cave.addItem(drum);
	valley.addMonster(harpy);
	clearing.addItem(statue);


	
	Location map[MAX_Y_COORDINATE][MAX_X_COORDINATE];
	map[0][0] = village;
	map[0][1] = valley;
	map[0][2] = jungle;
	map[1][2] = clearing;
	map[1][1] = ship;
	map[1][0] = caveEntrance;
	map[2][0] = cave;
	map[2][1] = temple;
	map[2][2] = lookoutTree;

	//Beginning of game.
	changeColor(BLUE_TEXT_COLOR);
	cout << "Treasures of Pegana" << endl;
	changeColor(WHITE_TEXT_COLOR);
	cout << "Designed by Emily Miner\n" << endl;
	Sleep(1000);

	//Setting start location.
	map[character.yCoordinate][character.xCoordinate].display();
	cout << "What will you do next?" << endl;

	//Once this for loop ends gameplay is over.
	for (;;) {
		string input;
		getline(cin, input);
		substring = input.substr(0, input.find(" "));
		substring2 = input.substr(input.find(" ") + 1);

		for (int i = 0; i < 8; i++) {
			if (directions[i] == input) {
				character.move(input);
				map[character.yCoordinate][character.xCoordinate].display();
				break;
			}
		}

		while (input == "l" || input == "look") {
			map[character.yCoordinate][character.xCoordinate].display();
			break;
		}

		while (input == "i" || input == "inventory") {
			character.inventory();
			break;
		}

		if (substring == "get") {

			for (int i = 0; i < MAX_ITEMS_IN_LOCATION; i++) {
				
				if (map[character.yCoordinate][character.xCoordinate].items[i].lookupName == substring2) {
					bool addedSuccesfully = character.addItem(map[character.yCoordinate][character.xCoordinate].items[i]);
						
					if (addedSuccesfully) {
						if (map[character.yCoordinate][character.xCoordinate].items[i].lookupName == drum.lookupName) {
							changeColor(RED_TEXT_COLOR);
							cout << "\nSince you took the drum the universe has now come to an end. Congratulations! Goodbye" << endl;
							changeColor(WHITE_TEXT_COLOR);
							return(1);
						}
						else {
							Item empty;
							empty.name = "EMPTY";
							map[character.yCoordinate][character.xCoordinate].items[i] = empty;
						}
					}
					else {
						cout << "Your bag is full, if you want it you better drop something." << endl;
					}
					break;
				}
				
			}
		}

		if (substring == "drop") {

			for (int i = 0; i < MAX_ITEMS_ON_CHARACTER; i++) {
				Item item = character.possesions[i];

				if (item.lookupName == substring2) {
					bool addedSuccesfully = map[character.yCoordinate][character.xCoordinate].addItem(item);

					if (addedSuccesfully) {
						character.removefromInventory(item);
						cout << "Dropped!" << endl;
					}
					else {
						cout << "This place cannot deal with anymore clutter. Dump your trash elsewhere!" << endl;
					}
					break;
				}
		
			}
		}

		if (substring == "attack") {
			
			if (substring2 == harpy.lookupName) {
				bool fled = false;
				bool hasWeapon = false;
				
				string weapon;
				cout << "\nWhat will you attack the harpy with?" << endl;
				cin >> weapon;

				for (int i = 0; i < MAX_ITEMS_ON_CHARACTER; i++) {
					Item item = character.possesions[i];
					if (item.lookupName == weapon) {
						hasWeapon = true;
						break;
					}
				}

				if (hasWeapon == false) {
					cout << "Attacking without a weapon is suicide. You must retreat." << endl;
					fled = true;
				}

				while (harpy.health > 0 && character.characterHealth > 0 && hasWeapon) {
					string attack;
					
					monsterDamage = rand() % 6 + 1;
					characterDamage = rand() % 4 + 1;
					harpy.health = harpy.health - monsterDamage;
					character.characterHealth = character.characterHealth - characterDamage;
					
					character.battle(character.characterHealth);
					harpy.attack(harpy.health);
					cin >> attack;
					
					for (int i = 0; i < 5; i++) {
						if (retreat[i] == attack) {
							fled = true;
							break;
						}
					}
					fled = false;
				}

				if (fled == false) {
					if (character.characterHealth <= 0) {
						cout << "Goodbye" << endl;
						break;
					}
					else {
						map[character.yCoordinate][character.xCoordinate].killMonster();
						cout << "You slay the harpy, and with the last fall of your sword you begin to hear the faint beat of a drum from the west." << endl;
					}
				}
				else {
					cout << "You barely escape with your life." << endl;
				}
			}
			else {
				cout << "Attack what? You cannot just attack nothing." << endl;
			}
		}
	}
}
