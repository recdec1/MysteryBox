#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Arsenal.h"
#include "Weapon.h"
#include <Windows.h>
#include "AssaultRifle.h"
#include <cstdlib>

bool weaponRolled = true;
int damage = 0;
string name;
string type;
float runspeed;
float hipfireaccuracy;
float adscoefficient;
float rateoffire;
float ads;
float roundsperminute;
float reloadtime;
int reserveammunition;
int roundspermag;
int currentammunition;
Arsenal mysteryBox;

void SwapWeapons(vector<Weapon> playerWeapons, int x, string weaponN);
void PrintAllWeaponSummaries(Arsenal WeaponList);
void DisplayInventory(vector<Weapon> playerWeapons);
void PrintWeaponSummary(int weaponSelected, vector<Weapon> playerWeapons);
void LoadFile();
void LoadRandomWeapon(int x);
char AddWeapon(vector<Weapon> & playerWeapons, string weaponN); // the swapping functions pass in a copy of the vector, need to pass in the pointer to, or reference of the vector. 


int main() // need to catch input errors that arent a part of the selection provided. 
{
	vector<Weapon>playerWeapons;
	char buttonPress;
	srand(time(NULL));
	int weaponSelected;
	static bool inWeapon = true;
	

	LoadFile();
	PrintAllWeaponSummaries(mysteryBox);

	// starts the mystery box program
	cout << "Press E to use the MysteryBox" << endl;
	do
	{
		cin >> buttonPress;
	} while (buttonPress != 'e' && buttonPress != 'E');
	

	while (buttonPress != 'm' && buttonPress != 'M')
	{
		int x = rand() % mysteryBox.getArsenalSize();
		string weaponName = mysteryBox.getWeaponList()[x].getName();
		if  (playerWeapons.size() < 2 || (buttonPress == 'e' || buttonPress == 'E')) // roll mystery box
		{
			weaponRolled = true;
			LoadRandomWeapon(x);
			cout << "Take Weapon: 'T'\n"
				<< "ReRoll MysteryBox: 'E'\n"
				<< "Players Inventory: 'I'\n"
				<< "Escape Program: 'M'" << endl << endl;
		}
		else
		{
			cout << "ReRoll MysteryBox: 'E'\n"
				<< "Players Inventory: 'I'\n"
				<< "Escape Program: 'M'" << endl << endl;
		}
		cin >> buttonPress; // make an overloaded class that can take in integers and characters separately -- this will fix the problem with converting character input to integer
		if ((buttonPress == 't' || buttonPress == 'T') && weaponRolled == true)
		{
			buttonPress = AddWeapon(playerWeapons, mysteryBox.getWeaponList()[x].getName());
			weaponRolled = false;
			if (buttonPress == 'e' || buttonPress == 'E')
				continue;
		}
		 if (buttonPress == 'i' || buttonPress == 'I' && playerWeapons.size() > 0) // redundant but do not permit access to the inventory without pressing I. 
		{
			int weaponSelected = 1;
			while (buttonPress != 'e' && buttonPress != 'E' && buttonPress != 'm' && buttonPress != 'M')
			{
			
				if (buttonPress == 'i' || buttonPress == 'I')
				{
					DisplayInventory(playerWeapons);
					cin >> weaponSelected;
					weaponSelected--;
				}
				cout << playerWeapons[weaponSelected].getName() << endl << "Weapon Summary: 'S'\n" << "Fire Weapon: 'F'\n" << "Reload: 'R'\n" << "Weapon Inventory: 'I'\n" << "Mystery Box: 'E'\n" << "Escape Program: 'M'" << endl << endl;
				cin >> buttonPress; // need to catch button presses that arent a part of the selection - else the program reprints ^^ this line. 
				switch (buttonPress)
				{
				case 's':
				case 'S':
					PrintWeaponSummary(weaponSelected, playerWeapons); // overcomplicated, can just pass in a weapon. 
					continue;
				case 'f':
				case 'F':
					while (true)
					{
						if (GetAsyncKeyState('f') && 0x8000 != 0)
							playerWeapons[weaponSelected].FireWeapon();
					}
					continue;
				case 'r':
				case 'R':
					playerWeapons[weaponSelected].Reload();
					continue;
				default:
					break;
				}
			}
		}
		else if (playerWeapons.size() == 0)
		{
			cout << "No Weapons in Inventory" << endl << endl;

		}
	}
	exit(0);
}
char AddWeapon(vector<Weapon> & playerWeapons, string weaponN)
{
	char input;
	// add weapon to player inventory if inventory isnt full
	if (playerWeapons.size() < 2)
	{
		playerWeapons.push_back(mysteryBox.getWeapon(weaponN));
	}
	else
	{
		cout << "Already Carrying 2 Weapons\n" << "Switch Weapons:\n" << "1: " << playerWeapons[0].getName() << endl << "2: " << playerWeapons[1].getName() <<
			endl << "Cancel: 'E'\n" << "Exit: 'M'\n";
		
		cin >> input;
		if (input == '1' || input == '2')
		{
			int x = input - '0';
			SwapWeapons(playerWeapons, x, weaponN);
			cout << "Swapped" << endl;
		}
		return input;
	}
}

void SwapWeapons(vector<Weapon> playerWeapons, int x, string weaponN)
{
	playerWeapons[x - 1] = mysteryBox.getWeapon(weaponN);
}

void DisplayInventory(vector<Weapon> playerWeapons)
{
	
	if (playerWeapons.size() == 1) // need to catch in case weapon inventory is smaller than 2 - ie looking at the weapon you have before taking a second
	{
		cout << "Weapon Inventory\n" << "1: " << playerWeapons[0].getName() << endl;
	}
	else
	{
		cout << "Weapon Inventory\n" << "1: " << playerWeapons[0].getName() << endl << "2: " << playerWeapons[1].getName() << endl;
	}
}

void PrintWeaponSummary(int weaponSelected, vector<Weapon> playerWeapons)
{
	cout << "Name: " << playerWeapons[weaponSelected].getName() << endl << 
		"Type: " << playerWeapons[weaponSelected].getType() << endl <<
		"Damage: " << playerWeapons[weaponSelected].getDamage() << endl <<
		"Loaded Ammuntion: " << playerWeapons[weaponSelected].getCurrentAmmunition() << " / " << playerWeapons[weaponSelected].getRoundsPerMag() << endl <<
		"Reserve Ammuntion: " << playerWeapons[weaponSelected].getReserveAmmunition() << endl << endl;
}

void LoadRandomWeapon(int x)
{
	cout << "Incoming..." << endl;
	for (int i = 5; i >= 1; i--)
	{
		cout << i << endl;
		Sleep(100); // for testing purposes. 
	}

	cout << "Name: " << mysteryBox.getWeaponList()[x].getName() << " --> " << "Type: "
		<< mysteryBox.getWeaponList()[x].getType() << " --> " << "Damage: " <<
		mysteryBox.getWeaponList()[x].getDamage() << endl << endl;
}

void LoadFile()
{
	string fileName("BasicWeapons.txt");
	ifstream fileInput;
	fileInput.open(fileName.c_str());
	if (!fileInput.is_open())
	{
		cout << "Cannot Read File\n";
	}

	//class member allocation function from text document. 
	while (fileInput >> type >> name >> damage >> runspeed >> hipfireaccuracy >> adscoefficient >> reserveammunition >> roundsperminute >> reloadtime >> ads >> roundspermag >> currentammunition)
	{
		Weapon weapon(type, name, damage, runspeed, hipfireaccuracy, adscoefficient, reserveammunition, roundsperminute, reloadtime, ads, roundspermag, currentammunition);
		mysteryBox.addWeapon(weapon);
		/*if (type == "AssualtRifle")
		{
			Weapon::setUp(name, damage, runspeed, rpm, reloadtime, ads, roundspermag, currentammunition);
		}*/
	}

	if (fileInput.is_open())
	{
		fileInput.close();
	}
}

void PrintAllWeaponSummaries(Arsenal WeaponList)
{
	for (auto i : WeaponList.getWeaponList())
	{
		cout << i.getName() << endl << i.getType() << endl << i.getDamage() << endl << i.getCurrentAmmunition() << endl << i.getRoundsPerMag() << endl <<
			i.getReserveAmmunition() << endl << i.getRateOfFire() << endl << i.getRunSpeed() << endl << i.getHipFireAccuracy() << endl << i.getADSCoefficient() << endl
			<< i.getReloadTime() << endl << i.getADSTime() << endl << endl;
	}
}