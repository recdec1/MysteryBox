#ifndef ASSUALTRIFLE_H
#define ASSAULTRIFLE_H


#include <string>
#include "Weapon.h"
using namespace std;


class AssaultRifle : public Weapon
{
private:
	string _weaponType = "Assault Rifle";
	float _hipFireAccuracy = .6;
	float _adsCoefficient = 1.5;
	int _reserveAmmunition = 360;
public:
	/*AssaultRifle(const string name, const int damage, const float runspeed,
		const float rpm, const float reloadtime, const float ads, const int roundspermag,
		const int currentammunition) : Weapon(name, damage, runspeed, rpm, reloadtime, ads, roundspermag, currentammunition)
	{
		cout << "Assault Rifle: ";
	}*/
		
	string getType() const { return _weaponType; }
	int getReserveAmmunition() const { return _reserveAmmunition; }
	float getHipFireAccuracy() const { return _hipFireAccuracy; }
	float getADSCoefficient() const { return _adsCoefficient; }

	/*Need to complete overload assignment and copy by reference constructor. */
};

#endif // !ASSUALTRIFLE_H