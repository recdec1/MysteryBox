#ifndef WEAPON_H
#define WEAPON_H


#include <string>
#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;

class Weapon
{
private:
	//attributes to be inherited
	// instead of taking in 1 text document, make weapon types class based off of separate text document
	string _weaponType;
	float _hipFireAccuracy;
	float _adsCoefficient;
	int _reserveAmmunition;
	/*class AssaultRifle;*/

	string _weaponName;
	float _runSpeed;
	float _rateOfFire;
	float _reloadTime;
	float _adsTime;
	int _baseDamage;
	int _roundsPerMag;
	int _currentAmmunition;
	bool _aiming = false;


public:

	Weapon() {};

	~Weapon() {};

	Weapon(const string& type, const string& name, const int& damage, const float& runspeed, const float& hipfireaccuracy, const float& adscoefficient, const int& reserveammunition,
		const float& rpm, const float& reloadtime, const float& ads, const int& roundspermag, const int& currentammunition)
		: _weaponName(name), _weaponType(type), _baseDamage(damage), _runSpeed(runspeed), _hipFireAccuracy(hipfireaccuracy), _adsCoefficient(adscoefficient), _reserveAmmunition(reserveammunition),
		_rateOfFire(rpm), _reloadTime(reloadtime), _adsTime(ads), _roundsPerMag(roundspermag), _currentAmmunition(currentammunition)
	{
		cout << "Weapon " << name << " Loaded." << endl;
	}

	// Copy by const reference constructor
	Weapon(const Weapon& rhs)
	{
		_weaponName = rhs._weaponName;
		_weaponType = rhs._weaponType;
		_baseDamage = rhs._baseDamage;
		_runSpeed = rhs._runSpeed;
		_hipFireAccuracy = rhs._hipFireAccuracy;
		_adsCoefficient = rhs._adsCoefficient;
		_reserveAmmunition = rhs._reserveAmmunition;
		_rateOfFire = rhs._rateOfFire;
		_reloadTime = rhs._reloadTime;
		_adsTime = rhs._adsTime;
		_roundsPerMag = rhs._roundsPerMag;
		_currentAmmunition = rhs._currentAmmunition;

	}

	// this is the overloaded assignment Operator
	Weapon& operator = (const Weapon& rhs)
	{
		_weaponName = rhs._weaponName;
		_weaponType = rhs._weaponType;
		_baseDamage = rhs._baseDamage;
		_runSpeed = rhs._runSpeed;
		_hipFireAccuracy = rhs._hipFireAccuracy;
		_adsCoefficient = rhs._adsCoefficient;
		_reserveAmmunition = rhs._reserveAmmunition;
		_rateOfFire = rhs._rateOfFire;
		_reloadTime = rhs._reloadTime;
		_adsTime = rhs._adsTime;
		_roundsPerMag = rhs._roundsPerMag;
		_currentAmmunition = rhs._currentAmmunition;
		return *this;
	}

	void setUp(const string& name, const int& damage, const float& runspeed, const float& rpm, const float& reloadtime,
		const float& ads, const int& roundspermag, const int& currentammunition)
	{
		_weaponName = name;
		_baseDamage = damage;
		_runSpeed = runspeed;
		_rateOfFire = rpm;
		_reloadTime = reloadtime;
		_adsTime = ads;
		_roundsPerMag = roundspermag;
		_currentAmmunition = currentammunition;
	}

	//Get Operations
	string getName() const { return _weaponName; }
	string getType() const { return _weaponType; }
	int getDamage() const { return _baseDamage; }
	int getCurrentAmmunition() const { return _currentAmmunition; }
	int getRoundsPerMag() const { return _roundsPerMag; }
	int getReserveAmmunition() const { return _reserveAmmunition; }
	float getRateOfFire() const { return _rateOfFire; }
	float getRunSpeed() const { return _runSpeed; }
	float getHipFireAccuracy() const { return _hipFireAccuracy; }
	float getADSCoefficient() const { return _adsCoefficient; }
	float getReloadTime() const { return _reloadTime; }
	float getADSTime() const { return _adsTime; }
	bool isAiming() const { return _aiming; }

	//Set Operators for mutable properties

	void setAiming()
	{
		if (_aiming == true)
			_aiming = false;
		else
			_aiming = true;
	}
	 
	void FireWeapon() // add funtionality to fire weapon when space is pressed
						// function will need to include a break clause when r is pressed for a reload 
	{
		if (_currentAmmunition == 0)
		{
			cout << "Please Reload" << endl << endl;
		}
		else
		{
			for (int i = _currentAmmunition; i > 0; i--)
			{
				cout << _currentAmmunition << endl;
				_currentAmmunition -= 1;
				Sleep(ceil(1 / (_rateOfFire / 60) * 1000));
				
			}
			cout << "Please Reload" << endl << endl;
		}
	}

	void Reload()
	{
		if (_currentAmmunition == _roundsPerMag)
			cout << "Full Magazine" << endl << endl;
		else if (_reserveAmmunition == 0)
			cout << "No Remaining Ammo" << endl << endl;
		else
		{
			cout << "Reloading..." << endl << endl;
			Sleep(_reloadTime * 1000);
			if (_reserveAmmunition >= _roundsPerMag - _currentAmmunition)
			{
				_reserveAmmunition -= (_roundsPerMag - _currentAmmunition);
				_currentAmmunition = _roundsPerMag;
			}
			else
			{
				_currentAmmunition += _reserveAmmunition;
				_reserveAmmunition = 0;
			}
			cout << "Reloaded in: " << _reloadTime << "s\n" << endl;
		}

		cout << "Current Ammo: " << _currentAmmunition << " / " 
			<< _roundsPerMag << endl << "Remaining Ammo: " << _reserveAmmunition << endl << endl;

	}
};


#endif // !WEAPON_H


