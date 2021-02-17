#ifndef ARSENAL_H
#define ARSENAL_H

#include <string>
#include <vector>
#include "Weapon.h"

using namespace std;

class Arsenal
{
private:
	vector<Weapon> mysteryBox_;

public:
	Arsenal() {};
	~Arsenal()
	{
		if (!mysteryBox_.empty())
		{
			mysteryBox_.clear();
		}
	}
	vector<Weapon> getWeaponList() const 
	{
		return mysteryBox_;
	}

	unsigned getArsenalSize() const
	{
		return static_cast<unsigned> (mysteryBox_.size());
	}

	void addWeapon(const Weapon& weapon)
	{
		mysteryBox_.push_back(weapon);
	}

	Weapon getWeapon(const string& name) const
	{
		for (unsigned i = 0; i < mysteryBox_.size(); ++i)
		{
			if (name == mysteryBox_[i].getName())
			{
				return mysteryBox_[i];
			}
		}
		return Weapon();
	}
	
	unsigned getDamage(const string name) const
	{
		for (unsigned i = 0; i < mysteryBox_.size(); ++i)
		{
			if (name == mysteryBox_[i].getName())
			{
				return mysteryBox_[i].getDamage();
			}
			else
			{
				return 0;
			}
		}
	}

	string getType(const string name) const
	{
		for (unsigned i = 0; i < mysteryBox_.size(); ++i)
		{
			if (name == mysteryBox_[i].getName())
			{
				return mysteryBox_[i].getType();
			}
			else
			{
				return "Not Defined";
			}
		}
	}

};
#endif // !ARSENAL_H



