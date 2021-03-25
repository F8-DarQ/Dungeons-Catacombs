//
// Dungeon - Catacombs
//
// Created by Justin Richard 03-17-2021
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::distance;

int askNumber(string question, int high, int low);
void displayInventory(const vector<string>& inventory, const vector<int>& stock, const vector<int>& prices);

class Enemy {
public:
	Enemy();
	void takeDamage(int damage);
	int getDamage() const;
	int getHealth() const;
protected:
	int m_Damage;
	int m_Health;
};
Enemy::Enemy() :
	m_Damage(5), m_Health(30)
{}
void Enemy::takeDamage(int damage) {
	m_Health -= damage;
}
int Enemy::getDamage() const {
	return m_Damage;
}
int Enemy::getHealth() const {
	return m_Health;
}

class Boss : public Enemy {
public:
	Boss();
	void SpecialAttack() const;
private:
	int m_DamageMultiplier;
};
Boss::Boss() :
	m_DamageMultiplier(2)
{}
void Boss::SpecialAttack() const {
	cout << "Boss's special attack hit you for " << (m_DamageMultiplier * m_Damage) << " damage! \n";
}

class Room {
private:
	string m_Name;
	string m_Description;
	string m_Event;
	vector<Room*> m_Exits;
public:
	Room(string name = "Empty Room", string description = "This is an empty room.", string event = "This is an event.");
	void AddExit(Room* room);
	void DisplayRoom();
	int NumberOfExits();
	vector<Room*> GetExits();
};
Room::Room(string name, string description, string event) {
	m_Name = name;
	m_Description = description;
	m_Event = event;
}
void Room::AddExit(Room* room) {
	m_Exits.push_back(room);
}
void Room::DisplayRoom() {
	cout << endl << m_Name << endl;
	cout << "--------------------" << endl;
	cout << m_Description << endl;
	cout << m_Event << endl << endl;
	cout << "You see exits to the following locations:" << endl;
	for (int i = 0; i < m_Exits.size(); i++) {
		cout << i+1 << "." << (*m_Exits[i]).m_Name << endl;
	}
}
int Room::NumberOfExits() {
	return m_Exits.size();
}
vector<Room*> Room::GetExits() {
	return m_Exits;
}

class Player {
	Room* m_CurrentRoom;
public:
	Player();
	void SetLocation(Room* room);
	Room* GetLocation();
	void takeDamage(int damage);
	void restoreHealth(int health);
	int getDamage() const;
	int getHealth() const;
protected:
	int m_Health;
	int m_Damage;
};
Player::Player() :
	m_Health(50), m_Damage(5)
{}
void Player::SetLocation(Room* room) {
	m_CurrentRoom = room;
}
Room* Player::GetLocation() {
	return m_CurrentRoom;
}
void Player::takeDamage(int damage) {
	m_Health -= damage;
}
void Player::restoreHealth(int health) {
	m_Health += health;
}
int Player::getHealth() const {
	return m_Health;
}
int Player::getDamage() const {
	return m_Damage;
}


int main(int argc, const char* argv[]) {
	Room* room1 = new Room("Dungeon Hub", "This is the starter area with merchants", "There is nothing of use in this room");
	Room* room2 = new Room("Dungeon Spawn", "The howls of the undead can be heard below", "There is nothing of use in this room");
	Room* room3 = new Room("Main Area", "You stand in an open room", "There is nothing of use in this room");
	Room* room4 = new Room("Prison Room", "The room is dimly lit", "There is nothing of use in this room");
	Room* room5 = new Room("Empty Room", "Plain room", "There is nothing of use in this room");
	Room* room6 = new Room("Chapel", "Small room with a balchony above, though no visible way to reach it", "There is nothing of use in this room");
	Room* room7 = new Room("Three Weirdos", "A small room with three figures standing silently", "Each of the figures has a chest next to them");
	Room* room8 = new Room("Mini-Boss", "The room is littered with skulls and bones", "A single figure stands among the bones");
	Room* room9 = new Room("Blood Room", "The room is painted a deep red", "You see a staircase leading lower");
	Room* room10 = new Room("Boss Room", "It seems the circus is in town, the room is decorated with pillers and color, resembling a circus tent", "There is a single clown");

	room1->AddExit(room2);

	room2->AddExit(room3);

	room3->AddExit(room2);
	room3->AddExit(room4);
	room3->AddExit(room5);

	room4->AddExit(room3);

	room5->AddExit(room3);
	room5->AddExit(room6);
	room5->AddExit(room8);

	room6->AddExit(room5);
	room6->AddExit(room7);

	room7->AddExit(room6);

	room8->AddExit(room5);
	room8->AddExit(room9);

	room9->AddExit(room10);

	room10->AddExit(room9);

	Player* player = new Player;

	vector<string> playerInventory;
	playerInventory.push_back("Midas Sword");
	playerInventory.push_back("Iron Armor");
	playerInventory.push_back("Health Potion");

	vector<int> playerStock;
	playerStock.push_back(1);
	playerStock.push_back(1);
	playerStock.push_back(3);

	vector<int> playerPrices;
	playerPrices.push_back(100);
	playerPrices.push_back(100);
	playerPrices.push_back(20);

	vector<bool> playerEquip;
	playerEquip.push_back(true);
	playerEquip.push_back(true);
	playerEquip.push_back(false);

	vector<string> merchantInventory;
	merchantInventory.push_back("Hyper Cleaver");
	merchantInventory.push_back("Dragon Armor");
	merchantInventory.push_back("Health Potion");

	vector<int> merchantStock;
	merchantStock.push_back(1);
	merchantStock.push_back(1);
	merchantStock.push_back(99);

	vector<int> merchantPrices;
	merchantPrices.push_back(100);
	merchantPrices.push_back(200);
	merchantPrices.push_back(20);

	vector<string> bossInventory;
	bossInventory.push_back("Bonzo Staff");
	bossInventory.push_back("Bonzo Mask");

	vector<int> bossStock;
	bossStock.push_back(1);
	bossStock.push_back(1);

	vector<int> bossPrices;
	bossPrices.push_back(0);
	bossPrices.push_back(0);

	float merchantBuyBackRate = 0.5;

	int playerGold = 100;

	player->SetLocation(room2);

	cout << "You stand in front of a giant door made of skulls, towering over you." << endl;
	cout << "Before the door stands a figure, covered in cloth." << endl;
	cout << "To the right, a small merchant has set up shop." << endl;

	int choice;
	int choice2;
	int choice3;
	int choice4;
	int choice5;
	int choice6;

	do {
		cout << endl << "1. Enter Dungeon" << endl;
		cout << "2. Speak to Merchant" << endl;
		cout << "3. View Inventory" << endl;
		cout << "4. Equip/Unequip Items" << endl;
		cout << "0. Quit" << endl;

		choice = askNumber("Your choice?", 4, 0);

		switch (choice) {
		case 1: { // speak to mort and enter dungeon
			cout << endl << "Good Luck adventurer, you'll need it when you face the Necromancer Bonzo below." << endl << endl;
			player->SetLocation(room2);
			player->GetLocation()->DisplayRoom();
			do {
				cout << endl << "1. Move to a new location" << endl;
				cout << "2. Interact" << endl;
				cout << endl;
				choice3 = askNumber("What would you like to do? (0 to quit) ", 2, 0);

				switch (choice3) {
				case 1: { // choose where to move to
					int moveChoice;
					moveChoice = askNumber("Where would you like to go? ", player->GetLocation()->NumberOfExits(), 1) - 1;
					if (moveChoice == -1) {
						cout << endl << "Invalid option." << endl;
					}
					else {
						player->SetLocation(player->GetLocation()->GetExits()[moveChoice]);
						player->GetLocation()->DisplayRoom();
					}
					break;
				}
				case 2: { // interact with something in the room
					if (player->GetLocation() == room7) { // Pick a Chest Room
						int chestChoice;
						cout << endl << "You see 3 figures standing quietly, each with a chest next to them" << endl;
						cout << "1. Marco: One of us is telling the truth." << endl;
						cout << "2. Falco: They are bothe telling the truth. The reward isn't in Gabi's chest." << endl;
						cout << "3. Gabi: The reward is not in my chest." << endl;
						chestChoice = askNumber("Which chest do you think it is in?", 3, 1) - 1;
						if (chestChoice == 2) {
							cout << endl << "Correct, have this reward." << endl;
							cout << "Added a Bag of Gems to your inventory." << endl;
							playerInventory.push_back("Bag of Gems");
							playerStock.push_back(1);
							playerPrices.push_back(100);
						}
						else {
							cout << endl << "Sorry, but you have chosen wrong." << endl;
							cout << "The figures and their chests disappear before your eyes." << endl;
						}
					}
					else if (player->GetLocation() == room8) { // Mini Boss Room
						Enemy enemy1;
						cout << endl << "a dark figure stands before you" << endl;
						cout << "Its clothes tattered and it's flesh peeling off" << endl;

						do {
							cout << endl << "1. Attack" << endl;
							cout << "2. Defend" << endl;
							cout << "3. Use potion" << endl;
							cout << "0. Give Up" << endl;

							choice4 = askNumber("Your choice?", 3, 0);

							switch (choice4) {
							case 1: { // attack the enemy
								cout << endl << "You hit the enemy for " << player->getDamage() << " damage!" << endl;
								enemy1.takeDamage(player->getDamage());
								cout << "Enemy has " << enemy1.getHealth() << " health remaining." << endl;
								if (enemy1.getHealth() <= 0) {
									cout << endl << "The enemy was defeated!" << endl;
								}
								else {
									cout << endl << "enemy hit you for " << enemy1.getDamage() << " damage!" << endl;
									player->takeDamage(enemy1.getDamage());
									cout << "You have " << player->getHealth() << " health remaining." << endl;
								}
								break;
							}
							case 2: { // defend against attack
								cout << endl << "You prepare yourself for the enemy attack." << endl;
								player->takeDamage(enemy1.getDamage() / 2);
								cout << "You have " << player->getHealth() << " health remaining." << endl;
								break;
							}
							case 3: { // use a health potion if you have one in inventory
								cout << endl << "You drink a health potion and restore 10 health." << endl;
								player->restoreHealth(10);
								cout << "You have " << player->getHealth() << " health remaining." << endl;
								playerStock[2]--;
								break;
							}
							case 0: { // give up on fight and leave combat
								cout << "The enemy is too strong, you turn and flee." << endl;
								break;
							}
							default: {
								cout << endl << "ERROR: Invalid Choice. You should never see this." << endl;
								break;
							}
							}
						} while (choice4 != 0 && enemy1.getHealth() > 0);
						break;
					}
					else if (player->GetLocation() == room10) { // Boss Room
						Boss Bonzo;
						cout << endl << "A clown with a big red nose stands before you" << endl;
						cout << "Congrats for making it this far, but this is the end of the line" << endl;

						do {
							cout << endl << "1. Attack" << endl;
							cout << "2. Defend" << endl;
							cout << "3. Use potion" << endl;
							cout << "0. Give Up" << endl;

							choice5 = askNumber("Your choice?", 3, 0);

							switch (choice5) {
							case 1: { // attack the enemy
								cout << endl << "You hit the enemy for " << player->getDamage() << " damage!" << endl;
								Bonzo.takeDamage(player->getDamage());
								cout << "Enemy has " << Bonzo.getHealth() << " health remaining." << endl;
								if (Bonzo.getHealth() <= 0) {
									cout << endl << "Bonzo the Clown was defeated! Please, take your reward." << endl;
									displayInventory(bossInventory, bossStock, bossPrices);
									int choice6 = askNumber("Take Item", bossInventory.size(), 0);
									if (!(bossStock[choice6 - 1])) {
										cout << endl << "You already took that item!" << endl;
										break;
									}
									bossStock[choice6 - 1]--;
									playerInventory.push_back(bossInventory[choice6 - 1]);
									playerStock.push_back(1);
									playerPrices.push_back(200);
									playerEquip.push_back(false);
									break;
								}
								else {
									cout << endl << "enemy hit you for " << Bonzo.getDamage() << " damage!" << endl;
									player->takeDamage(Bonzo.getDamage());
									cout << "You have " << player->getHealth() << " health remaining." << endl;
								}
								break;
							}
							case 2: { // defend against attack
								cout << endl << "You prepare yourself for the enemy attack." << endl;
								player->takeDamage(Bonzo.getDamage() / 2);
								cout << "You have " << player->getHealth() << " health remaining." << endl;
								break;
							}
							case 3: { // use a health potion if you have one in inventory
								cout << endl << "You drink a health potion and restore 10 health." << endl;
								player->restoreHealth(10);
								cout << "You have " << player->getHealth() << " health remaining." << endl;
								playerStock[2]--;
								break;
							}
							case 0: { // give up on fight and leave combat
								cout << "The enemy is too strong, you turn and flee." << endl;
								break;
							}
							default: {
								cout << endl << "ERROR: Invalid Choice. You should never see this." << endl;
								break;
							}
							}
						} while (choice5 != 0 && Bonzo.getHealth() > 0);
						break;
					}
					else {
						cout << endl << "There is nothing in here." << endl;
					}
					break;
				}
				case 0: { // quit back to main menu
					cout << endl << "You hear a laugh echo from the dungeon, taunting you to return." << endl;
					break;
				}
				default: {
					cout << endl << "ERROR: Invalid Choice... Wait a minute, you shouldn't be seeing this!" << endl;
					break;
				}
				}
			} while (choice3 != 0);
			break;
		}
		case 2: { // speak to Ophelia and run merchant
			do {
				cout << endl << "Hi, I'm Ophelia, what would you like to do?" << endl;
				cout << "1. Buy from merchant" << endl;
				cout << "2. Sell to merchant" << endl;
				cout << "3. View Inventory" << endl;
				cout << "4. View merchant inventory" << endl;
				cout << "0. Leave shop" << endl;

				choice2 = askNumber("Your choice?", 4, 0);

				switch (choice2) {
				case 1: { // buy from merchant
					cout << endl << "What do you need?" << endl;
					displayInventory(merchantInventory, merchantStock, merchantPrices);
					cout << "Gold: " << playerGold << endl;
					int choice3 = askNumber("Your Choice?", merchantInventory.size(), 0);

					if (!(merchantStock[choice3 - 1])) {
						cout << endl << "I'm sorry, but that item is out of stock." << endl;
						break;
					}
					if (!(playerGold >= merchantPrices[choice3 - 1])) {
						cout << endl << "What are you trying to pull here? You don't have enough gold for that." << endl;
						break;
					}

					playerGold -= merchantPrices[choice3 - 1];
					merchantStock[choice3 - 1]--;
					vector<string>::iterator it;

					it = find(playerInventory.begin(), playerInventory.end(), merchantInventory[choice3 - 1]);
					if (it != playerInventory.end()) {
						int index = distance(playerInventory.begin(), it);
						playerStock[index]++;
					}
					else {
						playerInventory.push_back(merchantInventory[choice3 - 1]);
						playerStock.push_back(1);
						playerPrices.push_back(merchantPrices[choice3 - 1]);
						playerEquip.push_back(false);
					}
					break;
				}
				case 2: { // sell to merchant
					cout << endl << "What have you got to sell?" << endl;
					displayInventory(playerInventory, playerStock, playerPrices);
					cout << "Gold: " << playerGold << endl;
					int choice4 = askNumber("Your Choice? ", playerInventory.size(), 0);

					playerGold += (merchantBuyBackRate * playerPrices[choice4 - 1]);
					playerStock[choice4 - 1]--;
					vector<string>::iterator it;

					it = find(merchantInventory.begin(), merchantInventory.end(), playerInventory[choice4 - 1]);
					if (it != merchantInventory.end()) {
						int index = distance(merchantInventory.begin(), it);
						merchantStock[index]++;
					}
					else {
						merchantInventory.push_back(playerInventory[choice4 - 1]);
						merchantStock.push_back(1);
						merchantPrices.push_back(playerPrices[choice4 - 1]);
					}
					if (playerStock[choice4 - 1] == 0) {
						playerInventory.erase(playerInventory.begin() + choice4 - 1);
						playerStock.erase(playerStock.begin() + choice4 - 1);
						playerPrices.erase(playerPrices.begin() + choice4 - 1);
						playerEquip.erase(playerEquip.begin() + choice4 - 1);
					}
					break;
				}
				case 3: { // display player inventory
					cout << endl << "Viewing your inventory" << endl;
					displayInventory(playerInventory, playerStock, playerPrices);
					cout << "Gold: " << playerGold << endl;
					break;
				}
				case 4: { // display merchant inventory
					cout << endl << "Viewing merchant inventory" << endl;
					displayInventory(merchantInventory, merchantStock, merchantPrices);
					break;
				}
				case 0: { // leave merchant
					cout << endl << "Thanks for shopping!" << endl;
					break;
				}
				default: {
					cout << endl << "ERROR: Invalid choice... Don't confuse Ophelia!" << endl;
					break;
				}
				}
			} while (choice2 != 0);
			break;
		}
		case 3: { // view player inventory
			cout << endl << "Viewing your inventory" << endl;
			displayInventory(playerInventory, playerStock, playerPrices);
			cout << "Gold: " << playerGold << endl;
			break;
		}
		case 4: { // equip/unequip items
			cout << endl << "What would you like to equip/unequip?" << endl;
			displayInventory(playerInventory, playerStock, playerPrices);

			break;
		}
		case 0: { // quit game
			cout << endl << "You exit the dungeon, but it still lives in your mind, the Necromancers cackles filling your head." << endl;
			cout << "Thanks for playing." << endl;
			break;
		}
		default: {
			cout << endl << "ERROR: Invalid choice... You shouldn't be able to see this?" << endl;
			break;
		}
		}
	} while (choice != 0);
	return 0;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << " (" << low << " - " << high << " ): ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}


void displayInventory(const vector<string>& inventory, const vector<int>& stock, const vector<int>& prices) {

	cout << setw(3) << "#  " << setw(20) << "ITEM NAME" << setw(10) << "STOCK" << setw(10) << "PRICE" << endl;

	for (int i = 0; i < inventory.size(); i++) {
		cout << i + 1 << ". " << setw(20) << inventory[i];
		if (stock[i] != 0) {
			cout << setw(10) << stock[i] << setw(10) << prices[i] << endl;
		}
		else {
			cout << setw(10) << "SOLD OUT" << setw(10) << prices[i] << endl;
		}
	}
}